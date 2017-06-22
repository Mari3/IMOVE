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

  // Set parameters for SimpleBlobDetector according to the camera height
  if (low_camera) {
    params.minArea = pixels_per_meter*5;
    params.minDistBetweenBlobs = params.minArea*0.15;
  } else {
    params.minArea = pixels_per_meter*0.6;
    params.minDistBetweenBlobs = params.minArea*1.6;
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
  // Draw circle around keypoints
  cv::drawKeypoints(thresh_frame, keypoints, keypoints_frame, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  // Change keypoint locations according to perspective
  for (auto &keypoint : keypoints) {
    Vector2 new_location = changeToPerspective(keypoint.pt.x, keypoint.pt.y, frame.rows, frame.cols);
    new_locations.push_back(new_location);
  }

  // Set frame with visible keyoints as frame to display
  display_frame = keypoints_frame;

  // Return all new locations
  return new_locations;
}

cv::Mat PeopleDetector::getDisplayFrame() {
  return display_frame;
}

Vector2 PeopleDetector::changeToPerspective(int keypoint_x, int keypoint_y, float frame_height, float frame_width) {
  int xco = keypoint_x;
  int yco = keypoint_y;

  // Adjust y
  if (keypoint_y < frame_height/3) {
    yco = keypoint_y+2*(pixels_per_meter/6);
  } else if (keypoint_y < (frame_height*2)/3) {
    yco = keypoint_y+(pixels_per_meter/6);
  } else {
    yco = keypoint_y;
  }
  // Adjust x
  if (keypoint_x < frame_width/3) {
    xco = keypoint_x +(pixels_per_meter/6);
  } else if (keypoint_x < (frame_width*2)/3) {
    xco = keypoint_x;
  } else {
    xco = keypoint_x-(pixels_per_meter/6);
  }

  return Vector2(xco, yco);
}
