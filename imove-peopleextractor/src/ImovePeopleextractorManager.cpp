#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>

#include "ImovePeopleextractorManager.hpp"

#include "OpenCVUtil.hpp"
#include "Interface/Person.h"
#include "Windows/FrameWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"

ImovePeopleextractorManager::ImovePeopleextractorManager(Calibration* calibration) {
	this->calibration = calibration;

	// setup people extractor
	this->people_extractor = new PeopleExtractor(this->calibration->getResolutionCamera(), this->calibration->getMeter(), 216);
}

void ImovePeopleextractorManager::run() {
	// debug windows
	FrameWindow window_frame(cv::Size(0, 0));
	DetectedPeopleCameraWindow detectedpeople_camera_window(cv::Size(500, 0));
	DetectedPeopleProjectionWindow detectedpeople_projection_window(cv::Size(1000, 0));

	// setup clock
	sf::Clock clock;

	// setup camera
	cv::VideoCapture video_capture(this->calibration->getCameraDevice());

	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::Mat detectpeople_frame;
	vector<Person> detected_people;
	// while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && video_capture.read(frame_camera)) {
		// debug projection frame
		this->calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);

		// extract people from camera frame
		detectpeople_frame = frame_camera.clone();
	 	detected_people = people_extractor->extractPeople(detectpeople_frame);
		people_extractor->displayResults();

		// draw detected people camera image
		detectedpeople_camera_window.drawImage(frame_camera, detected_people);

		// change extrated people to projector location from camera location
		calibration->changeProjectorFromCameraLocationPerson(detected_people);

		// draw detected people projection image
		detectedpeople_projection_window.drawImage(frame_projection, detected_people);

		//todo communicate to other process
	}

	// safe release video capture
	video_capture.release();
}
