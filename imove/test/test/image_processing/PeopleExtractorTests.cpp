
#include <gtest/gtest.h>

#include "../../../src/ImageProcessing/PeopleExtractor.h"

TEST (PeopleExtractorTests, extractOnePersonTest) {
  cv::VideoCapture capture("imove/test/image_processing/aulaTestShort.mp4");
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  cv::Mat frame;
  PeopleExtractor extractor = PeopleExtractor(cv::Size(1920, 1080), 191, 216);
  std::vector<Person> detected_people;

  for (int i=0; i < 50; i++) {
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }

    detected_people = extractor.extractPeople(frame);
  }

  ASSERT_EQ(detected_people.size(), (unsigned int) 1);
  ASSERT_NEAR(1545, detected_people[0].getLocation().x, 2);
  ASSERT_NEAR(95, detected_people[0].getLocation().y, 2);
}

TEST (PeopleExtractorTests, ExtractMultiplePeople) {
  cv::VideoCapture capture("imove/test/image_processing/aulaTest.mp4");
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  cv::Mat frame;
  PeopleExtractor extractor = PeopleExtractor(cv::Size(1920, 1080), 191, 216);
  std::vector<Person> detected_people;

  for (int i=0; i < 90; i++) {
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }

    detected_people = extractor.extractPeople(frame);
  }

  ASSERT_EQ(detected_people.size(), (unsigned int) 2);
  ASSERT_NEAR(1400, detected_people[0].getLocation().x, 2);
  ASSERT_NEAR(235, detected_people[0].getLocation().y, 2);
  ASSERT_NEAR(1275, detected_people[1].getLocation().x, 2);
  ASSERT_NEAR(265, detected_people[1].getLocation().y, 2);

  for (int i=0; i < 60; i++) {
    if (!capture.read(frame)) {
      std::cerr << "Unable to read next frame." << std::endl;
      std::cerr << "Exiting..." << std::endl;
      exit(EXIT_FAILURE);
    }

    detected_people = extractor.extractPeople(frame);
  }

  ASSERT_EQ(detected_people.size(), (unsigned int) 0);
  capture.release();
}
