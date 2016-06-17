#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/persistence.hpp>
#include <assert.h>

#include "ProjectorConfiguration.hpp"

ProjectorConfiguration::ProjectorConfiguration(const cv::Size& resolution, const bool& fullscreen, float meter, unsigned int maximum_fps_scene) : Configuration(),
	resolution(resolution),
	fullscreen(fullscreen),
	meter(meter),
	maximum_fps_scene(maximum_fps_scene)
{}

ProjectorConfiguration* ProjectorConfiguration::readNode(cv::FileStorage read_config) {
	// read resolutionfrom yml using OpenCV FileStorage
	cv::Size resolution;
	read_config["Resolution_projector"] >> resolution;
	// read fullscreen_projector from yml using OpenCV FileStorage
	bool fullscreen;
	read_config["Fullscreen_projector"] >> fullscreen;
	// read camera meter from yml using OpenCV FileStorage
	float meter;
	read_config["Meter_camera"] >> meter;

	return new ProjectorConfiguration(
		resolution,
		fullscreen,
		meter,
		Configuration::read(read_config, "Maximum_FPS_scene")
	);
}

ProjectorConfiguration* ProjectorConfiguration::createFromNode(cv::FileStorage read_config, cv::Size resolution) {
	// read fullscreenfrom yml using OpenCV FileStorage; default if not existing
	bool fullscreen;
	if (read_config["Fullscreen_projector"].isNone()) {
		fullscreen = ProjectorConfiguration::DEFAULT_FULLSCREEN;
	} else {
		read_config["Fullscreen_projector"] >> fullscreen;
	}
	// read meter from yml using OpenCV FileStorage; default if not existing
	float meter;
	if (read_config["Meter_camera"].isNone()) {
		meter = ProjectorConfiguration::DEFAULT_METER;
	} else {
		read_config["Meter_projector"] >> meter;
	}
 	
	// create initial ProjectorConfiguration based on configuration, arguments and defaults
	return new ProjectorConfiguration(
		resolution,
		fullscreen,
		meter,
		Configuration::create(read_config, "Maximum_FPS_scene", ProjectorConfiguration::DEFAULT_MAXIMUM_FPS_SCENE)
	);
}

void ProjectorConfiguration::writeNode(cv::FileStorage write_config) const {
	write_config << "Resolution_projector"              <<       this->resolution;
	write_config << "Fullscreen_projector"              <<       this->fullscreen;
	write_config << "Meter_projector"                   <<       this->meter;
	write_config << "Maximum_FPS_scene"                 << (int) this->maximum_fps_scene;
}

bool ProjectorConfiguration::getFullscreen() const {
	return this->fullscreen;
}
const cv::Size ProjectorConfiguration::getResolution() const {
	return this->resolution;
}
void ProjectorConfiguration::setMeter(float meter) {
	this->meter = meter;
}
const float ProjectorConfiguration::getMeter() const {
	return this->meter;
}
void ProjectorConfiguration::setMaximumFpsScene(const unsigned int maximum_fps_scene) {
	this->maximum_fps_scene = maximum_fps_scene;
}
const unsigned int ProjectorConfiguration::getMaximumFpsScene() const {
	return this->maximum_fps_scene;
}
