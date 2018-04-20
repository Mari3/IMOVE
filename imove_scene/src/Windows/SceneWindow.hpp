#include <SFML/Graphics.hpp>
#include <opencv2/opencv.hpp>

#include "../Scene/Scene.h"

// Window to display Scene
class SceneWindow {
	public:
		/**
		 * Initialize Scene window with resolution projector
		 *
		 * @param resoltuion_projector The resolution of the projector which the Scene should be rendering in.
		 **/
		SceneWindow(cv::Size resolution_projector, const bool& fullscreen_projector);

		// draw the Scene on the render window
		void drawScene(Scene* scene);

		// capture the drawn scene to image
		// const sf::Image captureFrameScene();

		// checks wether to close window or not and closes if needed
		bool shouldKeepOpen();

	protected:
		sf::RenderWindow* window_scene;
};
