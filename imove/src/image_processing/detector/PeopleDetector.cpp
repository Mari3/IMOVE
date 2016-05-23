//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {
  // Initialize background subtractor
  background_subtractor = createBackgroundSubtractorKNN();

  // Set parameters for SimpleBlobDetector
  params.filterByCircularity = false;
  params.filterByColor = false;
  params.filterByConvexity = false;
  params.filterByInertia = false;
  params.filterByArea = true;
  params.minArea = 50;
  params.maxArea = 333333;
  params.minDistBetweenBlobs = 20;

  // Create SimpleBlobDetector
  blob_detector = SimpleBlobDetector::create(params);
}

PeopleDetector::~PeopleDetector() {}

// Detect people in frame
vector<Vector2> PeopleDetector::detect(Mat frame) {
  // Vector to store newly detected locations
  vector<Vector2> new_locations;

  // Initialize frames for operations
  Mat background_subtr_frame;
  Mat thresh_frame;
  Mat keypoints_frame;

  // Apply background subtractor to frame
  background_subtractor->apply(frame, background_subtr_frame);
  // Filter out shadows
  threshold(background_subtr_frame, thresh_frame, 200, 255, 0);

  // Vector to store keypoints
  vector<KeyPoint> keypoints;
  // Detect blobs as keypoints
  blob_detector->detect(thresh_frame, keypoints);
  // Draw circle around keypoints
  drawKeypoints(thresh_frame, keypoints, keypoints_frame, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  // vector< vector<Point> > contours;
  // findContours(thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  // vector< vector<Point> > contours_thresholded;
  // for (auto contour : contours) {
  //   if (contourArea(contour) > 500) {
  //     contours_thresholded.push_back(contour);
  //   }
  // }
  // contours.clear();
  // drawContours(keypoints_frame, contours_thresholded, -1, Scalar(0,0,255));

  // Change keypoint locations according to perspective
  for (auto &keypoint : keypoints) {
    int xco;
    int yco;
    if (keypoint.pt.y < 60) {
      yco = keypoint.pt.y+6;
    } else if (keypoint.pt.y < 120) {
      yco = keypoint.pt.y;
    } else {
      yco = keypoint.pt.y-6;
    }
    if (keypoint.pt.x < 107) {
      xco = keypoint.pt.x +6;
    } else if (keypoint.pt.x < 214) {
      xco = keypoint.pt.x;
    } else {
      xco = keypoint.pt.x-6;
    }

    // Add location to locations vector
    Vector2 new_location = Vector2(xco, yco);
    new_locations.push_back(new_location);
  }

  // Show tresholded background subtraction with drawn keypoints
  imshow("Frame", keypoints_frame);
  // Return all new locations
  return new_locations;
}

void PeopleDetector::renew() {
  // Reset background subtractor to adapt to changes in lighting
  background_subtractor = createBackgroundSubtractorKNN();
}
