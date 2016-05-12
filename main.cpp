#include <iostream>
#include <sstream>
#include "PeopleDetector.h"

using namespace std;

int main(int argc, char* argv[]) {

  if (argc != 2) {
    cerr << "No video input" << endl;
    return EXIT_FAILURE;
  }

  PeopleDetector peopleDetector = PeopleDetector();
  peopleDetector.detectionTest(argv[1]);

  return 0;
}
