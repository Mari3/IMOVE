#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

#include "ImovePeopleextractorManager.hpp"

#include "OpenCVUtil.hpp"
#include "../../scene_interface/src/Person.h"
#include "../../scene_interface/src/Vector2.h"
#include "Windows/PeopleextractorWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"
#include "Windows/ImageWindow.hpp"
#include "../../scene_interface_sma/src/SharedMemory.hpp"

ImovePeopleextractorManager::ImovePeopleextractorManager(Calibration* calibration) {
	this->calibration = calibration;

	// setup people extractor
	this->people_extractor = new PeopleExtractor(this->calibration->getResolutionCamera(), this->calibration->getMeter(), 210);

	//Open the managed segment
	this->segment = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, scene_interface_sma::NAME_SHARED_MEMORY);
	// Get the extracted people queue in the segment
	this->si_people_queue = this->segment->find<scene_interface_sma::PeopleQueue>(scene_interface_sma::NAME_PEOPLE_QUEUE).first;
	// Get the people extractor scene frames queue in the segment
	this->pi_sceneframe_queue = this->segment->find<peopleextractor_interface_sma::SceneframeQueue>(peopleextractor_interface_sma::NAME_SCENEFRAME_QUEUE).first;
	this->running = this->segment->find<Running>(NAME_SHARED_MEMORY_RUNNING).first;
}

void ImovePeopleextractorManager::receiveSceneFrameAndFeedProjectionThread(ImovePeopleextractorManager* imove_peopleextractor_manager) {
	while (imove_peopleextractor_manager->still_run_receive_scene_frames) {
		imove_peopleextractor_manager->receiveSceneFrameAndFeedProjection();
	}
}

void ImovePeopleextractorManager::run() {
	// debug windows
	PeopleextractorWindow window_peopleextractor(cv::Size(0, 0), this->people_extractor);
	DetectedPeopleCameraWindow detectedpeople_camera_window(cv::Size(300, 0));
	ImageWindow eliminatedprojection_camera_window("Eliminated projection camera frame", cv::Size(600, 0));
	DetectedPeopleProjectionWindow detectedpeople_projection_window(cv::Size(900, 0));

	// setup clock
	sf::Clock clock;

	// setup camera
	cv::VideoCapture video_capture(this->calibration->getCameraDevice());

	std::thread receive_scene_frame_and_feed_projection_thread(ImovePeopleextractorManager::receiveSceneFrameAndFeedProjectionThread, this);

	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::Mat detectpeople_frame;
	std::vector<scene_interface::Person> extractedpeople;
	this->still_run_receive_scene_frames = true;
	// while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && video_capture.read(frame_camera) && this->running->running) {
		// debug projection frame
		this->calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);
		
		// delay for syncing processing projection elimination
		for (unsigned int i = 0; i < this->calibration->getIterationsDelayPeopleextracting(); ++i) {}
		// eliminate projection from camera frame
		cv::Mat frame_eliminatedprojection;
		this->calibration->eliminateProjectionFeedbackFromFrameCamera(frame_eliminatedprojection, frame_camera);
		eliminatedprojection_camera_window.drawImage(frame_eliminatedprojection);

		// extract people from camera frame
		detectpeople_frame = frame_eliminatedprojection.clone();
		extractedpeople = this->people_extractor->extractPeople(detectpeople_frame);
		window_peopleextractor.drawFrame();

		// draw detected people camera image
		detectedpeople_camera_window.drawImage(frame_camera, extractedpeople);

		// change extrated people to projector location from camera location
		this->calibration->changeProjectorFromCameraLocationPerson(extractedpeople);

		// draw detected people projection image
		detectedpeople_projection_window.drawImage(frame_projection, extractedpeople);
		
		// send extracted people via shared memory to scene
		this->sendExtractedpeople(extractedpeople);
	}

	// make other thread stop
	this->still_run_receive_scene_frames = false;
	receive_scene_frame_and_feed_projection_thread.join();

	// safe release video capture
	video_capture.release();
}

void ImovePeopleextractorManager::sendExtractedpeople(std::vector<scene_interface::Person> extractedpeople) {
	//Initialize shared memory STL-compatible allocator
	scene_interface_sma::PeopleSMA people_sma = scene_interface_sma::PeopleSMA((*this->segment).get_segment_manager());
	
	// create shared memory vector of extracted people
  boost::interprocess::offset_ptr<scene_interface_sma::People> si_people = this->segment->construct<scene_interface_sma::People>(boost::interprocess::anonymous_instance)(people_sma);

	for (scene_interface::Person person : extractedpeople) {
		//Initialize shared memory STL-compatible allocator
		scene_interface_sma::LocationsSMA locations_sma(this->segment->get_segment_manager());
		scene_interface::Vector2 location = person.getLocation();
		// create shared memory vector of locations
		boost::interprocess::offset_ptr<scene_interface_sma::Locations> locations = this->segment->construct<scene_interface_sma::Locations>(boost::interprocess::anonymous_instance)(locations_sma);
		// put shared memory allocated location in shared memory allocated vector of locations
		locations->push_back(
			this->segment->construct<scene_interface_sma::Location>(boost::interprocess::anonymous_instance)(location.x, location.y)
		);
		
		// create shared memory allocated person type from person type
		scene_interface_sma::PersonType person_type;
		switch (person.type) {
			case scene_interface::PersonType::Bystander:
				person_type = scene_interface_sma::PersonType::Bystander;
				break;
			case scene_interface::PersonType::Passerthrough:
				person_type = scene_interface_sma::PersonType::Passerthrough;
				break;
			case scene_interface::PersonType::Participant:
				person_type = scene_interface_sma::PersonType::Participant;
				break;
			case scene_interface::PersonType::None:
				person_type = scene_interface_sma::PersonType::None;
				break;
			case scene_interface::PersonType::StandingStill:
				person_type = scene_interface_sma::PersonType::StandingStill;
				break;
		}
		// put shared memory allocated extracted person in shared memory allocated vector of extracted people
		si_people->push_back(
			this->segment->construct<scene_interface_sma::Person>(boost::interprocess::anonymous_instance)(
				locations,
				person_type,
				person.getId()
			)
		);
	}

	// push shared memory allocated extracted people on the queue
	this->si_people_queue->push_back(
		si_people
	);
}

void ImovePeopleextractorManager::receiveSceneFrameAndFeedProjection() {
	// pop all frames which we are not able to process so fast
	while (this->pi_sceneframe_queue->size() > 2) {
		this->pi_sceneframe_queue->pop_front();
	}
	// when scene frame available
	if (!this->pi_sceneframe_queue->empty()) {
		// convert from sma to opencv mat
		boost::interprocess::offset_ptr<peopleextractor_interface_sma::Image> pi_sceneframe = this->pi_sceneframe_queue->front();
		cv::Mat cv_sceneframe = cv::Mat::zeros(pi_sceneframe->getHeight(), pi_sceneframe->getWidth(), CV_8UC3);
		for (unsigned int x = 0; x < pi_sceneframe->getWidth(); ++x) {
			for (unsigned int y = 0; y < pi_sceneframe->getHeight(); ++y) {
				cv_sceneframe.at<cv::Vec3b>(y, x) = cv::Vec3b(
					pi_sceneframe->getBlue(x, y),
					pi_sceneframe->getGreen(x, y),
					pi_sceneframe->getRed(x, y)
				);
			}
		}
		cv::Mat cv_sceneframe_resize;
		cv::resize(cv_sceneframe, cv_sceneframe_resize, cv::Size(pi_sceneframe->getWidth() * this->calibration->getFactorResizeCaptureScene(), pi_sceneframe->getHeight() * this->calibration->getFactorResizeCaptureScene()));
		// feed opencv image to calibration
		this->calibration->feedFrameProjector(cv_sceneframe_resize);
		// remove from queue
		this->pi_sceneframe_queue->pop_front();
	}
}
