//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {
  // Mat1f init_frame(960, 540, CV_8UC3, Scalar(0,0,0));
  // frame = init_frame;

  frame = Mat::zeros(540, 960, CV_8UC3);

  params.filterByCircularity = false;
  params.filterByColor = false;
  params.filterByConvexity = false;
  params.filterByInertia = false;
  params.filterByArea = true;
  params.minArea = 400;
  params.maxArea = 1000000;
  params.minDistBetweenBlobs = 100;
  detector = SimpleBlobDetector::create(params);
}

PeopleDetector::~PeopleDetector() {}

void PeopleDetector::detectionTest(char* videoFile) {

  cv::VideoCapture capture(videoFile);
  if (!capture.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }

  namedWindow("Frame");

  int keyboard;
  cv::Mat new_frame;

  while((char) keyboard != 'q'){
      for (int i=0; i<2; i++) {
        if(!capture.read(new_frame)) {
            cerr << "Unable to read next frame" << endl;
            exit(EXIT_FAILURE);
        }
      }

      resize(new_frame, new_frame, Size(960, 540));

      Mat diff_frame;
      absdiff(new_frame, frame, diff_frame);
      Scalar sumElems = sum(diff_frame);
      if (sumElems[0] + sumElems[1] + sumElems[2] > 10000000) {
        cout << "renew" << endl;
        renew();
      }

      frame = new_frame;
      detect();

      keyboard = waitKey(30);
  }

  capture.release();
}

void PeopleDetector::detectionTest() {

  VideoCapture capture(1);
  if (!capture.isOpened()) {
    cerr << "Unable to read from camera" << endl;
    exit(EXIT_FAILURE);
  }

  namedWindow("Frame");

  int keyboard;
  Mat new_frame;

  while((char)keyboard != 'q'){
      for (int i=0; i<2; i++) {
        if(!capture.read(new_frame)) {
            cerr << "Unable to read next frame" << endl;
            exit(EXIT_FAILURE);
        }
      }

      resize(new_frame, new_frame, Size(960, 540));

      Mat diff_frame;
      absdiff(new_frame, frame, diff_frame);
      Scalar sumElems = sum(diff_frame);
      if (sumElems[0] + sumElems[1] + sumElems[2] > 15000000) {
        cout << "renew" << endl;
        renew();
      }

      frame = new_frame;
      detect();

      keyboard = waitKey(30);
  }

  capture.release();
}

void PeopleDetector::detect() {

  new_locations.clear();

  Mat bg_sub_frame;
  Mat thresh;
  Mat keypoints_frame;
  Person* closestPerson;

  bg_sub->apply(frame, bg_sub_frame);
  threshold(bg_sub_frame, thresh, 200, 255, 0);

  vector<KeyPoint> keypoints;
  detector->detect(thresh,keypoints);
  drawKeypoints(thresh, keypoints, keypoints_frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

  for (auto &kp : keypoints) {
    float xco;
    float yco;
    if (kp.pt.y < 180) {
      yco = kp.pt.y+20;
    }
    else if (kp.pt.y < 360) {
      yco = kp.pt.y;
    }
    else {
      yco = kp.pt.y-20;
    }
    if (kp.pt.x < 320) {
      xco = kp.pt.x +20;
    }
    else if (kp.pt.x < 640) {
      xco = kp.pt.x;
    }
    else {
      xco = kp.pt.x-20;
    }

    Vector2 new_location = Vector2(xco, yco);
    // new_locations.push_back(new_location);
    int index_closest = getClosest(new_location);
    int id;
    if (index_closest < 0) {
      Person new_person = Person(new_location, Participant);
      detected_people.push_back(new_person);
      id = new_person.getId();
    }
    else {
      detected_people[index_closest].setLocation(new_location);
      id = detected_people[index_closest].getId();
    }

    putText(keypoints_frame, std::to_string(id), Point(new_location.x, new_location.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0));

    // circle(keypoints_frame, Point(xco, yco), 5, Scalar(255, 0,0), 3);

    // if (!detected_people.empty()) {
    //   closestPerson = getClosest(new_location);
    //   closestPerson->setLocation(new_location);
    // }
    // else {
    //   Person new_person = Person(new_location, Participant);
    //   detected_people.push_back(new_person);
    //   closestPerson = &detected_people.back();
    // }
    // putText(keypoints_frame, std::to_string(closestPerson->getId()), Point(new_location.x, new_location.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0));
    // cout << "check" << endl;
  }
  imshow("Frame", keypoints_frame);
}

void PeopleDetector::renew() {
  bg_sub = createBackgroundSubtractorKNN();
}

int PeopleDetector::getClosest(Vector2 location) {
  float min_distance = std::numeric_limits<float>::max();
  int min_index = -1;
  for (int i = 0; i < detected_people.size(); i++) {
    float distance = location.distance(detected_people[i].getLocation());
    if (distance < min_distance && distance < 100) {
      min_distance = distance;
      min_index = i;
    }
  }
  return min_index;
}
