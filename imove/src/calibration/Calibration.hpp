#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <queue>

#include "../interface/Person.h"

// Mappings for projector frames and points from camera frames and points based on camera and projector properties
class Calibration {
	public:
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param resolution_projector The projector resolution
		 * @param camera_projector_transformation The projection transformation matrix between the camera and projection
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 * @param projector_background_light The light level difference between the projectors projection light level and background level
		 **/
		Calibration(const cv::Size& resolution_projector, cv::Mat& camera_projector_transformation, unsigned int frames_projector_camera_delay, double projector_background_light, float meter);

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

		void changeProjectorFromCameraLocationPerson(std::vector<Person>& persons) const;

		/**
		 * Creates a projection frame from the camera frame based on the given camera_projector_transformation
		 * 
		 * @param frame_projection	The output projection frame
		 * @param frame_camera			The input camera frame
		 **/
		void createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const;

		/**
		 * Sets the amount of frames delay between the projectors projection captured by the camera.
		 * 
		 * @param frames_projector_camera_delay The amount of frames delay between the projectors projection captured by the camera
		 **/
		void setFramesProjectorCameraDelay(unsigned int frames_projector_camera_delay);

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
		 * Sets the one meter in pixels on a camera image.
		 * 
		 * @param meter The one meter in pixel on a camera image
		 **/
		void setMeter(float meter);

		/**
		 * Gets the one meter in pixels on a camera image.
		 **/
		float getMeter() const;

	private:
		// The projector resolution
		cv::Size resolution_projector;
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
