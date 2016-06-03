#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <boost/interprocess/offset_ptr.hpp>

#include "ImovePeopleextractorManager.hpp"

#include "OpenCVUtil.hpp"
#include "Interface/Person.h"
#include "Windows/FrameWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"

//#include <scene_interface/SharedMemory.hpp>
//#include <scene_interface/Person.hpp>
//#include <scene_interface/Vector2.hpp>
#include "../../scene_interface/src/SharedMemory.hpp"
#include "../../scene_interface/src/Person.hpp"
#include "../../scene_interface/src/Vector2.hpp"

ImovePeopleextractorManager::ImovePeopleextractorManager(Calibration* calibration) {
	this->calibration = calibration;

	// setup people extractor
	this->people_extractor = new PeopleExtractor(this->calibration->getResolutionCamera(), this->calibration->getMeter(), 216);

	//Open the managed segment
	this->segment = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, scene_interface::NAME_SHARED_MEMORY);
	// Get the extracted people vector in the segment
	this->extractedpeople_queue = this->segment->find<scene_interface::ExtractedpeopleQueue>(scene_interface::NAME_EXTRACTEDPEOPLE_QUEUE).first;
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
	vector<Person> extractedpeople;
	// while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY && video_capture.read(frame_camera)) {
		// debug projection frame
		this->calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);

		// extract people from camera frame
		detectpeople_frame = frame_camera.clone();
		extractedpeople = people_extractor->extractPeople(detectpeople_frame);
		people_extractor->displayResults();

		// draw detected people camera image
		detectedpeople_camera_window.drawImage(frame_camera, extractedpeople);

		// change extrated people to projector location from camera location
		calibration->changeProjectorFromCameraLocationPerson(extractedpeople);

		// draw detected people projection image
		detectedpeople_projection_window.drawImage(frame_projection, extractedpeople);
		
		// send extracted people via shared memory to scene
		sendExtractedpeople(extractedpeople);
	}

	// safe release video capture
	video_capture.release();
}

void ImovePeopleextractorManager::sendExtractedpeople(std::vector<Person> extractedpeople) {
	//Initialize shared memory STL-compatible allocator
	scene_interface::PersonSMA person_sma = scene_interface::PersonSMA((*this->segment).get_segment_manager());
	
	// create shared memory vector of extracted people
  boost::interprocess::offset_ptr<scene_interface::PersonVector> si_extractedpeople = this->segment->construct<scene_interface::PersonVector>(boost::interprocess::anonymous_instance)(person_sma);

	for (Person person : extractedpeople) {
		//Initialize shared memory STL-compatible allocator
		scene_interface::Vector2SMA vector2_sma(this->segment->get_segment_manager());
		Vector2 location = person.getLocation();
		// create shared memory vector of locations
		boost::interprocess::offset_ptr<scene_interface::Vector2Vector> locations = this->segment->construct<scene_interface::Vector2Vector>(boost::interprocess::anonymous_instance)(vector2_sma);
		// put shared memory allocated location in shared memory allocated vector of locations
		locations->push_back(
			this->segment->construct<scene_interface::Vector2>(boost::interprocess::anonymous_instance)(location.x, location.y)
		);
		
		// create shared memory allocated person type from person type
		scene_interface::PersonType person_type;
		switch (person.type) {
			case scene_interface::PersonType::Bystander:
				person_type = scene_interface::PersonType::Bystander;
				break;
			case Passerthrough:
				person_type = scene_interface::PersonType::Passerthrough;
				break;
			case Participant:
				person_type = scene_interface::PersonType::Participant;
				break;
			case None:
				person_type = scene_interface::PersonType::None;
				break;
			case StandingStill:
				person_type = scene_interface::PersonType::StandingStill;
				break;
		}
		// put shared memory allocated extracted person in shared memory allocated vector of extracted people
		si_extractedpeople->push_back(
			this->segment->construct<scene_interface::Person>(boost::interprocess::anonymous_instance)(
				locations,
				person_type,
				person.getId()
			)
		);
	}

	// push shared memory allocated extracted people on the queue
	this->extractedpeople_queue->push(
		si_extractedpeople
	);
}
