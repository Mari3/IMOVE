//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_PEOPLEDETECTOR_H
#define IMOVE_PEOPLEDETECTOR_H

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <cv.hpp>

#include "Person.h"

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <limits>

using namespace cv;

class PeopleDetector {

private:

  //Vector containing detected people
  std::vector<Person> detected_people = std::vector<Person>();

  //Vector containing newly detected locations in current frame
  std::vector<Vector2> new_locations;

  //Parameters for SimpleBlobDetector
  SimpleBlobDetector::Params params;

  //KNN background subtractor
  Ptr<BackgroundSubtractorKNN> bg_sub = createBackgroundSubtractorKNN();

  //Blob detector
  Ptr<SimpleBlobDetector> detector;

  //Current frame
  Mat frame;

public:
  PeopleDetector();
  ~PeopleDetector();

  //For test purposes only
  void detectionTest(char* videoFile);
  void detectionTest();

  //Create VideoCapture from input file (For test purposes only)
  VideoCapture readVideoFile(char* videoFile);

  //Create VideoCapture from camera input stream
  VideoCapture readVideoFile();

  //Main detection method
  void detectPeople(VideoCapture capture);

  //Detect people in frame
  void detect();

  //Renew background subtractor
  void renew();

  //Get closest location to a Person
  int getClosest(Vector2 location);

};


#endif //IMOVE_PEOPLEDETECTOR_H
