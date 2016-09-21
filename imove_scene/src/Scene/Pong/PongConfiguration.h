#ifndef IMOVE_PONGCONFIGURATION_H
#define IMOVE_PONGCONFIGURATION_H

struct PongConfiguration {
unsigned int screenWidth, screenHeight;
int ballSpeed, bt, controlRange, maxAngle;
static PongConfiguration readFromFile(char* fileName);
};


#endif //IMOVE_PONGCONFIGURATION_H