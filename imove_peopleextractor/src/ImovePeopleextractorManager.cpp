#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>

#include "ImovePeopleextractorManager.hpp"

#include "OpenCVUtil.hpp"
#include "../../scene_interface/src/Person.h"
#include "../../scene_interface/src/Vector2.h"
#include "Windows/FrameWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"

//#include <scene_interface_sma/SharedMemory.hpp>
//#include <scene_interface_sma/Person.hpp>
//#include <scene_interface_sma/Vector2.hpp>
#include "../../scene_interface_sma/src/SharedMemory.hpp"
#include "../../scene_interface_sma/src/Person.hpp"
#include "../../scene_interface_sma/src/Vector2.hpp"

ImovePeopleextractorManager::ImovePeopleextractorManager(Calibration* calibration) {
	this->calibration = calibration;

	// setup people extractor
	this->people_extractor = new PeopleExtractor(this->calibration->getResolutionCamera(), this->calibration->getMeter(), 216, this->calibration->getProjection());

	//Open the managed segment
	this->segment = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, scene_interface_sma::NAME_SHARED_MEMORY);
	// Get the extracted people vector in the segment
	this->extractedpeople_queue = this->segment->find<scene_interface_sma::ExtractedpeopleQueue>(scene_interface_sma::NAME_EXTRACTEDPEOPLE_QUEUE).first;
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
	std::vector<scene_interface::Person> people_camera;
	// while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && video_capture.read(frame_camera)) {
		// debug projection frame
		this->calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);

		// extract people from camera frame
		detectpeople_frame = frame_camera.clone();
		people_camera = people_extractor->extractPeople(detectpeople_frame);
		people_extractor->displayResults();

		// draw detected people camera image
		detectedpeople_camera_window.drawImage(frame_camera, people_camera);

		// change extrated people to projector location from camera location
		const std::vector<scene_interface::Person> people_projector = calibration->createPeopleProjectorFromPeopleCamera(people_camera);

		// draw detected people projection image
		detectedpeople_projection_window.drawImage(frame_projection, people_projector);
		
		// send extracted people via shared memory to scene
		sendExtractedpeople(people_projector);
	}

	// safe release video capture
	video_capture.release();
}

void ImovePeopleextractorManager::sendExtractedpeople(const std::vector<scene_interface::Person> extractedpeople) {
	//Initialize shared memory STL-compatible allocator
	scene_interface_sma::PersonSMA person_sma = scene_interface_sma::PersonSMA((*this->segment).get_segment_manager());
	
	// create shared memory vector of extracted people
  boost::interprocess::offset_ptr<scene_interface_sma::PersonVector> si_extractedpeople = this->segment->construct<scene_interface_sma::PersonVector>(boost::interprocess::anonymous_instance)(person_sma);

	for (scene_interface::Person person : extractedpeople) {
		//Initialize shared memory STL-compatible allocator
		scene_interface_sma::Vector2SMA vector2_sma(this->segment->get_segment_manager());
		scene_interface::Vector2 location = person.getLocation();
		// create shared memory vector of locations
		boost::interprocess::offset_ptr<scene_interface_sma::Vector2Vector> locations = this->segment->construct<scene_interface_sma::Vector2Vector>(boost::interprocess::anonymous_instance)(vector2_sma);
		// put shared memory allocated location in shared memory allocated vector of locations
		locations->push_back(
			this->segment->construct<scene_interface_sma::Vector2>(boost::interprocess::anonymous_instance)(location.x, location.y)
		);
		
		// create shared memory allocated person type from person type
		scene_interface_sma::Person::PersonType person_type;
		switch (person.getPersonType()) {
			case scene_interface::Person::PersonType::Bystander:
				person_type = scene_interface_sma::Person::PersonType::Bystander;
				break;
			case scene_interface::Person::PersonType::Passerthrough:
				person_type = scene_interface_sma::Person::PersonType::Passerthrough;
				break;
			case scene_interface::Person::PersonType::Participant:
				person_type = scene_interface_sma::Person::PersonType::Participant;
				break;
			case scene_interface::Person::PersonType::None:
				person_type = scene_interface_sma::Person::PersonType::None;
				break;
		}
		// create shared memory allocated movement type from movement type
		scene_interface_sma::Person::MovementType movement_type;
		switch (person.getMovementType()) {
			case scene_interface::Person::MovementType::StandingStill:
				movement_type = scene_interface_sma::Person::MovementType::StandingStill;
				break;
			case scene_interface::Person::MovementType::Moving:
				movement_type = scene_interface_sma::Person::MovementType::Moving;
				break;
		}
		// put shared memory allocated extracted person in shared memory allocated vector of extracted people
		si_extractedpeople->push_back(
			this->segment->construct<scene_interface_sma::Person>(boost::interprocess::anonymous_instance)(
				locations,
				person_type,
				movement_type,
				person.getId()
			)
		);
	}

	// push shared memory allocated extracted people on the queue
	this->extractedpeople_queue->push(
		si_extractedpeople
	);
}
