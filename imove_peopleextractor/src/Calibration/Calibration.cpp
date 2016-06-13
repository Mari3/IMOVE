#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/persistence.hpp>

#include "../OpenCVUtil.hpp"
#include "Calibration.hpp"
#include "../../../scene_interface/src/People.h"

Calibration::Calibration(const cv::Size& resolution_projector, const cv::Size& resolution_camera, unsigned int camera_device, const Boundary& projection, unsigned int frames_projector_camera_delay, double projector_background_light, float meter) {
	this->resolution_projector = resolution_projector;
	this->resolution_camera = resolution_camera;
	this->camera_device = camera_device;
	this->projection = projection;
	this->frames_projector_camera_delay = frames_projector_camera_delay;
	this->projector_background_light = projector_background_light;
	this->meter = meter;
	
	// create camera projection transformation based on 4 corners of the projection and the projector
	const unsigned int REQUIRED_CORNERS = 4;
	const unsigned int TOPLEFT          = 0;
	const unsigned int TOPRIGHT         = 1;
	const unsigned int BOTTOMLEFT       = 2;
	const unsigned int BOTTOMRIGHT      = 3;
	cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
	coordinate_corners_projector[TOPLEFT]     = cv::Point2f(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[TOPRIGHT]    = cv::Point2f(resolution_projector.width - 1,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[BOTTOMLEFT]  = cv::Point2f(		  	OpenCVUtil::ORIGIN2D.x, resolution_projector.height - 1);
	coordinate_corners_projector[BOTTOMRIGHT] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
	cv::Point2f* coordinate_corners_projection  = new cv::Point2f[REQUIRED_CORNERS];
	coordinate_corners_projection[TOPLEFT]     = cv::Point2f(projection.getUpperLeft().x, projection.getUpperLeft().y);
	coordinate_corners_projection[TOPRIGHT]    = cv::Point2f(projection.getUpperRight().x, projection.getUpperRight().y);
	coordinate_corners_projection[BOTTOMLEFT]  = cv::Point2f(projection.getLowerLeft().x, projection.getLowerLeft().y);
	coordinate_corners_projection[BOTTOMRIGHT] = cv::Point2f(projection.getLowerRight().x, projection.getLowerRight().y);
	this->camera_projector_transformation = cv::getPerspectiveTransform(
		coordinate_corners_projection,
		coordinate_corners_projector
	);
}

/**
 * Creates the boundary from the camera frame
 * 
 * @param resolution_camera The resolution of the camera for which to construct the camera frame boundary
 **/
const Boundary createBoundaryFrameCamera(cv::Size resolution_camera) {
	return Boundary(
		Vector2(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y),
		Vector2(resolution_camera.width - 1,          OpenCVUtil::ORIGIN2D.y),
		Vector2(		  	OpenCVUtil::ORIGIN2D.x, resolution_camera.height - 1),
		Vector2(resolution_camera.width - 1, resolution_camera.height - 1)
	);
}

/**
 * Creates the boundary of the projection from the camera projector transformation and resolution projector
 * 
 * @param resolution_projector            The resolution of the projector
 * @param camera_projector_transformation The camera projector perspective transformation
 **/
const Boundary createBoundaryProjectionFromCameraProjectorTransformation(const cv::Size resolution_projector, const cv::Mat camera_projector_transformation) {
	std::vector<cv::Point2f> coordinate_corners_projector;
	coordinate_corners_projector.push_back(cv::Point2f(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y));
	coordinate_corners_projector.push_back(cv::Point2f(resolution_projector.width - 1,          OpenCVUtil::ORIGIN2D.y));
	coordinate_corners_projector.push_back(cv::Point2f(		  	OpenCVUtil::ORIGIN2D.x, resolution_projector.height - 1));
	coordinate_corners_projector.push_back(cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1));
	std::vector<cv::Point2f> coordinate_corners_projection;
	
	cv::perspectiveTransform(
		coordinate_corners_projector,
		coordinate_corners_projection,
		camera_projector_transformation.inv()
	);

	const unsigned int TOPLEFT          = 0;
	const unsigned int TOPRIGHT         = 1;
	const unsigned int BOTTOMLEFT       = 2;
	const unsigned int BOTTOMRIGHT      = 3;
	return Boundary(
		Vector2(coordinate_corners_projection.at(TOPLEFT).x, coordinate_corners_projection.at(TOPLEFT).y),
		Vector2(coordinate_corners_projection.at(TOPRIGHT).x, coordinate_corners_projection.at(TOPRIGHT).y),
		Vector2(coordinate_corners_projection.at(BOTTOMLEFT).x, coordinate_corners_projection.at(BOTTOMLEFT).y),
		Vector2(coordinate_corners_projection.at(BOTTOMRIGHT).x, coordinate_corners_projection.at(BOTTOMRIGHT).y)
	);
}

Calibration* Calibration::readFile(const char* filepath) {
	// read Calibration config
	cv::FileStorage fs;
	fs.open(filepath, cv::FileStorage::READ);

	// read camera_device from yml using OpenCV FileNode
	unsigned int camera_device;
	  signed int int_camera_device;
	fs["Camera_device"] >> int_camera_device;
	// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
	if (int_camera_device < 0) {
		camera_device = 0;
	} else {
		camera_device = (unsigned int) int_camera_device;
	}
	// read resolution_camera from yml using OpenCV FileNode
	cv::Size resolution_camera;
	fs["Resolution_camera"] >> resolution_camera;
	// read resolution_projector from yml using OpenCV FileNode
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	// read camera_projector_transformation from yml using OpenCV FileNode
	cv::Mat camera_projector_transformation;
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	// read frames_projector_camera_delay from yml using OpenCV FileNode
	unsigned int frames_projector_camera_delay;
	  signed int int_frames_projector_camera_delay;
	fs["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
	// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
	if (int_frames_projector_camera_delay < 0) {
		frames_projector_camera_delay = 0;
	} else {
		frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
	}
	// read percentage_projector_background_light from yml using OpenCV FileNode
	double percentage_projector_background_light;
	fs["Percentage_projector_background_light"] >> percentage_projector_background_light;
	// read meter from yml using OpenCV FileNode
	float meter;
	fs["Meter"] >> meter;
	fs.release();

	return new Calibration(
		resolution_projector,
		resolution_camera,
		camera_device,
		createBoundaryProjectionFromCameraProjectorTransformation(
			resolution_projector,
			camera_projector_transformation
		),
		frames_projector_camera_delay,
		percentage_projector_background_light,
		meter
	);
}

Calibration* Calibration::createFromFile(const char* filepath, unsigned int cameradevice, cv::Size resolution_projector) {
	cv::FileStorage read_config;
	read_config.open(filepath, cv::FileStorage::READ);
	
	// read frames_projector_camera_delay from yml using OpenCV FileNode; default if not existing
	unsigned int frames_projector_camera_delay;
	if (read_config["Frames_projector_camera_delay"].isNone()) {
		frames_projector_camera_delay = Calibration::DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY;
	} else {
		signed int int_frames_projector_camera_delay;
		read_config["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
		// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
		if (int_frames_projector_camera_delay < 0) {
			frames_projector_camera_delay = 0;
		} else {
			frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
		}
	}
	// read projector_background_light from yml using OpenCV FileNode; default if not existing
	double projector_background_light;
	if (read_config["Projector_background_light"].isNone()) {
		projector_background_light = Calibration::DEFAULT_PROJECTOR_BACKGROUND_LIGHT;
	} else {
		read_config["Projector_background_light"] >> projector_background_light;
	}
	// read meter from yml using OpenCV FileNode; default if not existing
	float meter;
	if (read_config["Meter"].isNone()) {
		meter = Calibration::DEFAULT_METER;
	} else {
		read_config["Meter"] >> meter;
	}
 
	// retreive camera resolution from OpenCV VideoCapture
	cv::VideoCapture camera_videoreader(cameradevice);
	const cv::Size resolution_camera(camera_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), camera_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	camera_videoreader.release();
	
	// read camera_projector_transformation from yml using OpenCV FileNode
	Boundary projection;
	if (read_config["Camera_projector_transformation"].isNone()) {
		// if not exists in configuration; create projection as whole camera frame
		projection = createBoundaryFrameCamera(resolution_camera);
	} else {
		cv::Mat camera_projector_transformation;
		read_config["Camera_projector_transformation"] >> camera_projector_transformation;
		projection = createBoundaryProjectionFromCameraProjectorTransformation(
			resolution_projector,
			camera_projector_transformation
		);
	}

	read_config.release();
	
 	// create initial Calibration based on configuration, arguments and defaults
	return new Calibration(
		resolution_projector,
		resolution_camera,
		cameradevice,
		projection,
		frames_projector_camera_delay,
		projector_background_light,
		meter
	);
}

void Calibration::writeFile(const char* filepath) const {
	// write configuration based on Calibration
	cv::FileStorage write_config(filepath, cv::FileStorage::WRITE);
	
	write_config << "Camera_device" << (int) this->camera_device;
	write_config << "Resolution_camera" << this->resolution_camera;
	write_config << "Resolution_projector" << this->resolution_projector;
	write_config << "Camera_projector_transformation" << this->camera_projector_transformation;
	write_config << "Frames_projector_camera_delay" << (int) this->frames_projector_camera_delay;
	write_config << "Projector_background_light" << this->projector_background_light;
	write_config << "Meter" << this->meter;
	
	write_config.release();
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
			OpenCVUtil::Color::BLACK
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

const scene_interface::People Calibration::createPeopleProjectorFromPeopleCamera(const scene_interface::People& people_camera) const {
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

void Calibration::createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const {
	// fill projector frame from camera frame using perspective map
	cv::warpPerspective(
		frame_camera,
		frame_projection,
		this->camera_projector_transformation,
		this->resolution_projector
	);
}


unsigned int Calibration::getFramesProjectorCameraDelay() const {
	return this->frames_projector_camera_delay;
}
void Calibration::setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay) {
	this->frames_projector_camera_delay = frames_projector_camera_delay;
}
double Calibration::getProjectorBackgroundLight() const {
	return this->projector_background_light;
}
void Calibration::setProjectorBackgroundLight(double projector_background_light) {
	this->projector_background_light = projector_background_light;
}
cv::Mat Calibration::getCameraProjectorTransformation() const {
	return this->camera_projector_transformation;
}
void Calibration::setCameraProjectorTransformation(cv::Mat& camera_projector_transformation) {
	this->camera_projector_transformation = camera_projector_transformation;
}
cv::Size Calibration::getResolutionProjector() const {
	return this->resolution_projector;
}
cv::Size Calibration::getResolutionCamera() const {
	return this->resolution_camera;
}
unsigned int Calibration::getCameraDevice() const {
	return this->camera_device;
}
void Calibration::setMeter(float meter) {
	this->meter = meter;
}
const float Calibration::getMeter() const {
	return this->meter;
}
const Boundary Calibration::getProjection() const {
	return this->projection;
}
