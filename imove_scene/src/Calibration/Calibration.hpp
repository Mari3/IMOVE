#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <queue>

#include "../../../scene_interface/src/Person.h"
#include "../../../scene_interface/src/Boundary.h"

// Mappings for projector frames and points from camera frames and points based on camera and projector properties
class Calibration {
	public:
		// Default configuration parameters if not given when createFromFile
		static constexpr unsigned DEFAULT_FRAMES_PROJECTOR_CAMERA_DELAY = 5;
		static constexpr double DEFAULT_PROJECTOR_BACKGROUND_LIGHT = 39;
		static constexpr float DEFAULT_METER = 100.f;
		
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param resolution_projector The projector resolution
		 * @param resolution_camera The camera resolution
		 * @param camera_device The integer identifier of the camera by the OS
		 * @param boundary The boundary of the projection on the camera frame
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 **/
		Calibration(const cv::Size& resolution_projector, const cv::Size& resolution_camera, unsigned int camera_device, const Boundary& projection, unsigned int frames_projector_camera_delay, double projector_background_light, float meter);

		/**
		 * Creates the Calibration from a file by which the filepath is given
		 * 
		 * @param filepath Path to file from which to read Calibration
		 **/
		static Calibration* readFile(const char* filepath);
		
		/**
		 * Creates the Calibration from a file by which the filepath is given and defaults
		 * 
		 * @param filepath Path to file from which to load Calibration
		 **/
		static Calibration* createFromFile(const char* filepath, unsigned int cameradevice, cv::Size resolution_projector);
		
		/**
		 * Creates the file by which the filepath is given from the Calibration
		 * 
		 * @param filepath Path to file to which to save Calibration
		 **/
		void writeFile(const char* filepath) const;

		/**
		 * Adds a projector frame which is used for eliminating the projection
		 * 
		 * @param frame_projector The next frame of the projection
		 **/
		void feedFrameProjector(const cv::Mat& frame_projector);

		/**
		 * Removes the projection on the camera frame based on fed projector frames, the amount of frames to delay and the projector background light level.
		 * 
		 * @param frame_projectioneliminated	The output camera frame on which the projection is eliminated
		 * @param frame_camera								The input camera frame
		 **/
		void eliminateProjectionFeedbackFromFrameCamera(cv::Mat& frame_projectioneliminated, const cv::Mat& frame_camera);

		/**
		 * Creates points on the projector frame from the camera frame based on the given camera_projector_transformation
		 * 
		 * @param points_frame_projector	The output points on a projector frame
		 * @param points_frame_camera			The input points on a camera frame
		 **/

		void createPointsFrameProjectorFromPointsFrameCamera(std::vector<cv::Point2f>& points_frame_projector, const std::vector<cv::Point2f>& points_frame_camera) const;
		/**
		 * Changes persons location into the location on the projector based on the given camera_projector_transformation
		 * 
		 * @param persons locations get changed from camera frame location to projector frame location
		 **/

		void changeProjectorFromCameraLocationPerson(std::vector<scene_interface::Person>& persons) const;

		/**
		 * Creates a projection frame from the camera frame based on the given camera_projector_transformation
		 * 
		 * @param frame_projection	The output projection frame
		 * @param frame_camera			The input camera frame
		 **/
		void createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const;

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
		double getProjectorBackgroundLight() const;

		/**
		 * Sets the light level difference between the projectors projection light level and background level.
		 * 
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 **/
		void setProjectorBackgroundLight(double projector_background_light);

		/**
		 * Sets the projection transformation matrix between the camera and the projection.
		 * 
		 * @param camera_projector_transformation The projection transformation matrix between the camera and projection
		 **/
		void setCameraProjectorTransformation(cv::Mat& camera_projector_transformation);

		/**
		 * Gets the projection transformation matrix between the camera and the projection.
		 **/
		cv::Mat getCameraProjectorTransformation() const;

		/**
		 * Gets the resolution of the projector.
		 **/
		cv::Size getResolutionProjector() const;

		/**
		 * Gets the resolution of the camera.
		 **/
		cv::Size getResolutionCamera() const;

		/**
		 * Gets the integer of the camera device defined by the OS.
		 **/
		unsigned int getCameraDevice() const;

		/**
		 * Sets the one meter in pixels on a camera image.
		 * 
		 * @param meter The one meter in pixel on a camera image
		 **/
		void setMeter(float meter);

		/**
		 * Gets the one meter in pixels on a camera image.
		 **/
		const float getMeter() const;

		/**
		 * Gets (the boundary of) the projection
		 **/
		const Boundary getProjection() const;

	private:
		// The projector resolution
		cv::Size resolution_projector;
		// The camera resolution
		cv::Size resolution_camera;
		// The boundary of the projection
		Boundary projection;
		// The integer identifier of the camera device of the OS 
		unsigned int camera_device;
		// The projection transformation matrix between the camera and projection
		cv::Mat camera_projector_transformation;
		// The queue with the projector frames which are not yet expected to be captured by the camera frame
		std::queue<cv::Mat> frames_delay_projector;
		// The amount of frames delay between the projectors projection captured by the camera
		unsigned int frames_projector_camera_delay;
		// The light level difference between the projectors projection light level and background level
		double projector_background_light;
		// 1 meter in pixels on camera image
		float meter;
};

#endif // CALIBRATION_H
