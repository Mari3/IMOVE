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
  params.minArea = 700;
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

  //read input data. ESC or 'q' for quitting
  while( (char)keyboard != 'q' && (char)keyboard != 27 ){
      //read the current frame
      for (int i=0; i<2; i++) {
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
      }
      resize(frame, frame, Size(960, 540));
      detect(frame, keyboard);
  }

  capture.release();
}

void PeopleDetector::detect(Mat currentFrame, int key) {
  Mat bg_sub_frame;
  Mat thresh;
  Mat keypoints_frame;

  bg_sub->apply(currentFrame, bg_sub_frame);
  threshold(bg_sub_frame, thresh, 200, 255, 0);

  vector<KeyPoint> keypoints;
  detector->detect(thresh,keypoints);
  drawKeypoints(thresh, keypoints, keypoints_frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  imshow("Frame", keypoints_frame);
  key = waitKey( 30 );
}
