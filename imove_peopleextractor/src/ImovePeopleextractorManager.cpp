#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <boost/interprocess/offset_ptr.hpp>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib> //std::system

#include "ImovePeopleextractorManager.hpp"

#include "OpenCVUtil.hpp"
#include "Interface/Person.h"
#include "Windows/FrameWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"

//#include <scene_interface/ExtractedpeopleQueue.hpp>
//#include <scene_interface/Person.hpp>
//#include <scene_interface/Vector2.hpp>
#include "../../scene_interface/src/ExtractedpeopleQueue.hpp"
#include "../../scene_interface/src/Person.hpp"
#include "../../scene_interface/src/Vector2.hpp"

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

	// link to shared memory
	//Open the managed segment
	boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, "MySharedMemory");

	//Find the vector using the c-string name
	boost::interprocess::offset_ptr<scene_interface::ExtractedpeopleQueue> extractedpeople_queue = segment.find<scene_interface::ExtractedpeopleQueue>("root").first;

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

		//communicate to other process
		//Initialize shared memory STL-compatible allocator
    const scene_interface::PersonSMA person_sma(segment.get_segment_manager());

		//Construct a vector named "MyVector" in shared memory with argument alloc_inst
    boost::interprocess::offset_ptr<scene_interface::PersonVector> si_detected_people = segment.construct<scene_interface::PersonVector>(boost::interprocess::anonymous_instance)(person_sma);
		for (Person person : detected_people) {
			// convert person location
			//communicate to other process
			//Initialize shared memory STL-compatible allocator
    	const scene_interface::Vector2SMA vector2_sma(segment.get_segment_manager());
			Vector2 location = person.getLocation();
			boost::interprocess::offset_ptr<scene_interface::Vector2Vector> locations = segment.construct<scene_interface::Vector2Vector>(boost::interprocess::anonymous_instance)(vector2_sma);
			locations->push_back(
				segment.construct<scene_interface::Vector2>(boost::interprocess::anonymous_instance)(location.x, location.y)
			);
			
			// convert person type
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
			}
			std::cerr << "id: " << person.getId() << std::endl;
			boost::interprocess::offset_ptr<scene_interface::Person> si_person = segment.construct<scene_interface::Person>(boost::interprocess::anonymous_instance)(
				locations,
				person_type,
				person.getId()
			);
			si_detected_people->push_back(si_person);
		}
		extractedpeople_queue->push(
			si_detected_people
		);
	}

	// safe release video capture
	video_capture.release();
}
