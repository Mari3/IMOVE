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
#include "Detector/PeopleDetector.h"
#include "Identifier/PeopleIdentifier.h"
#include "../Interface/Person.h"
#include "../Util/Vector2.h"



class PeopleExtractor {
 private:
  // Detector to detect locations of people in a frame
  PeopleDetector detector;

  // Identifier to identify people with locations
  PeopleIdentifier identifier;

  // Current frame
  cv::Mat frame;
  cv::Mat results_frame;

  // Size of the frame
  cv::Size frame_size_resized;

  // Ratio with which the frame is resized
  float resize_ratio;

 public:
  PeopleExtractor(cv:: Size frame_size, float pixels_per_meter, float resolution_resize_height);
  ~PeopleExtractor();

  // Main extraction function to extract people from a frame
  vector<Person> extractPeople(cv::Mat& new_frame);

  // Display image processing results
  void displayResults();
};

#endif  // IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_
