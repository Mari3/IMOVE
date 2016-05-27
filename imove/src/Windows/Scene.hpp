#include <opencv2/opencv.hpp>

#include "../scene/Scene.h"

// Window to display scene
class SceneWindow {
	public:
		SceneWindow(cv::Size resolution_projector);
		
		void drawScene(Scene* scene);

	protected:
		sf::RenderWindow* window_scene;
};
