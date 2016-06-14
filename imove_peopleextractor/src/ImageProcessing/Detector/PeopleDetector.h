#ifndef IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_
#define IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <cv.hpp>
#include <vector>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "../../../../imove_imp/src/Vector2.h"

class PeopleDetector {
 private:
  // Parameters for SimpleBlobDetector
  cv::SimpleBlobDetector::Params params;

  // KNN background subtractor
  cv::Ptr<cv::BackgroundSubtractorKNN> background_subtractor;

  // Blob Detector
  cv::Ptr<cv::SimpleBlobDetector> blob_detector;

  // Nr of pixels equal to one meter on the Scene
  float pixels_per_meter;

  // Frame to display
  cv::Mat display_frame;

 public:
  PeopleDetector();
  // Constructor with number of pixels that represent one meter and wether the camera height is low or not
  PeopleDetector(float pixels_per_meter, bool low_camera);
  ~PeopleDetector();

  // Detect people in frame
  std::vector<Vector2> detect(cv::Mat& frame);

  cv::Mat getDisplayFrame();
};

#endif  // IMOVE_SRC_IMAGE_PROCESSING_DETECTOR_PEOPLEDETECTOR_H_
