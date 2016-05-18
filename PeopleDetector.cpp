//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleDetector.h"

PeopleDetector::PeopleDetector() {

  //Initialize empty frame
  frame = Mat::zeros(540, 960, CV_8UC3);

  // Set parameters for SimpleBlobDetector
  params.filterByCircularity = false;
  params.filterByColor = false;
  params.filterByConvexity = false;
  params.filterByInertia = false;
  params.filterByArea = true;
  params.minArea = 400;
  params.maxArea = 1000000;
  params.minDistBetweenBlobs = 100;

  // Create SimpleBlobDetector
  detector = SimpleBlobDetector::create(params);
}

PeopleDetector::~PeopleDetector() {}

//Create VideoCapture with input video (For test purposes only)
VideoCapture PeopleDetector::readVideoFile(char* videoFile) {
  VideoCapture cap(videoFile);
  if (!cap.isOpened()) {
    cerr << "Unable to open video file" << endl;
    exit(EXIT_FAILURE);
  }
  return cap;
}

//Create VideoCapture from camera input stream
VideoCapture PeopleDetector::readVideoFile() {
  VideoCapture cap(1);
  if (!cap.isOpened()) {
    cerr << "Unable to read from camera" << endl;
    exit(EXIT_FAILURE);
  }
  return cap;
}

//For test purposes only
void PeopleDetector::detectionTest(char* videoFile) {
  detectPeople(readVideoFile(videoFile));
}

//For test purposes only
void PeopleDetector::detectionTest() {
  detectPeople(readVideoFile());
}

//Main detection method
void PeopleDetector::detectPeople(VideoCapture capture) {

  namedWindow("Frame");
  int keyboard;
  Mat new_frame;
  Mat diff_frame;

  while((char)keyboard != 'q'){
      for (int i=0; i<2; i++) {
        if(!capture.read(new_frame)) {
            cerr << "Unable to read next frame" << endl;
            exit(EXIT_FAILURE);
        }
      }

      resize(new_frame, new_frame, Size(960, 540));

      absdiff(new_frame, frame, diff_frame);
      Scalar sumElems = sum(diff_frame);
      if (sumElems[0] + sumElems[1] + sumElems[2] > 14000000) {
        cout << "renew" << endl;
        renew();
      }

      frame = new_frame;
      detect();
      match();

      keyboard = waitKey(30);
  }

  capture.release();
}

//Detect people in frame
void PeopleDetector::detect() {

  new_locations.clear();

  Mat bg_sub_frame;
  // Mat thresh;
  Mat keypoints_frame;
  Person* closestPerson;

  bg_sub->apply(frame, bg_sub_frame);
  threshold(bg_sub_frame, thresh, 200, 255, 0);

  vector<KeyPoint> keypoints;
  detector->detect(thresh,keypoints);
  // drawKeypoints(thresh, keypoints, keypoints_frame, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

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
    new_locations.push_back(new_location);
  }

  // imshow("Frame", keypoints_frame);
}

void PeopleDetector::renew() {
  bg_sub = createBackgroundSubtractorKNN();
}

void PeopleDetector::match() {
  for (int i = 0; i < detected_people.size(); i++) {
    int index_closest = getClosest(detected_people[i]);
    if (index_closest < 0) {
    //if (detected_people[i].closeToEdge(960,540)) {
        detected_people.erase(detected_people.begin() + i);
        i--;
      //}
    }
    else {
      Vector2 new_loc = new_locations[index_closest];
      // if (close to edge) { // check closer to edge than location
      //  delete person
      // }
      detected_people[i].setLocation(new_loc);
      putText(thresh, std::to_string(detected_people[i].getId()), Point(new_loc.x, new_loc.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
      new_locations.erase(new_locations.begin() + index_closest);
    }
  }
  for (int j = 0; j < new_locations.size(); j++) {
    Person new_person = Person(new_locations[j], Participant);
    //if (!new_person.closeToEdge(960, 540)) {
      //new_locations.erase(new_locations.begin() + j);
      //j--;
    //}
    //else {
      detected_people.push_back(new_person);
      putText(thresh, std::to_string(new_person.getId()), Point(new_locations[j].x, new_locations[j].y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0));
    //}
  }
  imshow("Frame", thresh);
}

int PeopleDetector::getClosest(Person person) {
  float min_distance = std::numeric_limits<float>::max();
  int min_index = -1;
  for (int i = 0; i < new_locations.size(); i++) {
    float distance = person.getLocation().distance(new_locations[i]);
    if (distance < min_distance && distance < 100) {
      min_distance = distance;
      min_index = i;
    }
  }
  return min_index;
}
