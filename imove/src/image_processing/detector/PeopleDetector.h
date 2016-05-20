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

#include "../../interface/Person.h"

#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>

using namespace cv;

class PeopleDetector {

private:

  //Parameters for SimpleBlobDetector
  SimpleBlobDetector::Params params;

  //KNN background subtractor
  Ptr<BackgroundSubtractorKNN> bg_sub;

  //Blob detector
  Ptr<SimpleBlobDetector> blob_detector;

  //Frame to visualize test
  Mat test_frame;

public:
  PeopleDetector();
  ~PeopleDetector();

  //Detect people in frame
  vector<Vector2> detect(Mat frame);

  //Renew background subtractor
  void renew();

};


#endif //IMOVE_PEOPLEDETECTOR_H
