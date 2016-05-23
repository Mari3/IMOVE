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
    PeopleDetector detector;
    // CameraProjectionMapper mapper;
    PeopleIdentifier identifier;

    // Current frame
    Mat frame;

 public:
    PeopleExtractor();
    ~PeopleExtractor();

    vector<Person> extractPeople(Mat new_frame);
};


#endif  // IMOVE_SRC_IMAGE_PROCESSING_PEOPLEEXTRACTOR_H_
