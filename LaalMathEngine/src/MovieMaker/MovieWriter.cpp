#include "MovieMaker/MovieMaker.h"

namespace laal
{
	// One-time initialization.
	class FFmpegInitialize
	{
	public:

		FFmpegInitialize()
		{
			// Loads the whole database of available codecs and formats.
			av_register_all();
		}
	};

	static FFmpegInitialize ffmpegInitialize;

	MovieWriter::MovieWriter(const std::string& filename, const unsigned int width, const unsigned int height) :
		m_nFrameWidth(width),
		m_nFrameHeight(height),
		m_nFrameCount(0),
		m_nPtsCount(0)
	{
		// Preparing to convert my generated RGB images to YUV frames.
		m_pSWSCtx = sws_getContext(width, height, AV_PIX_FMT_ARGB, width, height, AV_PIX_FMT_YUV420P, SWS_FAST_BILINEAR, NULL, NULL, NULL);

		// Preparing the data concerning the format and codec,
		// in order to write properly the header, frame data and end of file.
		const char* fmtext = "mp4";
		const std::string file = filename + "." + fmtext;
		m_pOutputFormat = av_guess_format(fmtext, NULL, NULL);
		avformat_alloc_output_context2(&m_pFormatCtx, NULL, NULL, file.c_str());

		// Setting up the codec.
		AVCodec* codec = avcodec_find_encoder_by_name("libx264");
		AVDictionary* opt = NULL;
		av_dict_set(&opt, "preset", "slow", 0);
		av_dict_set(&opt, "crf", "20", 0);
		m_pStream = avformat_new_stream(m_pFormatCtx, codec);
		m_pCodecCtx = m_pStream->codec;
		m_pCodecCtx->width = width;
		m_pCodecCtx->height = height;
		m_pCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
		m_pCodecCtx->time_base = av_make_q(1, 30);

		// Setting up the format, its stream(s),
		// linking with the codec(s) and write the header.
		if (m_pFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
		{
			// Some formats require a global header.
			m_pCodecCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
		}
		avcodec_open2(m_pCodecCtx, codec, &opt);
		av_dict_free(&opt);

		// Once the codec is set up, we need to let the container know
		// which codec are the streams using, in this case the only (video) stream.
		//m_pStream->time_base = av_make_q(1, 30);
		av_dump_format(m_pFormatCtx, 0, file.c_str(), 1);
		avio_open(&m_pFormatCtx->pb, file.c_str(), AVIO_FLAG_WRITE);
		int ret = avformat_write_header(m_pFormatCtx, &opt);
		av_dict_free(&opt);

		// Preparing the containers of the frame data:
		// Allocating memory for each RGB frame, which will be lately converted to YUV.
		m_pInputFrame = av_frame_alloc();
		m_pInputFrame->format = AV_PIX_FMT_ARGB;
		m_pInputFrame->width = width;
		m_pInputFrame->height = height;
		ret = av_frame_get_buffer(m_pInputFrame, 1);

		// Allocating memory for each conversion output YUV frame.
		m_pOutputFrame = av_frame_alloc();
		m_pOutputFrame->format = AV_PIX_FMT_YUV420P;
		m_pOutputFrame->width = width;
		m_pOutputFrame->height = height;
		ret = av_frame_get_buffer(m_pOutputFrame, 1);

		// After the format, code and general frame data is set,
		// we can write the video in the frame generation loop:
		// std::vector<uint8_t> B(width*height*3);
	}

	void MovieWriter::AddFrame(const uint8_t* pixels)
	{
		// The AVFrame data will be stored as RGBRGBRGB... row-wise,
		// from left to right and from top to bottom.
		//av_frame_unref(rgbpic);
		//static int count = 0;
		//std::cout << "in the frame " << count++ << std::endl;
		//std::cout << (int)pixels[0] << " " << (int)pixels[1] << " " << (int)pixels[2] << " " << (int)pixels[3] << std::endl;
		//std::cout << "width => " << m_nFrameWidth << "height => " << m_nFrameHeight << std::endl;
		for (unsigned int y = 0; y < m_nFrameHeight; y++)
		{
			for (unsigned int x = 0; x < m_nFrameWidth; x++)
			{
				//rgbpic->linesize[0] is equal to width.
				m_pInputFrame->data[0][y * m_pInputFrame->linesize[0] + 4 * x + 0] = pixels[y * 4 * m_nFrameWidth + 4 * x + 3];
				m_pInputFrame->data[0][y * m_pInputFrame->linesize[0] + 4 * x + 1] = pixels[y * 4 * m_nFrameWidth + 4 * x + 2];
				m_pInputFrame->data[0][y * m_pInputFrame->linesize[0] + 4 * x + 2] = pixels[y * 4 * m_nFrameWidth + 4 * x + 1];
				m_pInputFrame->data[0][y * m_pInputFrame->linesize[0] + 4 * x + 3] = pixels[y * 4 * m_nFrameWidth + 4 * x + 0];
			}
		}

		// Not actually scaling anything, but just converting
		// the RGB data to YUV and store it in yuvpic.
		sws_scale(m_pSWSCtx, m_pInputFrame->data, m_pInputFrame->linesize, 0, m_nFrameHeight, m_pOutputFrame->data, m_pOutputFrame->linesize);

		av_init_packet(&m_Packet);
		m_Packet.data = NULL;
		m_Packet.size = 0;

		// The PTS of the frame are just in a reference unit,
		// unrelated to the format we are using. We set them,
		// for instance, as the corresponding frame number.
		//std::cout << "codec time base ---> "<< m_pCodecCtx->time_base.num << " " << m_pCodecCtx->time_base.den << std::endl;
		//std::cout << "stream time base ---> "<< m_pStream->time_base.num << " " << m_pStream->time_base.den << std::endl;
		//std::cout << "---> "<< m_nPtsCount * m_pStream->time_base.den / 30 << std::endl;
		//m_pInputFrame->pts = m_nPtsCount * m_pStream->time_base.den / 30;

		m_pOutputFrame->pts = m_nPtsCount;
		m_nPtsCount += 1;
		
		//m_pOutputFrame->pts = m_nFrameCount;

		int got_output;
		int ret = avcodec_encode_video2(m_pCodecCtx, &m_Packet, m_pOutputFrame, &got_output);
		if (got_output)
		{
			// We set the packet PTS and DTS taking in the account our FPS (second argument),
			// and the time base that our selected format uses (third argument).
			av_packet_rescale_ts(&m_Packet, av_make_q(1, 30), m_pStream->time_base);

			m_Packet.stream_index = m_pStream->index;
			std::cout << "Writing frame " << m_nFrameCount++ << " (size = " << m_Packet.size << ")"<< std::endl;

			// Write the encoded frame to the mp4 file.
			av_interleaved_write_frame(m_pFormatCtx, &m_Packet);
			av_packet_unref(&m_Packet);
		}
	}

	MovieWriter::~MovieWriter()
	{
		// Writing the delayed frames:
		for (int got_output = 1; got_output; )
		{
			int ret = avcodec_encode_video2(m_pCodecCtx, &m_Packet, NULL, &got_output);
			if (got_output)
			{
				av_packet_rescale_ts(&m_Packet, av_make_q(1, 30), m_pStream->time_base);
				m_Packet.stream_index = m_pStream->index;
				std::cout << "Writing frame " << m_nFrameCount++ << " (size = " << m_Packet.size << ")" << std::endl;
				av_interleaved_write_frame(m_pFormatCtx, &m_Packet);
				av_packet_unref(&m_Packet);
			}
		}

		// Writing the end of the file.
		av_write_trailer(m_pFormatCtx);

		// Closing the file.
		if (!(m_pOutputFormat->flags & AVFMT_NOFILE))
			avio_closep(&m_pFormatCtx->pb);
		avcodec_close(m_pStream->codec);

		// Freeing all the allocated memory:
		sws_freeContext(m_pSWSCtx);
		av_frame_free(&m_pInputFrame);
		av_frame_free(&m_pOutputFrame);
		avformat_free_context(m_pFormatCtx);
	}
}