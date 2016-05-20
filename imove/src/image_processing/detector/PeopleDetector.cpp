//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {

  bg_sub = createBackgroundSubtractorKNN();

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

//Detect people in frame
vector<Vector2> PeopleDetector::detect(Mat frame) {

  vector<Vector2> new_locations;

  Mat bg_sub_frame;
  Mat thresh_frame;
  Mat keypoints_frame;

  bg_sub->apply(frame, bg_sub_frame);
  threshold(bg_sub_frame, thresh_frame, 200, 255, 0);

  vector<KeyPoint> keypoints;
  blob_detector->detect(thresh_frame,keypoints);
  drawKeypoints(thresh_frame, keypoints, keypoints_frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

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

  for (auto &kp : keypoints) {
    int xco;
    int yco;
    if (kp.pt.y < 60) {
      yco = kp.pt.y+6;
    }
    else if (kp.pt.y < 120) {
      yco = kp.pt.y;
    }
    else {
      yco = kp.pt.y-6;
    }
    if (kp.pt.x < 107) {
      xco = kp.pt.x +6;
    }
    else if (kp.pt.x < 214) {
      xco = kp.pt.x;
    }
    else {
      xco = kp.pt.x-6;
    }
    Vector2 new_location = Vector2(xco, yco);
    new_locations.push_back(new_location);
  }

  imshow("Frame", keypoints_frame);
  return new_locations;
}

void PeopleDetector::renew() {
  bg_sub = createBackgroundSubtractorKNN();
}
