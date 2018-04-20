#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/persistence.hpp>
#include <assert.h>
#include <iostream>

#include "../OpenCVUtil.hpp"
#include "CameraConfiguration.hpp"

CameraConfiguration::CameraConfiguration(const cv::Size& resolution, unsigned int deviceid, const Boundary& projection, float meter, float area, float dist) : Configuration(),
	resolution(resolution),
	deviceid(deviceid),
	projection(projection),
	meter(meter),
	minBlobArea(area),
	minBlobDistance(dist)
{
	this->setProjection(projection);
}

CameraConfiguration* CameraConfiguration::readNode(cv::FileStorage read_config) {
	// read resolution_camera from yml using OpenCV FileStorage
	cv::Size resolution;
	read_config["Resolution_camera"] >> resolution;
	// read projection coordinates from yml using OpenCV FileStorage
	cv::Point2f cv_top_left, cv_top_right, cv_bottom_left, cv_bottom_right;
	read_config["Projection_top_left"]     >> cv_top_left;
	read_config["Projection_top_right"]    >> cv_top_right;
	read_config["Projection_bottom_left"]  >> cv_bottom_left;
	read_config["Projection_bottom_right"] >> cv_bottom_right;
	Vector2 top_left     (cv_top_left.x,    cv_top_left.y    );
	Vector2 top_right    (cv_top_right.x,   cv_top_right.y   );
	Vector2 bottom_left  (cv_bottom_left.x, cv_bottom_left.y );
	Vector2 bottom_right (cv_bottom_right.x, cv_bottom_right.y);
	// read camera meter from yml using OpenCV FileStorage
	float meter, area, distance;
	read_config["Meter_camera"] >> meter;
	read_config["Minimum_Area_Blobs"] >> area;
	read_config["Minimum_Distance_Between_Blobs"] >> distance;

	return new CameraConfiguration(
		resolution,
		Configuration::read(read_config, "Camera_device"),
		Boundary(
			top_left,
			top_right,
			bottom_left,
			bottom_right
		),
		meter,
		area,
		distance
	);
}

CameraConfiguration* CameraConfiguration::createFromNode(cv::FileStorage read_config, const unsigned int deviceid) {
	// read meter from yml using OpenCV FileStorage; default if not existing
	float meter;
	if (read_config["Meter_camera"].isNone()) {
		meter = CameraConfiguration::DEFAULT_METER_CAMERA;
	} else {
		read_config["Meter_camera"] >> meter;
	}

	// retreive camera resolution from OpenCV VideoCapture
	cv::VideoCapture camera_videoreader(deviceid);
	const cv::Size resolution(camera_videoreader.get(cv::CAP_PROP_FRAME_WIDTH), camera_videoreader.get(cv::CAP_PROP_FRAME_HEIGHT));
	camera_videoreader.release();

	// read projection from yml using OpenCV FileStorage
	Boundary projection;
	if (read_config["Projection_top_left"].isNone()) {
		// if not exists in configuration; create projection as whole camera frame
		projection = Boundary(
			Vector2(OpenCVUtil::ORIGIN2D.x, OpenCVUtil::ORIGIN2D.y),
			Vector2(  resolution.width - 1, OpenCVUtil::ORIGIN2D.y),
			Vector2(OpenCVUtil::ORIGIN2D.x,  resolution.height - 1),
			Vector2(  resolution.width - 1,  resolution.height - 1)
		);
	} else {
		// read projection coordinates from yml using OpenCV FileStorage
		cv::Point2f cv_top_left, cv_top_right, cv_bottom_left, cv_bottom_right;
		read_config["Projection_top_left"]     >> cv_top_left;
		read_config["Projection_top_right"]    >> cv_top_right;
		read_config["Projection_bottom_left"]  >> cv_bottom_left;
		read_config["Projection_bottom_right"] >> cv_bottom_right;
		Vector2 top_left     (cv_top_left.x,     cv_top_left.y    );
		Vector2 top_right    (cv_top_right.x,    cv_top_right.y   );
		Vector2 bottom_left  (cv_bottom_left.x,  cv_bottom_left.y );
		Vector2 bottom_right (cv_bottom_right.x, cv_bottom_right.y);
		projection = Boundary(
			top_left,
			top_right,
			bottom_left,
			bottom_right
		);
	}

	float area, distance;
	if (read_config["Minimum_Area_Blobs"].isNone()) {
		area = 50;
		distance = 50;
	} else {
		read_config["Minimum_Area_Blobs"] >> area;
		read_config["Minimum_Distance_Between_Blobs"] >> distance;
	}

 	// create initial CameraConfiguration based on configuration, arguments and defaults
	return new CameraConfiguration(
		resolution,
		deviceid,
		projection,
		meter,
		area,
		distance
	);
}

void CameraConfiguration::writeNode(cv::FileStorage write_config) const {
	write_config << "Camera_device"                     << (int) this->deviceid;
	write_config << "Resolution_camera"                 <<       this->resolution;
	write_config << "Projection_top_left"               <<       cv::Point2f( this->projection.getUpperLeft().x,  this->projection.getUpperLeft().y);
	write_config << "Projection_top_right"              <<       cv::Point2f(this->projection.getUpperRight().x, this->projection.getUpperRight().y);
	write_config << "Projection_bottom_left"            <<       cv::Point2f( this->projection.getLowerLeft().x,  this->projection.getLowerLeft().y);
	write_config << "Projection_bottom_right"           <<       cv::Point2f(this->projection.getLowerRight().x, this->projection.getLowerRight().y);
	write_config << "Meter_camera"                      <<       this->meter;
}

cv::Size CameraConfiguration::getResolution() const {
	return this->resolution;
}
unsigned int CameraConfiguration::getDeviceid() const {
	return this->deviceid;
}
void CameraConfiguration::setMeter(float meter) {
	this->meter = meter;
}
const float CameraConfiguration::getMeter() const {
	return this->meter;
}
void CameraConfiguration::setProjection(const Boundary& projection) {
	this->projection = projection;
}
const Boundary CameraConfiguration::getProjection() const {
	return this->projection;
}
const float CameraConfiguration::getMinBlobArea() {
	return this->minBlobArea;
}
const float CameraConfiguration::getMinBlobDistance() {
	return this->minBlobDistance;
}
