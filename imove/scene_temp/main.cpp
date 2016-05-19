#include <iostream>
#include "test/LightsManager.h"

using namespace std;

int main() {

    //get random number gen going
    time_t t;
    srand((unsigned)time(&t));

    LightsManager manager;
    manager.run();

}