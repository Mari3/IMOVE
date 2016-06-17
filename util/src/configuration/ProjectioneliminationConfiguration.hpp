#ifndef PROJECTIONELIMINIATION_H
#define PROJECTIONELIMINIATION_H

#include <opencv2/imgproc/imgproc.hpp>

#include "Configuration.hpp"

// Configuration variables for eliminating projection from camera frame
class ProjectioneliminationConfiguration : public Configuration {
	public:
		// Default configuration parameters if not given when createFromNode
		static constexpr unsigned int    DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY     = 5;
		static constexpr          double DEFAULT_PROJECTOR_BACKGROUND_LIGHT        = 39;
		static constexpr unsigned int    DEFAULT_FPS_CAPTURE_SCENE                 = 8;
		static constexpr unsigned int    DEFAULT_ITERATIONS_DELAY_PEOPLEEXTRACTING = 5000;
		static constexpr unsigned int    DEFAULT_FACTOR_RESIZE_CAPTURE_SCENE       = 10;
		
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 * @param fps_capture_scene The fps capture scene for projection elimination
		 * @param iterations_delay_peopleextracting The amount of iterations to stall for syncing people extracting and slow scene capture image
		 * @param factor_resize_capture_scene The factor to resize the captured scene before sending over to people extractor
		 **/
		ProjectioneliminationConfiguration(unsigned int frames_projector_camera_delay, float projector_background_light, unsigned int fps_capture_scene, unsigned int iterations_delay_peopleextracting, unsigned int factor_resize_capture_scene);

		/**
		 * Creates the ProjectioneliminationConfiguration from a file by which the filepath is given
		 * 
		 * @param read_config File node from which to read ProjectorConfiguration
		 **/
		static ProjectioneliminationConfiguration* readNode(cv::FileStorage read_config);
		
		/**
		 * Creates the ProjectioneliminationConfiguration from a file by which the filepath is given and defaults
		 * 
		 * @param read_config File node from which to load ProjectorConfiguration
		 **/
		static ProjectioneliminationConfiguration* createFromNode(cv::FileStorage read_config);
		
		/**
		 * Creates the file by which the filepath is given from the ProjectioneliminationConfiguration
		 * 
		 * @param write_config File node to which to save ProjectorConfiguration
		 **/
		void writeNode(cv::FileStorage write_config) const;

		/**
		 * Gets the amount of frames delay between the projectors projection captured by the camera.
		 **/
		unsigned int getFramesProjectorCameraDelay() const;

		/**
		 * Sets the amount of frames delay between the projectors projection captured by the camera.
		 * 
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 **/
		void setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay);

		/**
		 * Gets the light level difference between the projectors projection light level and background level.
		 **/
		float getProjectorBackgroundLight() const;

		/**
		 * Sets the light level difference between the projectors projection light level and background level.
		 * 
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 **/
		void setProjectorBackgroundLight(float projector_background_light);

		/**
		 * Sets the frames per second on which to capture the scene and queue it for projection elimination
		 * 
		 * @param fps_capture_scene The amount of frames per second on which to capture the scene
		 **/
		void setFpsCaptureScene(const unsigned int fps_capture_scene);
		
		/**
		 * Gets the frames per second on which to capture the scene and queue it for projection elimination
		 **/
		const unsigned int getFpsCaptureScene() const;

		/**
		 * Sets the amount of iterations to stall for syncing people extracting and slow scene capture image
		 * 
		 * @param iterations_delay_peopleextracting The amount of iterations to stall for sycing people extracting with slow capture scene image
		 **/
		void setIterationsDelayPeopleextracting(unsigned int iterations_delay_peopleextracting);
		
		/**
		 * Gets the amount of iterations to stall for syncing people extracting and slow scene capture image
		 **/
		const unsigned int getIterationsDelayPeopleextracting() const;

		/**
		 * Sets the factor to resize the captured scene before sending over to people extractor
		 * 
		 * @param factor_resize_capture_scene The factor to resize the captured scene before sending to people extractor
		 **/
		void setFactorResizeCaptureScene(unsigned int factor_resize_capture_scene);
		
		/**
		 * Gets the factor to resize the captured scene before sending over to people extractor
		 **/
		const unsigned int getFactorResizeCaptureScene() const;

	protected:
		// The amount of frames delay between the projectors projection captured by the camera
		unsigned int frames_projector_camera_delay;
		// The light level difference between the projectors projection light level and background level
		float projector_background_light;
		// fps capture scene for projection elimination
		unsigned int fps_capture_scene;
		// amount of iterations to stall for syncing people extracting and slow scene capture image
		unsigned int iterations_delay_peopleextracting;
		// factor to resize the captured scene before sending over to people extractor
		unsigned int factor_resize_capture_scene;
};

#endif // PROJECTIONELIMINIATION_H
