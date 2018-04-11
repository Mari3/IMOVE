#ifndef IMOVE_CONFIGURATION_H
#define IMOVE_CONFIGURATION_H

struct SceneConfiguration {
  unsigned int screenWidth, screenHeight;
  int radius;
  static SceneConfiguration readFromFile(char* fileName);
};


#endif //IMOVE_PONGCONFIGURATION_H
