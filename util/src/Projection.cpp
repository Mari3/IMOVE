#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "OpenCVUtil.hpp"
#include "Projection.hpp"
#include "../../scene_interface/src/People.h"

Projection::Projection(ImoveConfiguration* calibration)
: calibration(calibration)
{}

void Projection::feedFrameProjector(const cv::Mat& frame_projector) {
	// add a cloned frame to the queue
	this->frames_delay_projector.push(frame_projector.clone());
}

void Projection::eliminateProjectionFeedbackFromFrameCamera(cv::Mat& frame_projectioneliminated, const cv::Mat& frame_camera) {
	// Skip frames which are older than delay
	ProjectioneliminationConfiguration* projectionelimination_configuration = this->calibration->getProjectioneliminationConfiguration();
	while ((((signed int) frames_delay_projector.size()) - 1) > (signed int) projectionelimination_configuration->getFramesProjectorCameraDelay()) {
	  this->frames_delay_projector.pop();
	}
	if (this->frames_delay_projector.size() <= projectionelimination_configuration->getFramesProjectorCameraDelay()) {
		// use camera frame when no projector frames are (yet) fed
		frame_projectioneliminated = frame_camera;
	} else {
		// fill projection frame from camera frame using perspective map
		cv::warpPerspective(
			this->frames_delay_projector.front(),
			frame_projectioneliminated,
			this->calibration->getCameraProjectorTransformation(),
			frame_camera.size(),
			cv::INTER_LINEAR | cv::WARP_INVERSE_MAP,
			cv::BORDER_CONSTANT,
			OpenCVUtil::Color::BLACK
		);
		// subtract given image based on light level difference between projection and background
		frame_projectioneliminated = frame_camera - (frame_projectioneliminated * projectionelimination_configuration->getProjectorBackgroundLight());
	}
}

void Projection::createPointsFrameProjectorFromPointsFrameCamera(std::vector<cv::Point2f>& points_frame_projector, const std::vector<cv::Point2f>& points_frame_camera) const {
	// cv::perspectiveTransform does not accept empty vector. this will result points_frame_projector to be empty vector as expected
	if (!points_frame_camera.empty()) {
		// fill projector frame points from camera frame points using perspective map
		cv::perspectiveTransform(
			points_frame_camera,
			points_frame_projector,
			this->calibration->getCameraProjectorTransformation()
		);
	}
}

const scene_interface::People Projection::createPeopleProjectorFromPeopleCamera(const scene_interface::People& people_camera) const {
	// map std::vector<cv::Point2f> from std::vector<scene_interface::Person> for input this->createPointsFrameProjectorFramePointsFrameCamera
	std::vector<cv::Point2f> points_camera = std::vector<cv::Point2f>(people_camera.size());
	for (unsigned int i = 0; i < people_camera.size(); i++) {
		scene_interface::Location location_person = people_camera.at(i).getLocation();
		points_camera.at(i) = cv::Point2f(
			location_person.getX(),
			location_person.getY()
		);
	}
	// fill projector frame points from camera frame points using perspective map
	std::vector<cv::Point2f> points_projector;
	this->createPointsFrameProjectorFromPointsFrameCamera(
		points_projector,
		points_camera
	);
	// set scene_interface::People location based on mapped projector frame points
	scene_interface::People people_projector;
	for (unsigned int i = 0; i < people_camera.size(); ++i) {
		scene_interface::Person person_camera = people_camera.at(i);
		// create person type from shared memory person type
		cv::Point2f point_projector = points_projector.at(i);
		people_projector.push_back(scene_interface::Person(
			person_camera.getId(),
			scene_interface::Location(
				point_projector.x,
				point_projector.y
			),
			person_camera.getPersonType(),
			person_camera.getMovementType()
		));
	}
	return people_projector;
}

void Projection::createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const {
	// fill projector frame from camera frame using perspective map
	cv::warpPerspective(
		frame_camera,
		frame_projection,
		this->calibration->getCameraProjectorTransformation(),
		this->calibration->getProjectorConfiguration()->getResolution()
	);
}
