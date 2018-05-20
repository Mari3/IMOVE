#include <opencv2/opencv.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

#include "ImovePeopleextractorManager.hpp"

#include "../../util/src/configuration/ImoveConfiguration.hpp"
#include "../../util/src/OpenCVUtil.hpp"
#include "../../scene_interface/src/People.h"
#include "../../util/src/Vector2.h"
#include "Windows/PeopleextractorWindow.hpp"
#include "Windows/DetectedPeopleCameraWindow.hpp"
#include "Windows/DetectedPeopleProjectionWindow.hpp"
#include "Windows/ImageWindow.hpp"
#include "../../scene_interface_sma/src/SharedMemory.hpp"

ImovePeopleextractorManager::ImovePeopleextractorManager(ImoveConfiguration* calibration) : calibration(calibration), projection(Projection(calibration)) {
	CameraConfiguration* camera_configuration = this->calibration->getCameraConfiguration();
	// setup people extractor
	//this->people_extractor = new PeopleExtractor(camera_configuration->getResolution(), camera_configuration->getMeter(), 216, camera_configuration->getProjection().createReorientedTopLeftBoundary());
	this->people_extractor = new PeopleExtractor(camera_configuration);

	//Open the managed segment
	this->segment = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, scene_interface_sma::NAME_SHARED_MEMORY);
	// Get the extracted people queue in the segment
	this->si_people_queue = this->segment->find<scene_interface_sma::PeopleQueue>(scene_interface_sma::NAME_PEOPLE_QUEUE).first;
	// Get the people extractor scene frames queue in the segment
	this->pi_sceneframe_queue = this->segment->find<peopleextractor_interface_sma::SceneframeQueue>(peopleextractor_interface_sma::NAME_SCENEFRAME_QUEUE).first;
	this->running = this->segment->find<Running>(NAME_SHARED_MEMORY_RUNNING).first;
}

void ImovePeopleextractorManager::receiveSceneFrameAndFeedProjectionThread(ImovePeopleextractorManager* imove_peopleextractor_manager) {
	imove_peopleextractor_manager->receiveSceneFrameAndFeedProjection();
}

void ImovePeopleextractorManager::run() {
	const unsigned int& iterations_delay_peopleextracting = this->calibration->getProjectioneliminationConfiguration()->getIterationsDelayPeopleextracting();

	// debug windows
	PeopleextractorWindow* window_peopleextractor;
	DetectedPeopleCameraWindow* detectedpeople_camera_window;
	ImageWindow* eliminatedprojection_camera_window;
	DetectedPeopleProjectionWindow* detectedpeople_projection_window;
	if (this->calibration->getDebugMode()) {
		float width_resolution_projector = this->calibration->getProjectorConfiguration()->getResolution().width;
		 window_peopleextractor = new PeopleextractorWindow(
			cv::Point2i(width_resolution_projector, 0),
			cv::Size(600, 600),
			this->people_extractor
		);
		detectedpeople_camera_window = new DetectedPeopleCameraWindow(
			cv::Point2i(width_resolution_projector + 600, 0),
			cv::Size(600, 600)
		);
		eliminatedprojection_camera_window = new ImageWindow(
			"Eliminated projection camera frame",
			cv::Point2i(width_resolution_projector, 600),
			cv::Size(300, 300)
		);
		detectedpeople_projection_window = new DetectedPeopleProjectionWindow(
			cv::Point2i(width_resolution_projector + 300, 600),
			cv::Size(300, 300)
		);
	}

	// setup camera
	cv::VideoCapture video_capture(this->calibration->getCameraConfiguration()->getDeviceid());

	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::Mat detectpeople_frame;
	scene_interface::People people_camera;
	CameraConfiguration* camera_configuration = this->calibration->getCameraConfiguration();
	// while no key pressed
	while (video_capture.read(frame_camera) && this->running->running) {
		cv::resize(frame_camera, frame_camera, camera_configuration->getResolution());

		// debug projection frame
		this->projection.createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
			//frame_resized
		);

		// delay for syncing processing projection elimination
		for (unsigned int i = 0; i < iterations_delay_peopleextracting; ++i) {}
		// eliminate projection from camera frame
		cv::Mat frame_eliminatedprojection;
		this->projection.eliminateProjectionFeedbackFromFrameCamera(frame_eliminatedprojection, frame_camera);
		if (this->calibration->getDebugMode()) {
			eliminatedprojection_camera_window->drawImage(frame_eliminatedprojection);
		}

		// extract people from camera frame
		detectpeople_frame = frame_eliminatedprojection.clone();
		people_camera = this->people_extractor->extractPeople(detectpeople_frame);
		if (this->calibration->getDebugMode()) {
			window_peopleextractor->drawFrame();
		}

		if (this->calibration->getDebugMode()) {
			// draw detected people camera image
			detectedpeople_camera_window->drawImage(frame_camera, people_camera);
		}

		// change extrated people to projector location from camera location
		const scene_interface::People people_projector = this->projection.createPeopleProjectorFromPeopleCamera(people_camera);

		// draw detected people projection image
		if (this->calibration->getDebugMode()) {
			detectedpeople_projection_window->drawImage(frame_projection, people_projector);
		}

		// send extracted people via shared memory to scene
		this->sendExtractedpeople(people_projector);

		// shutdown on keypress
		if (cv::waitKey(1) != OpenCVUtil::NOKEY_ANYKEY) {
			this->running->running = false;
			this->running->reboot_on_shutdown = false;
		}
	}

	// safe release video capture
	video_capture.release();
}

void ImovePeopleextractorManager::sendExtractedpeople(const scene_interface::People extractedpeople) {
	//Initialize shared memory STL-compatible allocator
	scene_interface_sma::PeopleSMA people_sma = scene_interface_sma::PeopleSMA((*this->segment).get_segment_manager());

	// create shared memory vector of extracted people
  boost::interprocess::offset_ptr<scene_interface_sma::People> si_people = this->segment->construct<scene_interface_sma::People>(boost::interprocess::anonymous_instance)(people_sma);

	for (scene_interface::Person person : extractedpeople) {
		//Initialize shared memory STL-compatible allocator
		scene_interface_sma::LocationsSMA locations_sma(this->segment->get_segment_manager());
		scene_interface::Location location = person.getLocation();
		// create shared memory vector of locations
		boost::interprocess::offset_ptr<scene_interface_sma::Locations> locations = this->segment->construct<scene_interface_sma::Locations>(boost::interprocess::anonymous_instance)(locations_sma);
		// put shared memory allocated location in shared memory allocated vector of locations
		locations->push_back(
			this->segment->construct<scene_interface_sma::Location>(boost::interprocess::anonymous_instance)(location.getX(), location.getY())
		);

		// create shared memory allocated person type from person type
		scene_interface_sma::Person::PersonType person_type;
		switch (person.getPersonType()) {
			case scene_interface::Person::PersonType::Bystander:
				person_type = scene_interface_sma::Person::PersonType::Bystander;
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
		si_people->push_back(
			this->segment->construct<scene_interface_sma::Person>(boost::interprocess::anonymous_instance)(
				locations,
				person_type,
				movement_type,
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
	boost::interprocess::offset_ptr<peopleextractor_interface_sma::SceneframeQueue>& pi_sceneframe_queue = this->pi_sceneframe_queue;
	boost::interprocess::offset_ptr<Running>& running = this->running;
	const float factor_resize_capture_scene = this->calibration->getProjectioneliminationConfiguration()->getFactorResizeCaptureScene();
	Projection& projection = this->projection;

	while (running->running) {
		// when scene frame available
		if (!pi_sceneframe_queue->empty()) {
			// pop all frames which we are not able to process so fast
			while (pi_sceneframe_queue->size() > 2) {
				pi_sceneframe_queue->pop_front();
			}
			// convert from sma to opencv mat
			boost::interprocess::offset_ptr<peopleextractor_interface_sma::Image> pi_sceneframe = pi_sceneframe_queue->front();
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
			cv::resize(cv_sceneframe, cv_sceneframe_resize, cv::Size(pi_sceneframe->getWidth() * factor_resize_capture_scene, pi_sceneframe->getHeight() * factor_resize_capture_scene));
			// feed opencv image to calibration
			projection.feedFrameProjector(cv_sceneframe_resize);
			// remove from queue
			pi_sceneframe_queue->pop_front();
		}
	}
}
