#include <opencv2/opencv.hpp>

#include "Manager.hpp"

#include "OpenCVUtil.hpp"
#include "interface/Person.h"
#include "scene/LightTrail/LightTrailScene.h"
#include "scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "Windows/Frame.hpp"
#include "Windows/DetectedPeopleCamera.hpp"
#include "Windows/DetectedPeopleProjection.hpp"
#include "Windows/Scene.hpp"

ImoveManager::ImoveManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail) {
	this->calibration = calibration;
	
	// setup scene
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

void ImoveManager::run() {
	// debug windows
	FrameWindow window_frame(cv::Size(0, 0));
	DetectedPeopleCameraWindow detectedpeople_camera_window(cv::Size(500, 0));
	DetectedPeopleProjectionWindow detectedpeople_projection_window(cv::Size(1000, 0));
	
	// setup scene window
	SceneWindow window_scene(this->calibration->getResolutionProjector());
	
	// setup clock
	sf::Clock clock;
	
	// setup camera
	cv::VideoCapture video_capture(this->calibration->getCameraDevice());

	cv::Mat frame_camera;
	cv::Mat frame_projection;
	cv::Mat detectpeople_frame;
	vector<Person> detected_people;
	float dt;
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
		
		// draw detected people camera image
		detectedpeople_camera_window.drawImage(frame_camera, detected_people);
		
		// change extrated people to projector location from camera location
		calibration->changeProjectorFromCameraLocationPerson(detected_people);
		
		// draw detected people projection image
		detectedpeople_projection_window.drawImage(frame_projection, detected_people);
		
		// update scene with location of people
		this->scene->updatePeople(detected_people);

		// draw next scene frame based on clock difference
		dt = clock.restart().asSeconds();
		//dt = 1.f/24.f;
		this->scene->update(dt);
		
		// draw the actual scene on window
		window_scene.drawScene(this->scene);
	}

	// safe release video capture
	video_capture.release();
}
