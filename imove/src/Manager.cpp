#include <opencv2/opencv.hpp>

#include "Manager.hpp"

#include "OpenCVUtil.hpp"
#include "interface/Person.h"
#include "scene/LightTrail/LightTrailScene.h"
#include "scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"

ImoveManager::ImoveManager(Calibration* calibration, LightTrailConfiguration configuration_lighttrail) {
	this->calibration = calibration;
	// debug windows
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 500, 0);

	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1000, 0);

	cv::namedWindow("Frame", cv::WINDOW_NORMAL);

	// setup scene
	this->window_scene = new sf::RenderWindow(
		sf::VideoMode(
			this->calibration->getResolutionProjector().width,
			this->calibration->getResolutionProjector().height
		),
		"Projector"
	);
  this->window_scene->clear(sf::Color::Black);
  this->window_scene->display();

  this->scene = new LightTrailScene(
		configuration_lighttrail,
    new LightSourceVectorRepository(),
    new LightTrailVectorRepository(),
    new GravityPointVectorRepository(),
    new ColorHoleVectorRepository(),
    new LightPersonMapRepository()
  );
	
	// setup people extractor
	this->people_extractor = new PeopleExtractor(this->calibration->getResolutionCamera(), this->calibration->getMeter(), 216);
}

bool ImoveManager::run() {
	// setup clock
  sf::Clock clock;
	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::VideoCapture video_capture(this->calibration->getCameraDevice());
	vector<Person> detected_people;
	cv::Mat detectpeople_frame;

	// while no key pressed
	while (cv::waitKey(1) == OpenCVUtil::NOKEY_ANYKEY) {
		//for(int i=0;i<2;++i)
		//	video_capture.grab();
		if (!video_capture.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			return false;
		}

		// debug projection frame
		this->calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);
		// extract people from camera frame
		detectpeople_frame = frame_camera.clone();
	 	detected_people = people_extractor->extractPeople(detectpeople_frame);
		// detected_people.push_back(Person(Vector2(resolution_camera.width / 2, 2 * (resolution_camera.height / 3)), Participant));
		// debug people drawing on camera frame
		for (unsigned int i = 0; i < detected_people.size(); ++i) {
			cv::circle(
				frame_camera,
				cv::Point2f(
					detected_people.at(i).getLocation().x,
					detected_people.at(i).getLocation().y
				),
				20,
				cv::Scalar(255, 0, 0),
				2
			);
		}
		// debug camera frame
		cv::imshow("Camera", frame_camera);
		// change extrated people to projector location from camera location
		calibration->changeProjectorFromCameraLocationPerson(detected_people);
		// debug extracted perspective mapped people on projection
		for (unsigned int i = 0; i < detected_people.size(); ++i) {
			cv::circle(
				frame_projection,
				cv::Point2f(
					detected_people.at(i).getLocation().x,
					detected_people.at(i).getLocation().y
				),
				80,
				cv::Scalar(255, 244, 0),
				8
			);
			cv::putText(
				frame_projection,
				std::to_string(detected_people.at(i).getId()),
				cv::Point2f(
					detected_people.at(i).getLocation().x,
					detected_people.at(i).getLocation().y
				),
				cv::FONT_HERSHEY_SIMPLEX,
				1,
				cv::Scalar(255, 0, 0)
			);
		}
		// debug projection window
		cv::imshow("Projection", frame_projection);

		// update scene with location of people
		this->scene->updatePeople(detected_people);

		// draw next scene frame based on clock difference
		float dt = clock.restart().asSeconds();
		//float dt = 1.f/24.f;
		this->scene->update(dt);

		this->window_scene->clear(sf::Color::Black);
		this->scene->draw(*this->window_scene);

		this->window_scene->display();
	}
	video_capture.release();

	return true;
}
