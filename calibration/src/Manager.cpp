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

bool CalibrationManager::run() {
	// setup calibration windows
	cv::Mat frame_camera;
	cv::VideoCapture camera_videoreader(calibration->getCameraDevice());
	camera_videoreader.set(cv::CAP_PROP_AUTOFOCUS, 0);
	
	ProjectorWindow projector_window(cv::Size(0, 0));
	CalibrationProjectionWindow calibrationprojection_window(cv::Point2i(300, 0), calibration);
	CalibrationMeterWindow calibrationmeter_window(cv::Point2i(600, 0), calibration);
	EliminateProjectionWindow eliminateprojection_window(cv::Size(900, 0), calibration);
	ProjectionWindow projection_window(cv::Size(1200, 0), calibration);

	cv::Mat frame_projector;
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && camera_videoreader.read(frame_camera)) {
		frame_projector = cv::Mat::zeros(calibration->getResolutionProjector(), CV_8UC3);
		projector_window.drawImage(frame_projector);
		calibration->feedFrameProjector(projector_window.getClonedImage());
		eliminateprojection_window.drawImage(frame_camera);
		
		projection_window.drawImage(eliminateprojection_window.getClonedImage());
		
		calibrationprojection_window.drawImage(frame_camera.clone());
		calibrationmeter_window.drawImage(frame_camera.clone());
	}

	camera_videoreader.release();

	return true;
}
