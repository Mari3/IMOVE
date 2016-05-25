#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Calibration.hpp"


const unsigned char U8_NONE = 0;

Calibration::Calibration(const cv::Size& resolution_projector, cv::Mat& camera_projector_transformation, unsigned int frames_projector_camera_delay, double projector_background_light) {
	this->resolution_projector = resolution_projector;
	this->camera_projector_transformation = camera_projector_transformation;
	this->frames_projector_camera_delay = frames_projector_camera_delay;
	this->projector_background_light = projector_background_light;
}

void Calibration::feedFrameProjector(const cv::Mat& frame_projector) {
	// add a cloned frame to the queue
	this->frames_delay_projector.push(frame_projector.clone());
}

void Calibration::eliminateProjectionFeedbackFromFrameCamera(cv::Mat& frame_projectioneliminated, const cv::Mat& frame_camera) {
	// Skip frames which are older than delay
  while ((frames_delay_projector.size() - 1) > this->frames_projector_camera_delay) {
	  this->frames_delay_projector.pop();
	}
	if (this->frames_delay_projector.empty()) {
		// use camera frame when no projector frames are (yet) fed
		frame_projectioneliminated = frame_camera;
	} else {
		// fill projection frame from camera frame using perspective map
		cv::warpPerspective(
			this->frames_delay_projector.front(),
			frame_projectioneliminated,
			this->camera_projector_transformation,
			frame_camera.size(),
			cv::INTER_LINEAR | cv::WARP_INVERSE_MAP,
			cv::BORDER_CONSTANT,
			cv::Scalar(U8_NONE, U8_NONE, U8_NONE)
		);
		// subtract given image based on light level difference between projection and background
		frame_projectioneliminated = frame_camera - (frame_projectioneliminated * this->projector_background_light);
	}
}

void Calibration::createPointsFrameProjectorFromPointsFrameCamera(std::vector<cv::Point2f>& points_frame_projector, const std::vector<cv::Point2f>& points_frame_camera) const {
	// cv::perspectiveTransform does not accept empty vector. this will result points_frame_projector to be empty vector as expected
	if (!points_frame_camera.empty()) {
		// fill projector frame points from camera frame points using perspective map
		cv::perspectiveTransform(
			points_frame_camera,
			points_frame_projector,
			this->camera_projector_transformation
		);
	}
}

void Calibration::changeProjectorFromCameraLocationPerson(std::vector<Person>& persons) const {
	// map std::vector<cv::Point2f> from std::vector<Person> for input this->createPointsFrameProjectorFramePointsFrameCamera
	std::vector<cv::Point2f> points_camera = std::vector<cv::Point2f>(persons.size());
	for (unsigned int i = 0; i < persons.size(); i++) {
		Vector2 location_person = persons.at(i).getLocation();
		points_camera.at(i) = cv::Point2f(
			location_person.x,
			location_person.y
		);
	}
	// fill projector frame points from camera frame points using perspective map
	std::vector<cv::Point2f> points_projector;
	this->createPointsFrameProjectorFromPointsFrameCamera(
		points_projector,
		points_camera
	);
	// set Persons location based on mapped projector frame points
	for (unsigned int i = 0; i < persons.size(); i++) {
		cv::Point2f point_projector = points_projector.at(i);
		persons.at(i).setLocation(Vector2(
			point_projector.x,
			point_projector.y
		));
	}
}

void Calibration::createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const {
	// fill projector frame from camera frame using perspective map
	cv::warpPerspective(
		frame_camera,
		frame_projection,
		this->camera_projector_transformation,
		this->resolution_projector
	);
}


void Calibration::setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay) {
	this->frames_projector_camera_delay = frames_projector_camera_delay;
}
void Calibration::setProjectorBackgroundLight(double projector_background_light) {
	this->projector_background_light = projector_background_light;
}
void Calibration::setCameraProjectorTransformation(cv::Mat& camera_projector_transformation) {
	this->camera_projector_transformation = camera_projector_transformation;
}
