#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <queue>

#include "../../scene_interface/src/People.h"
#include "../../util/src/Boundary.h"

// Mappings for projector frames and points from camera frames and points based on camera and projector properties
class Calibration {
	public:
		// Default configuration parameters if not given when createFromFile
		static constexpr unsigned int    DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY     = 5;
		static constexpr          double DEFAULT_PROJECTOR_BACKGROUND_LIGHT        = 39;
		static constexpr          float  DEFAULT_METER_CAMERA                      = 100.f;
		static constexpr unsigned int    DEFAULT_MAXIMUM_FPS_SCENE                 = 60;
		static constexpr unsigned int    DEFAULT_FPS_CAPTURE_SCENE                 = 8;
		static constexpr unsigned int    DEFAULT_ITERATIONS_DELAY_PEOPLEEXTRACTING = 5000;
		static constexpr unsigned int    DEFAULT_FACTOR_RESIZE_CAPTURE_SCENE       = 10;
		static constexpr          bool   DEFAULT_FULLSCREEN_PROJECTOR              = true;
		
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param resolution_projector The projector resolution
		 * @param fullscreen_projector The projector fullscreen or not
		 * @param resolution_camera The camera resolution
		 * @param camera_device The integer identifier of the camera by the OS
		 * @param boundary The boundary of the projection on the camera frame
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 * @param meter The amount of pixels measured as 1 meter on camere frame
		 * @param maximum_fps_scene The maximum fps for the scene
		 * @param fps_capture_scene The fps capture scene for projection elimination
		 * @param iterations_delay_peopleextracting The amount of iterations to stall for syncing people extracting and slow scene capture image
		 * @param factor_resize_capture_scene The factor to resize the captured scene before sending over to people extractor
		 **/
		Calibration(const cv::Size& resolution_projector, const bool& fullscreen_projector, const cv::Size& resolution_camera, unsigned int camera_device, const Boundary& projection, unsigned int frames_projector_camera_delay, float projector_background_light, float meter, unsigned int maximum_fps_scene, unsigned int fps_capture_scene, unsigned int iterations_delay_peopleextracting, unsigned int factor_resize_capture_scene);

		/**
		 * Creates the Calibration from a file by which the filepath is given
		 * 
		 * @param filepath Path to file from which to read Calibration
		 **/
		static const Calibration readFile(const char* filepath);
		
		/**
		 * Creates the Calibration from a file by which the filepath is given and defaults
		 * 
		 * @param filepath Path to file from which to load Calibration
		 **/
		static Calibration createFromFile(const char* filepath, unsigned int cameradevice, cv::Size resolution_projector);
		
		/**
		 * Creates the file by which the filepath is given from the Calibration
		 * 
		 * @param filepath Path to file to which to save Calibration
		 **/
		void writeFile(const char* filepath) const;

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
		 * Gets the projection transformation matrix between the camera and the projection.
		 **/
		cv::Mat getCameraProjectorTransformation() const;

		/**
		 * Gets the resolution of the projector.
		 **/
		cv::Size getResolutionProjector() const;

		/**
		 * Gets whether the scene should be fullscreen on projector.
		 **/
		bool getFullscreenProjector() const;

		/**
		 * Gets the resolution of the camera.
		 **/
		cv::Size getResolutionCamera() const;

		/**
		 * Gets the integer of the camera device defined by the OS.
		 **/
		unsigned int getCameraDevice() const;

		/**
		 * Sets the one meter in pixels on a camera image and calculates the one meter in pixels on a projector meter
		 * 
		 * @param meter The one meter in pixel on a camera image
		 **/
		void setMeterCamera(float meter_camera);

		/**
		 * Gets the one meter in pixels on a camera image.
		 **/
		const float getMeterCamera() const;

		/**
		 * Gets the one meter in pixels on a projector image.
		 **/
		const float getProjectorMeter() const;

		/**
		 * Sets (the boundary of) the projection and calculates camera projector transformation
		 *
		 * @param projection The (boundary of the) projection
		 **/
		void setProjection(const Boundary& projection);

		/**
		 * Gets (the boundary of) the projection
		 **/
		const Boundary getProjection() const;

		/**
		 * Sets the maximum FPS of the scene
		 * 
		 * @param maximum_fps_scene The maximum amount of frames per second for the scene
		 **/
		void setMaximumFpsScene(const unsigned int maximum_fps_scene);

		/**
		 * Gets the maximum frames per second of the scene
		 **/
		const unsigned int getMaximumFpsScene() const;

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
		/**
		 * Reads an unsigned int from configuration node using given name. assert fails when < 0
		 * 
		 * @param read_config          opencv yml configuration node
		 * @param name_yml             name of unsigned int property in yml configuration
		 **/
		static inline unsigned int read(cv::FileStorage read_config, char const* name_yml) {
				signed int   signed_int;
		  unsigned int unsigned_int;
			assert(!read_config[name_yml].isNone());
			read_config[name_yml] >> signed_int;
			// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
			assert(signed_int >= 0);
			unsigned_int = (unsigned int) signed_int;
			return unsigned_int;
		}
		/**
		 * Creates an unsigned int from configuration node using given name and if not exists use default. 0 when < 0
		 * 
		 * @param read_config          opencv yml configuration node
		 * @param name_yml             name of unsigned int property in yml configuration
		 * @param default_unsigned_int if not given returns this default unsigned int
		 **/
		static inline unsigned int create(cv::FileStorage read_config, char const* name_yml, unsigned int default_unsigned_int) {
				signed int   signed_int;
		  unsigned int unsigned_int;
			if (read_config[name_yml].isNone()) {
				unsigned_int = default_unsigned_int;
			} else {
				read_config[name_yml] >> signed_int;
				// OpenCV yml does not support unsigned in; initialize signed int to unsigned int 0
				if (signed_int < 0) {
					unsigned_int = 0;
				} else {
					unsigned_int = (unsigned int) signed_int;
				}
			}
			return unsigned_int;
		}

		// The projector resolution
		cv::Size resolution_projector;
		// Whether to put scene fullscreen or not
		bool fullscreen_projector;
		// The camera resolution
		cv::Size resolution_camera;
		// The integer identifier of the camera device of the OS 
		unsigned int camera_device;
		// The boundary of the projection
		Boundary projection;
		// The projection transformation matrix between the camera and projection
		cv::Mat camera_projector_transformation;
		// The queue with the projector frames which are not yet expected to be captured by the camera frame
		std::queue<cv::Mat> frames_delay_projector;
		// The amount of frames delay between the projectors projection captured by the camera
		unsigned int frames_projector_camera_delay;
		// The light level difference between the projectors projection light level and background level
		float projector_background_light;
		// 1 meter in pixels on camera image
		float meter_camera;
		// 1 meter in pixels on camera image
		float meter_projector;
		// fps scene
		unsigned int maximum_fps_scene;
		// fps capture scene for projection elimination
		unsigned int fps_capture_scene;
		// amount of iterations to stall for syncing people extracting and slow scene capture image
		unsigned int iterations_delay_peopleextracting;
		// factor to resize the captured scene before sending over to people extractor
		unsigned int factor_resize_capture_scene;
};

#endif // CALIBRATION_H
