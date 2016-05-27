#include <opencv2/opencv.hpp>

#include "../scene/Scene.h"

// Window to display scene
class SceneWindow {
	public:
		/**
		 * Initialize scene window with resolution projector
		 * 
		 * @param resoltuion_projector The resolution of the projector which the scene should be rendering in.
		 **/
		SceneWindow(cv::Size resolution_projector);
		
		// draw the scene on the render window
		void drawScene(Scene* scene);

	protected:
		sf::RenderWindow* window_scene;
};
