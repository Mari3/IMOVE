#include "Manager.hpp"

#include "../../imove/src/OpenCVUtil.hpp"
#include "Windows/Projection.hpp"
#include "Windows/Projector.hpp"
#include "Windows/CalibrationProjection.hpp"
#include "Windows/CalibrationMeter.hpp"
#include "Windows/EliminateProjection.hpp"

CalibrationManager::CalibrationManager(Calibration* calibration) {
	this->calibration = calibration;
}

void CalibrationManager::run() {
	// setup camera
	cv::Mat frame_camera;
	cv::VideoCapture camera_videoreader(calibration->getCameraDevice());
	camera_videoreader.set(cv::CAP_PROP_AUTOFOCUS, 0);
	
	// setup calibration windows
	ProjectorWindow projector_window(cv::Size(0, 0));
	CalibrationProjectionWindow calibrationprojection_window(cv::Point2i(300, 0), calibration);
	CalibrationMeterWindow calibrationmeter_window(cv::Point2i(600, 0), calibration);
	EliminateProjectionWindow eliminateprojection_window(cv::Size(900, 0), calibration);
	ProjectionWindow projection_window(cv::Size(1200, 0), calibration);

	cv::Mat frame_projector;
	// while camera frame can be read and while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && camera_videoreader.read(frame_camera)) {
		// initialize a black projector frame
		frame_projector = cv::Mat::zeros(calibration->getResolutionProjector(), CV_8UC3);
		// draw projector image for calibration
		projector_window.drawImage(frame_projector);
		
		// feed calibration image for delay and brightness calibration
		calibration->feedFrameProjector(projector_window.getClonedImage());
		// draw calibrated eliminated camera image
		eliminateprojection_window.drawImage(frame_camera);
		
		// draw calibrated eliminated projection image
		projection_window.drawImage(eliminateprojection_window.getClonedImage());
		
		// draw calibration projection image
		calibrationprojection_window.drawImage(frame_camera.clone());
		// draw calibration meter image
		calibrationmeter_window.drawImage(frame_camera.clone());
	}
	
	//safe release camera
	camera_videoreader.release();
}
