#ifndef CAMERACONFIGURATION_H
#define CAMERACONFIGURATION_H

#include <opencv2/imgproc/imgproc.hpp>

#include "../Boundary.h"
#include "Configuration.hpp"

// Mappings for projector frames and points from camera frames and points based on camera and projector properties
class CameraConfiguration : public Configuration {
	public:
		// Default configuration parameters if not given when createFromFile
		static constexpr          float  DEFAULT_METER_CAMERA                      = 100.f;

		/**
		 * Setup properties for mapping projector from camera.
		 *
		 * @param resolution The camera resolution
		 * @param deviceid The integer identifier of the camera by the OS
		 * @param boundary The boundary of the projection on the camera frame
		 * @param meter The amount of pixels measured as 1 meter on camere frame
		 **/
		CameraConfiguration(const cv::Size& resolution, unsigned int deviceid, const Boundary& projection, float meter, float area, float dist);

		/**
		 * Creates the CameraConfiguration from a file node by which the filepath is given
		 *
		 * @param read_config File node from which to read CameraConfiguration
		 **/
		static CameraConfiguration* readNode(cv::FileStorage read_config);

		/**
		 * Creates the CameraConfiguration from a file node by which the filepath is given and defaults
		 *
		 * @param rea_config File node from which to load CameraConfiguration
		 * @param deviceid The id of the device given by the os
		 **/
		static CameraConfiguration* createFromNode(cv::FileStorage read_config, const unsigned int deviceid);

		/**
		 * Creates the file by which the file node is given from the CameraConfiguration
		 *
		 * @param write_config File node to which to save CameraConfiguration
		 **/
		void writeNode(cv::FileStorage write_config) const;

		/**
		 * Gets the resolution of the camera.
		 **/
		cv::Size getResolution() const;

		/**
		 * Gets the integer of the camera device defined by the OS.
		 **/
		unsigned int getDeviceid() const;

		/**
		 * Sets the one meter in pixels on a camera image and calculates the one meter in pixels on a projector meter
		 *
		 * @param meter The one meter in pixel on a camera image
		 **/
		void setMeter(float meter);

		/**
		 * Gets the one meter in pixels on a camera image.
		 **/
		const float getMeter() const;

		/**
		 * Sets (the boundary of) the projection
		 *
		 * @param projection The (boundary of the) projection
		 **/
		void setProjection(const Boundary& projection);

		/**
		 * Gets (the boundary of) the projection
		 **/
		const Boundary getProjection() const;

		/**
		 * Gets the minimum area of blobs
		 **/
		 const float getMinBlobArea();

		 /**
 		 * Gets the minimum distance between blobs
 		 **/
		 const float getMinBlobDistance();

	protected:
		// The camera resolution
		cv::Size resolution;
		// The integer identifier of the camera device of the OS
		unsigned int deviceid;
		// The boundary of the projection
		Boundary projection;
		// 1 meter in pixels on camera image
		float meter;
		// Minimum blob area for blob detection
		float minBlobArea;
		// Minimum distance between blobs
		float minBlobDistance;
};

#endif // CAMERACONFIGURATION_H
