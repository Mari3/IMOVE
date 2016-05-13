//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {
  params.filterByCircularity = false;
  params.filterByColor = false;
  params.filterByConvexity = false;
  params.filterByInertia = false;
  params.filterByArea = true;
  params.minArea = 400;
  params.maxArea = 1000000;
  params.minDistBetweenBlobs = 100;
  detector = SimpleBlobDetector::create(params);
}
PeopleDetector::~PeopleDetector() {}

void PeopleDetector::detectionTest(char* videoFile) {

  cv::VideoCapture capture(videoFile);
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  namedWindow("Frame");

  int keyboard;
  cv::Mat frame;

  while((char) keyboard != 'q'){
      for (int i=0; i<2; i++) {
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame" << endl;
            exit(EXIT_FAILURE);
        }
      }
      resize(frame, frame, Size(960, 540));
      detect(frame);

      keyboard = waitKey(30);
  }

  capture.release();
}

void PeopleDetector::detectionTest() {

  VideoCapture capture(1);
  if (!capture.isOpened()) {
    cerr << "Unable to read from camera" << endl;
    exit(EXIT_FAILURE);
  }

  namedWindow("Frame");

  int keyboard;
  cv::Mat frame;

  while((char)keyboard != 'q'){
      for (int i=0; i<2; i++) {
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame" << endl;
            exit(EXIT_FAILURE);
        }
      }
      resize(frame, frame, Size(960, 540));
      detect(frame);

      keyboard = waitKey(30);
  }

  capture.release();
}

void PeopleDetector::detect(Mat currentFrame) {

  Mat bg_sub_frame;
  Mat thresh;
  Mat keypoints_frame;

  bg_sub->apply(currentFrame, bg_sub_frame);
  threshold(bg_sub_frame, thresh, 200, 255, 0);

  vector<KeyPoint> keypoints;
  detector->detect(thresh,keypoints);
  drawKeypoints(thresh, keypoints, keypoints_frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  for (auto &kp : keypoints) {
    float xco;
    float yco;
    if (kp.pt.y < 180) {
      yco = kp.pt.y+20;
    }
    else if (kp.pt.y < 360) {
      yco = kp.pt.y;
    }
    else {
      yco = kp.pt.y-20;
    }
    if (kp.pt.x < 320) {
      xco = kp.pt.x +20;
    }
    else if (kp.pt.x < 640) {
      xco = kp.pt.x;
    }
    else {
      xco = kp.pt.x-20;
    }
    circle(keypoints_frame, Point(xco, yco), 5, Scalar(255, 0,0), 3);


  }

  imshow("Frame", keypoints_frame);
}
