#include "./EliminateProjectionWindow.hpp"

EliminateProjectionWindow::EliminateProjectionWindow(cv::Point2i position, Calibration* calibration) : OpenCVWindow("Eliminate projection", position) {
	this->calibration = calibration;
	track_projector_background_light = round(this->calibration->getProjectorBackgroundLight() * FLOAT_FULL_PERCENTAGE);
	cv::createTrackbar(this->name_trackbar_ratio_projector_background_light, this->name_window, &this->track_projector_background_light, this->INT_FULL_PERCENTAGE, EliminateProjectionWindow::onProjectorBackgroundLight, (void*) &*this);
	this->track_frames_projector_camera_delay = (signed int) this->calibration->getFramesProjectorCameraDelay();
	cv::createTrackbar(this->name_trackbar_frames_projector_camera_delay, this->name_window, &this->track_frames_projector_camera_delay, this->INT_FULL_PERCENTAGE, EliminateProjectionWindow::onFramesProjectorCameraDelay, (void*) &*this);
}

void EliminateProjectionWindow::drawImage(cv::Mat image_camera) {
	cv::Mat image_projectionelimination;

	this->calibration->eliminateProjectionFeedbackFromFrameCamera(image_projectionelimination, image_camera);
	OpenCVWindow::drawImage(image_projectionelimination);
}

// Projector background light trackbar callback
void EliminateProjectionWindow::onProjectorBackgroundLight(int tracked_int, void *param) {
	EliminateProjectionWindow* that = (EliminateProjectionWindow*) param;

	// set as float from percentage
	that->calibration->setProjectorBackgroundLight(((float) tracked_int) / that->FLOAT_FULL_PERCENTAGE);
}

// Amount of frames delay between projection and camera trackbar callback
void EliminateProjectionWindow::onFramesProjectorCameraDelay(int tracked_int, void *param) {
	EliminateProjectionWindow* that = (EliminateProjectionWindow*) param;
	
	if (tracked_int < 0) {
		that->calibration->setFramesProjectorCameraDelay(0);
	} else {
		that->calibration->setFramesProjectorCameraDelay((unsigned int) tracked_int);
	}
}
