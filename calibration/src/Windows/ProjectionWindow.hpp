#include <opencv2/opencv.hpp>

#include "../../../util/src/OpenCVWindow.hpp"
#include "../../../util/src/Projection.hpp"

class ProjectionWindow : public OpenCVWindow {
	public:
		ProjectionWindow(cv::Point2i position, cv::Size size, Projection* projection);
		
		void drawImage(cv::Mat image_camera);

	protected:
		Projection* projection;
};
