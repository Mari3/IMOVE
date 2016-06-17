#include <vector>

#include "PeopleDetector.h"
#include "../../../../util/src/Vector2.h"

PeopleDetector::PeopleDetector() {}

PeopleDetector::PeopleDetector(float pixels_per_meter, bool low_camera) : pixels_per_meter(pixels_per_meter) {
  // Initialize background subtractor
  background_subtractor = cv::createBackgroundSubtractorKNN();

  // Set parameters for SimpleBlobDetector
  params.filterByCircularity = false;
  params.filterByColor = false;
  params.filterByConvexity = false;
  params.filterByInertia = false;
  params.filterByArea = true;
  params.maxArea = 1000000;

  // Set parameters for SimpleBlobDetector according wether the camera height is low or not
  if (low_camera) {
    params.minArea = pixels_per_meter*5;
    params.minDistBetweenBlobs = params.minArea*0.15;
  } else {
    params.minArea = pixels_per_meter*1.2;
    params.minDistBetweenBlobs = params.minArea*0.6;
  }
  // Create SimpleBlobDetector
  blob_detector = cv::SimpleBlobDetector::create(params);
}

PeopleDetector::~PeopleDetector() {}

// Detect people in frame
std::vector<Vector2> PeopleDetector::detect(cv::Mat& frame) {
  // Vector to store newly detected locations
  std::vector<Vector2> new_locations;

  // Initialize frames for operations
  cv::Mat background_subtr_frame;
  cv::Mat thresh_frame;
  cv::Mat keypoints_frame;

  // Apply background subtractor to frame
  background_subtractor->apply(frame, background_subtr_frame);
  // Filter out shadows
  threshold(background_subtr_frame, thresh_frame, 200, 255, 0);

  // Vector to store keypoints
  std::vector<cv::KeyPoint> keypoints;
  // Detect blobs as keypoints
  blob_detector->detect(thresh_frame, keypoints);
  cvtColor(thresh_frame, thresh_frame, CV_GRAY2RGB);
  // Draw circle around keypoints
  cv::drawKeypoints(thresh_frame, keypoints, keypoints_frame, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  float frame_height = frame.rows;
  float frame_width = frame.cols;

  // Change keypoint locations according to perspective
  for (auto &keypoint : keypoints) {
    int xco;
    int yco;
    if (keypoint.pt.y < frame_height/3) {
      yco = keypoint.pt.y+2*(pixels_per_meter/6);
    } else if (keypoint.pt.y < (frame_height*2)/3) {
      yco = keypoint.pt.y+(pixels_per_meter/6);
    } else {
      yco = keypoint.pt.y;
    }
    if (keypoint.pt.x < frame_width/3) {
      xco = keypoint.pt.x +(pixels_per_meter/6);
    } else if (keypoint.pt.x < (frame_width*2)/3) {
      xco = keypoint.pt.x;
    } else {
      xco = keypoint.pt.x-(pixels_per_meter/6);
    }

    cv::circle(keypoints_frame, cv::Point(xco, yco), 5, cv::Scalar(0, 0, 255));

    // Add location to locations vector
    Vector2 new_location = Vector2(xco, yco);
    new_locations.push_back(new_location);
  }

  display_frame = keypoints_frame;

  // Return all new locations
  return new_locations;
}

cv::Mat PeopleDetector::getDisplayFrame() {
  return display_frame;
}
