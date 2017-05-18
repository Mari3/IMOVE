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
#include "../Person.h"
#include "../../../scene_interface/src/People.h"
#include "../../../util/src/Vector2.h"
#include "../../../util/src/Boundary.h"



class PeopleExtractor {
 private:
  // Detector to detect locations of people in a frame
  PeopleDetector detector;

  // Identifier to identify people with locations
  PeopleIdentifier identifier;

  // Current frame
  cv::Mat frame;
  // Debug frame
  cv::Mat debug_frame;

  // Size of the frame after resizing
  cv::Size frame_size_resized;

  // Convert objects from the People class to the scene interface People class
  const scene_interface::People convert(std::vector<Person>& people);

  // Ratio with which the frame is resized
  float resize_ratio;

  int playfield_a = 20;
  int playfield_b = 20;

 public:
  PeopleExtractor(const cv::Size& frame_size, float pixels_per_meter, float resolution_resize_height, const Boundary& boundary);
  ~PeopleExtractor();

  // Main extraction function to extract people from a frame
  const scene_interface::People extractPeople(cv::Mat& new_frame);

  // Display image processing results
  const cv::Mat getDebugFrame() const;
};

#endif  // IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_
