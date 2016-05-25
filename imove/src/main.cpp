#include <opencv2/opencv.hpp>
#include <opencv2/core/persistence.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

#include "calibration/Calibration.hpp"
#include "image_processing/PeopleExtractor.h"
#include "interface/Person.h"
#include "scene/Scene.h"
#include "scene/LightTrail/LightTrailScene.h"
#include "scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"

const signed int NOKEY_ANYKEY = -1;

std::mutex mutex_scene;
bool running = true;

Calibration* calibration;
int camera_device;
Scene* scene;
cv::Size resolution_camera;
cv::Size resolution_projector;
float meter;

// Sets up people extracting and loop extracting people for scene input while running
void main_peopleextractor() {
	PeopleExtractor people_extractor = PeopleExtractor(resolution_camera, meter, 216);

	// debug camera window
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::VideoCapture video_capture(camera_device);

	// while no key pressed
	while (cv::waitKey(1) == NOKEY_ANYKEY) {
		//for(int i=0;i<2;++i)
		//	video_capture.grab();
		if (!video_capture.read(frame_camera)) {
			std::cerr << "Unable to read next frame." << std::endl;
			std::cerr << "Exiting..." << std::endl;
			exit(EXIT_FAILURE);
		}

		// debug projection frame
		calibration->createFrameProjectionFromFrameCamera(
			frame_projection,
			frame_camera
		);
		// extract people from camera frame
	 	vector<Person> detected_people = people_extractor.extractPeople(frame_camera);
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
				//std::to_string(detected_people.at(i).getId()),
				"12",
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
		mutex_scene.lock();
		scene->updatePeople(detected_people);
		mutex_scene.unlock();
	}
	running = false;

	pthread_exit(NULL);
}

// setup and run scene with continous people extraction as input based on configuration given in parameter otherwise show parameters
int main(int argc, char* argv[]) {
	// show parameters if not given 1 parameter
	if (argc != 3) {
		std::cerr << "Usage: <path to configuration file> <path to configuration scene>" << std::endl;
		return EXIT_SUCCESS;
	}

	// read calibration config
	cv::FileStorage fs;
	fs.open(argv[1], cv::FileStorage::READ);
	fs["Camera_device"] >> camera_device;
	//cv::Size resolution_camera;
	fs["Resolution_camera"] >> resolution_camera;
	cv::Size resolution_projector;
	fs["Resolution_projector"] >> resolution_projector;
	cv::Mat camera_projector_transformation;
	fs["Camera_projector_transformation"] >> camera_projector_transformation;
	unsigned int frames_projector_camera_delay;
	signed int int_frames_projector_camera_delay;
	fs["Frames_projector_camera_delay"] >> int_frames_projector_camera_delay;
	if (int_frames_projector_camera_delay < 0) {
		frames_projector_camera_delay = 0;
	} else {
		frames_projector_camera_delay = (unsigned int) int_frames_projector_camera_delay;
	}
	double percentage_projector_background_light;
	fs["Percentage_projector_background_light"] >> percentage_projector_background_light;
	//float meter;
	fs["Meter"] >> meter;
	fs.release();

	calibration = new Calibration(resolution_projector, camera_projector_transformation, frames_projector_camera_delay, percentage_projector_background_light);

	// debug windows
	cv::namedWindow("Camera", cv::WINDOW_NORMAL);
	cv::moveWindow("Camera", 500, 0);

	cv::namedWindow("Projection", cv::WINDOW_NORMAL);
	cv::moveWindow("Projection", 1000, 0);

	cv::namedWindow("Frame", cv::WINDOW_NORMAL);

	// setup scene
    sf::RenderWindow window(sf::VideoMode(resolution_projector.width, resolution_projector.height),"Projection");
    window.clear(sf::Color::Black);
    window.display();
    
    
    LightTrailConfiguration config = LightTrailConfiguration::readFromFile(argv[2]);
    scene = new LightTrailScene(config,
                                       new LightSourceVectorRepository(),
                                       new LightTrailVectorRepository(),
                                       new GravityPointVectorRepository(),
                                       new ColorHoleVectorRepository(),
                                       new LightPersonMapRepository()
                                       );

	// setup clock
    sf::Clock clock;

	// setup people extracting in seperate thread
	std::thread thread_peopleextractor(main_peopleextractor);

	// while no key pressed on other thread
	while (running) {

		// draw next scene frame based on clock difference
		mutex_scene.lock();
		float dt = clock.restart().asSeconds();
		//float dt = 1.f/24.f;
		scene->update(dt);

		window.clear(sf::Color::Black);
		scene->draw(window);

		mutex_scene.unlock();
		window.display();
	}

	// normally exit program by stopping people extractor thread
	thread_peopleextractor.join();

	return EXIT_SUCCESS;
}
