# What To Install

This is an overview of everything that needs to be installed on your system to get the framework running.

### Tools
This project is written in C++ and therefore requires a C++ compiler. It has been succesfully built using gcc and g++ from the GNU Compiler Collection.

To build the project, CMake is required. It was last verified to work with CMake version 3.11.0.


### Libraries
The framework depends on 3 external libraries:
- OpenCV
- SFML
- boost

##### OpenCV
This library is an open source computer vision library used in the detection part of the framework. The latest version that has been verified to work with the framework is 3.4.1.

##### SFML
SFML is a multimedia library which is used in this project to generate the projected graphics. The framework is compatible with version 2.4.2.

##### Boost
Because this framework combines computer vision to analyse frames and generation of graphics to project, it requires two processes running on separate threads. The boost library provides the ability to manage threads and memory to keep the processes separate and provide communication through shared memory. The latest verified version that works is 1.66.0. 
