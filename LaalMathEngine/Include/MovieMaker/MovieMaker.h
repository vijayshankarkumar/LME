#ifndef LAAL_MOVIE_MAKER_HPP
#define LAAL_MOVIE_MAKER_HPP

#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>

extern "C"
{
//#include <x264.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
}

#pragma warning(disable:4996)

namespace laal
{
	//! ============================================
	//! [MovieMaker]
	//! ============================================
	class MovieWriter
	{
		const unsigned int m_nFrameWidth;

		const unsigned int m_nFrameHeight;

		unsigned int m_nFrameCount;

		uint64_t m_nPtsCount;

		SwsContext* m_pSWSCtx;
		
		AVOutputFormat* m_pOutputFormat;
		
		AVStream* m_pStream;
		
		AVFormatContext* m_pFormatCtx;
		
		AVCodecContext* m_pCodecCtx;
		
		AVPacket m_Packet;

		AVFrame* m_pInputFrame;

		AVFrame* m_pOutputFrame;

	public:

		MovieWriter(const std::string& filename, const unsigned int width, const unsigned int height);

		void AddFrame(const uint8_t* pixels);

		~MovieWriter();
	};

	class MovieReader
	{
		const unsigned int width, height;

		SwsContext* swsCtx;
		
		AVOutputFormat* fmt;
		
		AVStream* stream;
		
		AVFormatContext* fc;
		
		AVCodecContext* c;
		
		AVFrame* pFrame;
		
		AVFrame* pFrameRGB;

		// The index of video stream.
		int ivstream;

	public:

		MovieReader(const std::string& filename, const unsigned int width, const unsigned int height);

		bool GetFrame(std::vector<uint8_t>& pixels);

		~MovieReader();
	};
}

#endif // !LAAL_MOVIE_MAKER_HPP
