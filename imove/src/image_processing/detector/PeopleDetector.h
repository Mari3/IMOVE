//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_
#define IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <cv.hpp>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

#include "../../interface/Person.h"

using namespace cv;

class PeopleDetector {
 private:
  // Parameters for SimpleBlobDetector
  SimpleBlobDetector::Params params;

  // KNN background subtractor
  Ptr<BackgroundSubtractorKNN> background_subtractor;

  // Blob detector
  Ptr<SimpleBlobDetector> blob_detector;

 public:
   PeopleDetector();
   ~PeopleDetector();

  // Detect people in frame
  vector<Vector2> detect(Mat frame);

  // Renew background subtractor
  void renew();
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_
