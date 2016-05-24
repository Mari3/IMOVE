//
// Created by Wouter Posdijk on 11/05/16.
//

#ifndef IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_
#define IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_

#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <cv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
// #include "cameraprojectionmapper/CameraProjectionMapper.h"
#include "detector/PeopleDetector.h"
#include "identifier/PeopleIdentifier.h"
#include "../interface/Person.h"
#include "../util/Vector2.h"



class PeopleExtractor {
 private:
  // Detector to detect locations of people in a frame
  PeopleDetector detector;

  // CameraProjectionMapper mapper;

  // Identifier to identify people with locations
  PeopleIdentifier identifier;

  // Current frame
  cv::Mat frame;

  // Size of the frame
  cv::Size frame_size;

  // Ratio with which the frame is resized
  float resize_ratio;

  // Nr of pixels equal to one meter on the scene
  float pixels_per_meter;

 public:
  PeopleExtractor(cv:: Size frame_size, float pixels_per_meter);
  ~PeopleExtractor();

  // Main extraction function to extract people from a frame
  vector<Person> extractPeople(cv::Mat new_frame);
};

#endif  // IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_
