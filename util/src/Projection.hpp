#ifndef PROJECTION_H
#define PROJECTION_H

#include <opencv2/imgproc/imgproc.hpp>

#include <vector>
#include <queue>

#include "Calibration.hpp"
#include "../../scene_interface/src/People.h"
#include "../../util/src/Boundary.h"

// Mappings for projector frames and points from camera frames and points based on camera and projector properties
class Projection {
	public:
		/**
		 * Setup properties for mapping projector from camera.
		 * 
		 * @param calibration Calibration which contains configuration on which to map projection 
		 **/
		Projection(Calibration* calibration);

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
		 * Creates the people on the projector from people on the camera using camera projector transformation
		 * 
		 * @param people_camera The people on the camera
		 **/
		const scene_interface::People createPeopleProjectorFromPeopleCamera(const scene_interface::People& people_camera) const;

		/**
		 * Creates a projection frame from the camera frame based on the given camera_projector_transformation
		 * 
		 * @param frame_projection	The output projection frame
		 * @param frame_camera			The input camera frame
		 **/
		void createFrameProjectionFromFrameCamera(cv::Mat& frame_projection, const cv::Mat& frame_camera) const;

	protected:
		// The queue with the projector frames which are not yet expected to be captured by the camera frame
		std::queue<cv::Mat> frames_delay_projector;
		
		// The calibration including configuration of camera and projector
		Calibration* calibration;
};

#endif // PROJECTION_H
