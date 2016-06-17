#include "ImoveConfiguration.hpp"
#include "../OpenCVUtil.hpp"

ImoveConfiguration::ImoveConfiguration(const bool debug_mode, CameraConfiguration* camera_configuration, ProjectorConfiguration* projector_configuration, ProjectioneliminationConfiguration* projectionelimination_configuration) :
debug_mode(debug_mode),
camera_configuration(camera_configuration),
projector_configuration(projector_configuration),
projectionelimination_configuration(projectionelimination_configuration)
{
	this->deriveCameraProjectorTransformation();
	this->deriveMeterProjectorFromMeterCamera();
}

ImoveConfiguration* ImoveConfiguration::readFile(const char* filepath) {
	// read ImoveConfiguration config
	cv::FileStorage read_config;
	read_config.open(filepath, cv::FileStorage::READ);
	
	// read debug mode from yml using OpenCV FileNode
	bool debug_mode;
	read_config["Debug_mode"] >> debug_mode;
 	
	// create initial ImoveConfiguration based on configuration and defaults
	CameraConfiguration* camera_configuration = CameraConfiguration::readNode(read_config);
	ProjectorConfiguration* projector_configuration = ProjectorConfiguration::readNode(read_config);
	ProjectioneliminationConfiguration* projectionelimination_configuration = ProjectioneliminationConfiguration::readNode(read_config);
	ImoveConfiguration* calibration = new ImoveConfiguration(
		debug_mode,
		camera_configuration,
		projector_configuration,
		projectionelimination_configuration
	);

	read_config.release();

	return calibration;
}

ImoveConfiguration* ImoveConfiguration::createFromFile(const char* filepath, const int deviceid_camera, const cv::Size& resolution_projector) {
	cv::FileStorage read_config;
	read_config.open(filepath, cv::FileStorage::READ);
	
	// read debug mode from yml using OpenCV FileNode; default if not existing
	bool debug_mode;
	if (read_config["Debug_mode"].isNone()) {
		debug_mode = ImoveConfiguration::DEFAULT_DEBUG_MODE;
	} else {
		read_config["Debug_mode"] >> debug_mode;
	}
	
 	// create initial ImoveConfiguration based on configuration and defaults
	CameraConfiguration* camera_configuration = CameraConfiguration::createFromNode(read_config, deviceid_camera);
	ProjectorConfiguration* projector_configuration = ProjectorConfiguration::createFromNode(read_config, resolution_projector);
	ProjectioneliminationConfiguration* projectionelimination_configuration = ProjectioneliminationConfiguration::createFromNode(read_config);
	ImoveConfiguration* calibration = new ImoveConfiguration(
		debug_mode,
		camera_configuration,
		projector_configuration,
		projectionelimination_configuration
	);

	read_config.release();

	return calibration;
}

void ImoveConfiguration::writeFile(const char* filepath) const {
	// write configuration based on ImoveConfiguration
	cv::FileStorage write_config(filepath, cv::FileStorage::WRITE);
	
	write_config << "Debug_mode" << (int) this->debug_mode;

	this->camera_configuration->writeNode(write_config);
	this->projector_configuration->writeNode(write_config);
	this->projectionelimination_configuration->writeNode(write_config);
	
	write_config.release();
}

CameraConfiguration* ImoveConfiguration::getCameraConfiguration() const {
	return this->camera_configuration;
}

ProjectorConfiguration* ImoveConfiguration::getProjectorConfiguration() const {
	return this->projector_configuration;
}

ProjectioneliminationConfiguration* ImoveConfiguration::getProjectioneliminationConfiguration() const {
	return this->projectionelimination_configuration;
}

void ImoveConfiguration::deriveMeterProjectorFromMeterCamera() {
	std::vector<cv::Point2f> projector_points;
	std::vector<cv::Point2f> camera_points;
	cv::Size resolution_camera = this->camera_configuration->getResolution();
	float half_meter = this->camera_configuration->getMeter() / 2;
	cv::Point2f center_camera(
		resolution_camera.width / 2,
		resolution_camera.height / 2
	);
	camera_points.push_back(cv::Point2f(
		center_camera.x - half_meter,
		center_camera.y
	));
	camera_points.push_back(cv::Point2f(
		center_camera.x + half_meter,
		center_camera.y
	));
	cv::perspectiveTransform(
		camera_points,
		projector_points,
		this->getCameraProjectorTransformation()
	);
	float xdiff = projector_points.at(0).x - projector_points.at(1).x;
	float ydiff = projector_points.at(0).y - projector_points.at(1).y;
	this->projector_configuration->setMeter(sqrt(xdiff * xdiff + ydiff * ydiff));
}
void ImoveConfiguration::deriveCameraProjectorTransformation() {
	// create camera projection transformation based on 4 corners of the projection and the projector
	const unsigned int REQUIRED_CORNERS = 4;
	const unsigned int TOPLEFT          = 0;
	const unsigned int TOPRIGHT         = 1;
	const unsigned int BOTTOMLEFT       = 2;
	const unsigned int BOTTOMRIGHT      = 3;
	const cv::Size& resolution_projector = this->getProjectorConfiguration()->getResolution();
	const Boundary& projection = this->getCameraConfiguration()->getProjection();
	cv::Point2f* coordinate_corners_projector = new cv::Point2f[REQUIRED_CORNERS];
	coordinate_corners_projector[TOPLEFT]     = cv::Point2f(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[TOPRIGHT]    = cv::Point2f(resolution_projector.width - 1,          OpenCVUtil::ORIGIN2D.y);
	coordinate_corners_projector[BOTTOMLEFT]  = cv::Point2f(		  	OpenCVUtil::ORIGIN2D.x, resolution_projector.height - 1);
	coordinate_corners_projector[BOTTOMRIGHT] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
	cv::Point2f* coordinate_corners_projection = new cv::Point2f[REQUIRED_CORNERS];
	coordinate_corners_projection[TOPLEFT]     = cv::Point2f( projection.getUpperLeft().x,  projection.getUpperLeft().y);
	coordinate_corners_projection[TOPRIGHT]    = cv::Point2f(projection.getUpperRight().x, projection.getUpperRight().y);
	coordinate_corners_projection[BOTTOMLEFT]  = cv::Point2f( projection.getLowerLeft().x,  projection.getLowerLeft().y);
	coordinate_corners_projection[BOTTOMRIGHT] = cv::Point2f(projection.getLowerRight().x, projection.getLowerRight().y);
	this->camera_projector_transformation = cv::getPerspectiveTransform(
		coordinate_corners_projection,
		coordinate_corners_projector
	);
}

const cv::Mat ImoveConfiguration::getCameraProjectorTransformation() {
	return this->camera_projector_transformation;
}
const bool ImoveConfiguration::getDebugMode() const {
	return this->debug_mode;
}
