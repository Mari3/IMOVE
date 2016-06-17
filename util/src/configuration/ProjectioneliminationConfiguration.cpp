#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/persistence.hpp>
#include <assert.h>

#include "ProjectioneliminationConfiguration.hpp"

ProjectioneliminationConfiguration::ProjectioneliminationConfiguration(unsigned int frames_projector_camera_delay, float projector_background_light, unsigned int fps_capture_scene, unsigned int iterations_delay_peopleextracting, unsigned int factor_resize_capture_scene) :
	frames_projector_camera_delay(frames_projector_camera_delay),
	projector_background_light(projector_background_light),
	fps_capture_scene(fps_capture_scene),
	iterations_delay_peopleextracting(iterations_delay_peopleextracting),
	factor_resize_capture_scene(factor_resize_capture_scene)
{}

ProjectioneliminationConfiguration* ProjectioneliminationConfiguration::readNode(cv::FileStorage read_config) {
	float projector_background_light;
	read_config["Projector_background_light"] >> projector_background_light;

	return new ProjectioneliminationConfiguration(
		Configuration::read(read_config, "Frames_projector_camera_delay"),
		projector_background_light,
		Configuration::read(read_config, "FPS_capture_scene"),
		Configuration::read(read_config, "Iterations_delay_peopleextracting"),
		Configuration::read(read_config, "Factor_resize_capture_scene")
	);
}

ProjectioneliminationConfiguration* ProjectioneliminationConfiguration::createFromNode(cv::FileStorage read_config) {
	// read projector_background_light from yml using OpenCV FileStorage; default if not existing
	float projector_background_light;
	if (read_config["Projector_background_light"].isNone()) {
		projector_background_light = ProjectioneliminationConfiguration::DEFAULT_PROJECTOR_BACKGROUND_LIGHT;
	} else {
		read_config["Projector_background_light"] >> projector_background_light;
	}
 
 	// create initial ProjectioneliminationConfiguration based on configuration, arguments and defaults
	return new ProjectioneliminationConfiguration(
		Configuration::create(read_config, "Frames_projector_camera_delay", ProjectioneliminationConfiguration::DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY),
		projector_background_light,
		Configuration::create(read_config, "FPS_capture_scene", ProjectioneliminationConfiguration::DEFAULT_FPS_CAPTURE_SCENE),
		Configuration::create(read_config, "Iterations_delay_peopleextracting", ProjectioneliminationConfiguration::DEFAULT_ITERATIONS_DELAY_PEOPLEEXTRACTING),
		Configuration::create(read_config, "Factor_resize_capture_scene", ProjectioneliminationConfiguration::DEFAULT_FACTOR_RESIZE_CAPTURE_SCENE)
	);
}

void ProjectioneliminationConfiguration::writeNode(cv::FileStorage write_config) const {
	write_config << "Frames_projector_camera_delay"     << (int) this->frames_projector_camera_delay;
	write_config << "Projector_background_light"        <<       this->projector_background_light;
	write_config << "FPS_capture_scene"                 << (int) this->fps_capture_scene;
	write_config << "Iterations_delay_peopleextracting" << (int) this->iterations_delay_peopleextracting;
	write_config << "Factor_resize_capture_scene"       << (int) this->factor_resize_capture_scene;
}

unsigned int ProjectioneliminationConfiguration::getFramesProjectorCameraDelay() const {
	return this->frames_projector_camera_delay;
}
void ProjectioneliminationConfiguration::setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay) {
	this->frames_projector_camera_delay = frames_projector_camera_delay;
}
float ProjectioneliminationConfiguration::getProjectorBackgroundLight() const {
	return this->projector_background_light;
}
void ProjectioneliminationConfiguration::setProjectorBackgroundLight(float projector_background_light) {
	this->projector_background_light = projector_background_light;
}
void ProjectioneliminationConfiguration::setFpsCaptureScene(const unsigned int fps_capture_scene) {
	this->fps_capture_scene = fps_capture_scene;
}
const unsigned int ProjectioneliminationConfiguration::getFpsCaptureScene() const {
	return this->fps_capture_scene;
}
void ProjectioneliminationConfiguration::setIterationsDelayPeopleextracting(unsigned int iterations_delay_peopleextracting) {
	this->iterations_delay_peopleextracting = iterations_delay_peopleextracting;
}
const unsigned int ProjectioneliminationConfiguration::getIterationsDelayPeopleextracting() const {
	return this->iterations_delay_peopleextracting;
}
void ProjectioneliminationConfiguration::setFactorResizeCaptureScene(unsigned int factor_resize_capture_scene) {
	this->factor_resize_capture_scene = factor_resize_capture_scene;
}
const unsigned int ProjectioneliminationConfiguration::getFactorResizeCaptureScene() const {
	return this->factor_resize_capture_scene;
}
