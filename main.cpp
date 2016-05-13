#include <iostream>
#include <sstream>
#include "PeopleDetector.h"

using namespace std;

int main(int argc, char* argv[]) {

  PeopleDetector peopleDetector = PeopleDetector();

  if (argc != 2) {
    peopleDetector.detectionTest();
  }
  else {
    peopleDetector.detectionTest(argv[1]);
  }

  return 0;
}
