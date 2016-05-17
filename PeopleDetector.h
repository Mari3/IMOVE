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
  std::vector<Person> detected_people = std::vector<Person>();
  std::vector<Vector2> new_locations;
  SimpleBlobDetector::Params params;
  Ptr<BackgroundSubtractorKNN> bg_sub = createBackgroundSubtractorKNN();
  Ptr<SimpleBlobDetector> detector;
  Mat frame;

public:
  PeopleDetector();
  ~PeopleDetector();

  void detectionTest(char* videoFile);
  void detectionTest();
  void detect();
  void renew();
  int getClosest(Vector2 location);

};


#endif //IMOVE_PEOPLEDETECTOR_H
