#ifndef OPENCVUTIL_H
#define OPENCVUTIL_H
#include <opencv2/core/core.hpp>

namespace OpenCVUtil {
	const unsigned char U8_FULL      = 255;
	const unsigned char U8_HALF      = 127;
	const unsigned char U8_NONE      =   0;
	
	const   signed  int NOKEY_ANYKEY =  -1;
	
	const cv::Point2f ORIGIN2D(0, 0);

	namespace Color {
		const cv::Scalar ORANGE(U8_NONE, U8_HALF, U8_FULL);
		const cv::Scalar GREEN(U8_NONE, U8_FULL, U8_HALF);
		const cv::Scalar DARKBLUE(U8_HALF, U8_NONE, U8_NONE);
		const cv::Scalar LIGHTBLUE(U8_HALF, U8_FULL, U8_NONE);
		const cv::Scalar WHITE(U8_FULL, U8_FULL, U8_FULL);
		const cv::Scalar BLACK(U8_NONE, U8_NONE, U8_NONE);
	}

	/**
	 * Draws a cross on the image on location with color
	 * 
	 * @param image Image to be drawing cross on
	 * @param point Point on the image of the center of the cross
	 * @param color Color of the cross
	 * @param size Height=width of the cross
	 * @param thickness Thinkness of the lines of the cross
	 **/
	void drawCrossOnImage(cv::Mat& image, const cv::Point2f& point, const cv::Scalar& color, const unsigned int size, const unsigned int thickness);
}

#endif // OPENCVUTIL_H
