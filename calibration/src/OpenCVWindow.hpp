#include <opencv2/imgproc/imgproc.hpp>

class OpenCVWindow {
	public:
		OpenCVWindow(const char* name_window, cv::Point2i position);
	
	private:
		const char* name_window;
};
