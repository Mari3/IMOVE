#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/persistence.hpp>
 
#include <iostream>
#include <string>
#include <queue>

#include "../../imove/src/OpenCVUtil.hpp"
#include "../../imove/src/calibration/Calibration.hpp"
#include "./Windows/Projection.hpp"
#include "./Windows/Projector.hpp"
#include "./Windows/CalibrationProjection.hpp"
#include "./Windows/CalibrationMeter.hpp"
#include "./Windows/EliminateProjection.hpp"


// arguments
unsigned int CONFIGPATH_ARGN = 1;
unsigned int CAMERADEVICE_ARGN = 2;
unsigned int WIDTH_RESOLUTION_ARGN = 3;
unsigned int HEIGHT_RESOLUTION_ARGN = 4;

const signed int NOKEY_ANYKEY = -1;


// create calibration configuration based on arguments and configuration and user input in projection, meter and projection elimination windows
int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cout << "Usage: <path to configuration file> <int camera device> <resolution projector width> <resolution projector height>" << std::endl;
		return EXIT_SUCCESS;
	}

	const char* configurationfilepath_calibration = argv[CONFIGPATH_ARGN];
	// read config if property is not set, use default
	Calibration* calibration = Calibration::createFromFile(
		configurationfilepath_calibration,
		std::stoi(argv[CAMERADEVICE_ARGN]),
		cv::Size(
			std::stoi(argv[WIDTH_RESOLUTION_ARGN]),
			std::stoi(argv[HEIGHT_RESOLUTION_ARGN])
		)
	);
	
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
	while (cv::waitKey(1) == NOKEY_ANYKEY && camera_videoreader.read(frame_camera)) {
		frame_projector = cv::Mat::zeros(calibration->getResolutionProjector(), CV_8UC3);
		projector_window.drawImage(frame_projector);
		calibration->feedFrameProjector(projector_window.getClonedImage());
		eliminateprojection_window.drawImage(frame_camera);
		
		projection_window.drawImage(eliminateprojection_window.getClonedImage());
		
		calibrationprojection_window.drawImage(frame_camera.clone());
		calibrationmeter_window.drawImage(frame_camera.clone());
	}

	camera_videoreader.release();
	
	calibration->writeFile(configurationfilepath_calibration);
	
	return EXIT_SUCCESS;
}
