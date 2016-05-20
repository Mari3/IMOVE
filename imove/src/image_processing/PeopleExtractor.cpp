//
// Created by Wouter Posdijk on 11/05/16.
//

#include "PeopleExtractor.h"

PeopleExtractor::PeopleExtractor() {

  //Initialize empty frame
  frame = Mat::zeros(180, 320, CV_8UC1);

  detector = PeopleDetector();
  identifier = PeopleIdentifier();
}

PeopleExtractor::~PeopleExtractor() {}

vector<Person> PeopleExtractor::extractPeople(Mat new_frame) {

  Mat diff_frame;

  cvtColor(new_frame, new_frame, CV_RGB2GRAY);
  resize(new_frame, new_frame, Size(320, 180));
  absdiff(new_frame, frame, diff_frame);
  Scalar sumElems = sum(diff_frame);
  if (sumElems[0] + sumElems[1] + sumElems[2] > 7000000) {
    //  cout << "renew" << endl;
    detector.renew();
  }

  frame = new_frame;
  vector<Person> people = identifier.match(detector.detect(frame));
  for (Person& p : people) {
    Vector2 old_loc = p.getLocation();
    p.setLocation(Vector2(old_loc.x*3.375, old_loc.y*3.375));
  }

  return people;



}
