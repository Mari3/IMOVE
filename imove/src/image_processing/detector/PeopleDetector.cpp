//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

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

  if (low_camera) {
    params.minArea = pixels_per_meter*5;
    params.minDistBetweenBlobs = params.minArea*0.20;
  } else {
    params.minArea = pixels_per_meter*2;
    params.minDistBetweenBlobs = params.minArea*0.250;
  }
  // Create SimpleBlobDetector
  blob_detector = cv::SimpleBlobDetector::create(params);
}

PeopleDetector::~PeopleDetector() {}

// Detect people in frame
vector<Vector2> PeopleDetector::detect(cv::Mat frame) {
  // Vector to store newly detected locations
  vector<Vector2> new_locations;

  // Initialize frames for operations
  cv::Mat background_subtr_frame;
  cv::Mat thresh_frame;
  cv::Mat keypoints_frame;

  // Apply background subtractor to frame
  background_subtractor->apply(frame, background_subtr_frame);
  // Filter out shadows
  threshold(background_subtr_frame, thresh_frame, 200, 255, 0);

  // Vector to store keypoints
  vector<cv::KeyPoint> keypoints;
  // Detect blobs as keypoints
  blob_detector->detect(thresh_frame, keypoints);
  // Draw circle around keypoints
  cv::drawKeypoints(thresh_frame, keypoints, keypoints_frame, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  float frame_height = frame.rows;
  float frame_width = frame.cols;

  // Change keypoint locations according to perspective
  for (auto &keypoint : keypoints) {
    int xco;
    int yco;
    if (keypoint.pt.y < frame_height/3) {
      yco = keypoint.pt.y+(pixels_per_meter/6);
    } else if (keypoint.pt.y < (frame_height*2)/3) {
      yco = keypoint.pt.y;
    } else {
      yco = keypoint.pt.y-(pixels_per_meter/6);
    }
    if (keypoint.pt.x < frame_width/3) {
      xco = keypoint.pt.x +(pixels_per_meter/6);
    } else if (keypoint.pt.x < (frame_width*2)/3) {
      xco = keypoint.pt.x;
    } else {
      xco = keypoint.pt.x-(pixels_per_meter/6);
    }

    // Add location to locations vector
    Vector2 new_location = Vector2(xco, yco);
    new_locations.push_back(new_location);
  }

  // Show tresholded background subtraction with drawn keypoints
  cv::imshow("Frame", keypoints_frame);
  // Return all new locations
  return new_locations;
}

void PeopleDetector::renew() {
  // Reset background subtractor to adapt to changes in lighting
  background_subtractor = cv::createBackgroundSubtractorKNN();
}
