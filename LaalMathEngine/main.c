//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <x264.h>
//
//
//#pragma warning(disable:4996)
//
//int imgSizeX = 854;
//int imgSizeY = 480;
//int frameNum = 60;
//
//void setParam(x264_param_t& param) {
//	x264_param_default_preset(&param, "veryfast", "zerolatency");
//	param.i_csp = X264_CSP_I420;
//	param.i_width = imgSizeX;
//	param.i_height = imgSizeY;
//	param.b_vfr_input = 0;
//	param.b_repeat_headers = 1;
//	param.i_keyint_max = 5;
//	param.b_annexb = 1;
//	param.b_opencl = 1;
//	param.i_fps_den = 1001;
//	param.i_fps_num = 30000;
//	x264_param_apply_profile(&param, "high");
//}
//
//void drawImgYUV(x264_picture_t& pic) {
//	static int count = 0;
//	// image input settings
//	for (int y = 0, j = 0; y < imgSizeY; ++y) {
//		for (int x = 0; x < imgSizeX; ++x, j++) {
//			// only draw Y channel, let UV channel to be default values.
//			pic.img.plane[0][j] = (x + count * 5) & 0xFF;
//		}
//	}
//	count++;
//}
//
//int main() {
//	FILE* file = fopen("out.h264", "wb");
//
//	x264_param_t param;
//	setParam(param);
//
//	x264_t* h = x264_encoder_open(&param);
//
//	x264_picture_t pic;
//	x264_picture_t pic_out;
//	x264_nal_t* nal;
//	int i_nal;
//	x264_picture_alloc(&pic, param.i_csp, param.i_width, param.i_height);
//
//	for (int i = 0; i < frameNum; ++i) {
//		drawImgYUV(pic);
//		int bytes = x264_encoder_encode(h, &nal, &i_nal, &pic, &pic_out);
//		printf("frame %d bytes %d\n", i, bytes);
//		if (bytes > 0) {
//			fwrite(nal->p_payload, bytes, 1, file);
//		}
//	}
//
//	/* Flush delayed frames */
//	/*while (x264_encoder_delayed_frames(h))
//	{
//		static int count = 0;
//		int bytes = x264_encoder_encode(h, &nal, &i_nal, NULL, &pic_out);
//		printf("frame %d bytes %d\n", count++, bytes);
//		if (bytes > 0) {
//			fwrite(nal->p_payload, bytes, 1, file);
//		}
//	}*/
//
//	x264_picture_clean(&pic);
//	x264_encoder_close(h);
//	fclose(file);
//	return 0;
//}