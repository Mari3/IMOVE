#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>
#include <queue>

#include "./OpenCVUtil.hpp"
#include "../../imove/src/calibration/Calibration.hpp"
#include "./Windows/Projection.hpp"
#include "./Windows/Projector.hpp"
#include "./Windows/CalibrationProjection.hpp"
#include "./Windows/CalibrationMeter.hpp"
#include "./Windows/EliminateProjection.hpp"



// Default configuration parameters if not given
unsigned DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY = 5;
double DEFAULT_PROJECTOR_BACKGROUND_LIGHT = 39;
float DEFAULT_METER = 100.f;


// arguments
unsigned int CONFIGPATH_ARGN = 1;
unsigned int CAMERADEVICE_ARGN = 2;
unsigned int CALIBRATIONPATH_ARGN = 3;

const signed int NOKEY_ANYKEY = -1;

Calibration* calibration = NULL;
cv::Mat camera_projector_transformation;



// create calibration configuration based on arguments and configuration and user input in projection, meter and projection elimination windows
int main(int argc, char* argv[]) {
	if (argc != 4) {
		std::cout << "Usage: <path to configuration file> <int camera device> <path to calibration projection video file>" << std::endl;
		return EXIT_SUCCESS;
	}
	
	// read config if property is not set, use default
	cv::FileStorage read_config;
	char* configpath = argv[CONFIGPATH_ARGN];
	read_config.open(configpath, cv::FileStorage::READ);

	unsigned int frames_projector_camera_delay;
	if (read_config["Frames_projector_camera_delay"].isNone()) {
		frames_projector_camera_delay = DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY;
	} else {
		signed int int_frames_projector_camera_delay;
		read_config["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
		if (int_frames_projector_camera_delay < 0) {
			frames_projector_camera_delay = 0;
		} else {
			frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
		}
	}
	double projector_background_light;
	if (read_config["Projector_background_light"].isNone()) {
		projector_background_light = DEFAULT_PROJECTOR_BACKGROUND_LIGHT;
	} else {
		read_config["Projector_background_light"] >> projector_background_light;
	}
	float meter;
	if (read_config["Meter"].isNone()) {
		meter = DEFAULT_METER;
	} else {
		read_config["Meter"] >> meter;
	}
 
	cv::Mat frame_projector;
	cv::VideoCapture projector_videoreader(argv[CALIBRATIONPATH_ARGN]);
	
	cv::Mat frame_camera;
	int cameradevice = std::stoi(argv[CAMERADEVICE_ARGN]);
	cv::VideoCapture camera_videoreader(cameradevice);
	camera_videoreader.set(CV_CAP_PROP_AUTOFOCUS, 0);
	
	const cv::Size resolution_projector(projector_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), projector_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	const cv::Size resolution_camera(camera_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), camera_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	if (read_config["Camera_projector_transformation"].isNone()) {
		cv::Point2f* coordinate_corners_projector = new cv::Point2f[CalibrationProjectionWindow::REQUIRED_CORNERS];
		coordinate_corners_projector[0] = cv::Point2f(        OpenCVUtil::ORIGIN2D.x,          OpenCVUtil::ORIGIN2D.y);
		coordinate_corners_projector[1] = cv::Point2f(resolution_projector.width - 1,          OpenCVUtil::ORIGIN2D.y);
		coordinate_corners_projector[2] = cv::Point2f(		  	OpenCVUtil::ORIGIN2D.x, resolution_projector.height - 1);
		coordinate_corners_projector[3] = cv::Point2f(resolution_projector.width - 1, resolution_projector.height - 1);
		cv::Size resolution_camera(camera_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), camera_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
		cv::Point2f* coordinate_corners_camera = new cv::Point2f[CalibrationProjectionWindow::REQUIRED_CORNERS];
		coordinate_corners_camera[0]   = cv::Point2f(     OpenCVUtil::ORIGIN2D.x,       OpenCVUtil::ORIGIN2D.y);
		coordinate_corners_camera[1]   = cv::Point2f(resolution_camera.width - 1,       OpenCVUtil::ORIGIN2D.y);
		coordinate_corners_camera[2]   = cv::Point2f(			OpenCVUtil::ORIGIN2D.x, resolution_camera.height - 1);
		coordinate_corners_camera[3]   = cv::Point2f(resolution_camera.width - 1, resolution_camera.height - 1);
		
		camera_projector_transformation = cv::getPerspectiveTransform(
			coordinate_corners_camera,
			coordinate_corners_projector
		);
	} else {
		read_config["Camera_projector_transformation"] >> camera_projector_transformation;
	}
	read_config.release();
	
 	// create initial calibration based on configuration, arguments and defaults
	calibration = new Calibration(resolution_projector, camera_projector_transformation, frames_projector_camera_delay, projector_background_light);
	
	// setup calibration windows
	ProjectorWindow projector_window(cv::Size(0, 0));
	CalibrationProjectionWindow calibrationprojection_window(cv::Point2i(300, 0), calibration, resolution_projector);
	CalibrationMeterWindow calibrationmeter_window(cv::Point2i(600, 0), calibration, meter);
	EliminateProjectionWindow eliminateprojection_window(cv::Size(900, 0), calibration, projector_background_light, frames_projector_camera_delay);
	ProjectionWindow projection_window(cv::Size(1200, 0), calibration);

	
	while (cv::waitKey(1) == NOKEY_ANYKEY && projector_videoreader.read(frame_projector) && camera_videoreader.read(frame_camera)) {

		calibration->feedFrameProjector(frame_projector);
		eliminateprojection_window.drawImage(frame_camera);

		projector_window.drawImage(frame_projector);
		projection_window.drawImage(eliminateprojection_window.getClonedImage());
		
		calibrationprojection_window.drawImage(frame_camera.clone());
		calibrationmeter_window.drawImage(frame_camera.clone());
	}

	projector_videoreader.release();
	camera_videoreader.release();
	
	// write configuration based on calibration
	cv::FileStorage write_config(configpath, cv::FileStorage::WRITE);
	write_config << "Camera_device" << cameradevice;
	write_config << "Resolution_camera" << resolution_camera;
	write_config << "Resolution_projector" << resolution_projector;
	write_config << "Camera_projector_transformation" << calibration->getCameraProjectorTransformation();
	write_config << "Frames_projector_camera_delay" << (int) frames_projector_camera_delay;
	write_config << "Projector_background_light" << projector_background_light;
	write_config << "Meter" << calibrationmeter_window.getMeter();
	write_config.release();
	
	return EXIT_SUCCESS;
}
