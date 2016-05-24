#ifndef OPENCVWINDOW_H
#define OPENCVWINDOW_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class OpenCVWindow {
	public:
		OpenCVWindow(const char* name_window, cv::Point2i position);
		
		cv::Mat getClonedImage() const;
		void drawImage(cv::Mat image);

	protected:
		const char* name_window;
		cv::Mat image;
};

#endif // OPENCVWINDOW_H
