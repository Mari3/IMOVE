
#include <gtest/gtest.h>

#include "../../../src/image_processing/PeopleExtractor.h"

TEST (PeopleExtractorTests, extractPeopleTest) {
  PeopleExtractor extractor = PeopleExtractor(cv::Size(1920, 1080), 191, 216);
}
