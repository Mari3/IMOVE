#!/bin/bash
set -e
clear
g++ -std=c++11 -g -Wall -pedantic -Werror main_test.cpp ImoveSceneManager_test.cpp ../../scene_interface/src/ExtractedpeopleQueue.cpp ../../scene_interface/src/Vector2.cpp ../../scene_interface/src/Person.cpp Interface/Person.cpp Util/Vector2.cpp -o receiver -lboost_system -lpthread -lboost_thread -lrt
gdb -ex run --args ./receiver
