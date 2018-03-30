# IMOVE - A Track and Project Framework

This Repository contains the source code and documentation of the IMOVE project. This project is a framework that combines image processing, calibration techniques and computer graphics to create an interactive experience for the user, using a projector and a camera.

## Building the project
The project is built using CMake with gcc/g++. The easiest way to build is to run the build script from terminal (./build.sh from repository root).

### Dependencies
To build this project you will need to have 3 libraries installed on your system: OpenCV 3.4.1, SFML 2.4.2, boost 1.66.0. The project should be able to find the libraries automatically.

## Applications
The following applications are built:

### calibration
This is a separate application used to calibrate the program to configure certain setup-specific variables, such as the location of the projection in the camera view.
From cli (run from repository root): ./build/bin/calibration ./config/<yourconfigfile>.yml <camera id> <projector resolution width> <projector resolution height>
or put the desired settings in the calibrate script and run ./calibrate.sh

### imove
This is the main application. It processes the camera input and turns it into the graphics that are to be projected by the projector. When running imove, it automatically splits itself up in two other applications, imove_peopleextractor which handles detection and imove_scene which handles the graphics being projected.
From cli (run from repository root): ./build/bin/imove ./config/<system config file>.yml ./config/<scene config file>.yml
or put the desired settings in the run script and run ./run.sh


## Parts of the IMOVE framework
IMOVE consists of a number of interacting parts. The diagram below shows the high-level structure of the project.
![Structure](IMOVEstructure.png)
