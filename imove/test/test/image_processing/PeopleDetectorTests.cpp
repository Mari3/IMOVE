
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/persistence.hpp>
#include <vector>

#include "../../../src/image_processing/detector/PeopleDetector.h"

TEST (PeopleDetectorTests, DetectOnePerson) {
  cv::VideoCapture capture("imove/test/image_processing/aulaTestShort.mp4");
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  cv::Mat frame;
  PeopleDetector detector = PeopleDetector(38.2, false);
  std::vector<Vector2> detected_locations;

  for (int i=0; i < 50; i++) {
    detected_locations.clear();
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }

    cvtColor(frame, frame, CV_RGB2GRAY);
    resize(frame, frame, cv::Size(384, 216));

    detected_locations = detector.detect(frame);
  }
  ASSERT_EQ(detected_locations.size(), (unsigned int) 1);
  ASSERT_NEAR(310, detected_locations[0].x, 2);
  ASSERT_NEAR(20, detected_locations[0].y, 2);
  capture.release();
}

TEST (PeopleDetectorTests, DetectMultiplePeople) {
  cv::VideoCapture capture("imove/test/image_processing/aulaTest.mp4");
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  cv::Mat frame;
  PeopleDetector detector = PeopleDetector(38.2, false);
  std::vector<Vector2> detected_locations;

  for (int i=0; i < 200; i++) {
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  for (int j=0; j < 200; j++) {
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }

    cvtColor(frame, frame, CV_RGB2GRAY);
    resize(frame, frame, cv::Size(384, 216));
    detected_locations = detector.detect(frame);
  }
  
  ASSERT_EQ(detected_locations.size(), (unsigned int) 4);
  ASSERT_NEAR(327, detected_locations[0].x, 2);
  ASSERT_NEAR(198, detected_locations[0].y, 2);
  ASSERT_NEAR(302, detected_locations[1].x, 2);
  ASSERT_NEAR(147, detected_locations[1].y, 2);
  ASSERT_NEAR(233, detected_locations[2].x, 2);
  ASSERT_NEAR(75, detected_locations[2].y, 2);
  ASSERT_NEAR(213, detected_locations[3].x, 2);
  ASSERT_NEAR(63, detected_locations[3].y, 2);
  capture.release();
}
