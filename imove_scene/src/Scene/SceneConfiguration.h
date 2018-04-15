#ifndef IMOVE_CONFIGURATION_H
#define IMOVE_CONFIGURATION_H

#include "../../../util/src/configuration/ImoveConfiguration.hpp"

// Reads and holds parameter values that can be used in a scene
struct SceneConfiguration {
  // Width and height of the scene which whould correspond with
  // the resolution of the projector
  unsigned int screenWidth, screenHeight;
  // Radius of the circles
  int radius;
  // Function to read values from a yml file
  static SceneConfiguration readFromFile(char* fileName, ImoveConfiguration* calibration);
};


#endif //IMOVE_PONGCONFIGURATION_H
