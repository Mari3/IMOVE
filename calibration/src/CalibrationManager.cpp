#include "CalibrationManager.hpp"

#include "../../util/src/OpenCVUtil.hpp"
#include "Windows/ProjectionWindow.hpp"
#include "Windows/ProjectorWindow.hpp"
#include "Windows/CalibrationProjectionWindow.hpp"
#include "Windows/CalibrationMeterWindow.hpp"
#include "Windows/EliminateProjectionWindow.hpp"

CalibrationManager::CalibrationManager(Calibration& calibration) : calibration(calibration), projection(Projection(calibration)) {}

void CalibrationManager::run() {
	// setup camera
	cv::Mat frame_camera;
	cv::VideoCapture camera_videoreader(calibration.getCameraDevice());
	camera_videoreader.set(cv::CAP_PROP_AUTOFOCUS, 0);
	
	// setup Calibration windows
	ProjectorWindow projector_window(cv::Point2i(this->calibration.getResolutionProjector().width, 0), cv::Size(300, 300));
	CalibrationProjectionWindow calibrationprojection_window(cv::Point2i(this->calibration.getResolutionProjector().width + 300, 0), cv::Size(300, 300), this->calibration);
	CalibrationMeterWindow calibrationmeter_window(cv::Point2i(this->calibration.getResolutionProjector().width + 600, 0), cv::Size(300, 300), this->calibration);
	EliminateProjectionWindow eliminateprojection_window(cv::Point2i(this->calibration.getResolutionProjector().width, 300), cv::Size(300, 300), this->calibration, this->projection);
	ProjectionWindow projection_window(cv::Point2i(this->calibration.getResolutionProjector().width + 300, 300), cv::Size(300, 300), this->projection);

	cv::Mat frame_projector;
	// while camera frame can be read and while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && camera_videoreader.read(frame_camera)) {
		// initialize a black projector frame
		frame_projector = cv::Mat::zeros(calibration.getResolutionProjector(), CV_8UC3);
		// draw projector image for Calibration
		projector_window.drawImage(frame_projector);
		
		// feed Calibration image for delay and brightness Calibration
		projection.feedFrameProjector(projector_window.getClonedImage());
		// draw calibrated eliminated camera image
		eliminateprojection_window.drawImage(frame_camera);
		
		// draw calibrated eliminated projection image
		projection_window.drawImage(eliminateprojection_window.getClonedImage());
		
		// draw Calibration projection image
		calibrationprojection_window.drawImage(frame_camera.clone());
		// draw Calibration meter image
		calibrationmeter_window.drawImage(frame_camera.clone());
	}
	
	//safe release camera
	camera_videoreader.release();
}
