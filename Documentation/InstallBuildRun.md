# How to Install, Build and Run the IMOVE Framework

The IMOVE framework is written in C++ and can be built and run using simple terminal/cli commands. Below is a step-by-step guide on what to install, how to build and how to run the project.

## What To Install

This is an overview of everything that needs to be installed on your system to get the framework running.

### Tools
This project is written in C++ and therefore requires a C++ compiler. It has been successfully built using gcc and g++ from the GNU Compiler Collection.

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


## Building

Once all dependencies have been installed, building can easily be done using the build script provided. Simply run
```
$ ./build.sh
```
from the repository root and the project will start building. After the initial build, some computers complain when the same script is used to rebuild after changes because a build directory already exists. In that case, use the rebuild script instead of the build script in the same way. It automatically removes the existing build directory before building.

## Running
The building process creates 4 executables but only 2 of them should be run separately: calibration and imove.

#### calibration
This is a separate application used to calibrate the program to configure certain setup-specific variables, such as the location of the projection inside the camera view.

To run this application, run the following cli command from the repository root:
```
$ ./build/bin/calibration ./config/<system config file>.yml <camera id> <projector resolution width> <projector resolution height>
```
All settings configured during the calibration are stored in a YAML file. An example of a calibration config file is *config/test.yml*. Camera id specifies which camera is to be used. A built-in camera usually has id *0* and a camera connected through usb *1*. The last two parameters that need to be specified when running the calibration are the projector resolution height and width in pixels.   

Alternatively, all desired settings can be put in the calibrate script which simplifies the command to:
```
$ ./calibrate.sh
```
This file also contains an example of how to run the calibration executable. Multiple scripts can be created in a similar fashion with different settings for different set-ups.

#### imove
This is the main application. It processes the camera input and turns it into the graphics that are to be projected by the projector. When running imove, it automatically splits itself up in two other applications, imove_peopleextractor which handles detection and imove_scene which handles the graphics being projected. That is why there are 4 executables after building the project. The imove executable starts each of the 2 remaining executables on a separate thread.

To run the imove application, run the following cli command from the repository root:
```
$ ./build/bin/imove ./config/<system config file>.yml ./config/<scene config file>.yml
```
The system config file specified here should be the same one that was used specified in the calibration command. During calibration, the settings are written into this file and in the main application the settings are read so they can be used in the system. Because this framework is designed to be flexible and adaptable enough to work in many different circumstances, both the tracking and projection system need some calibration and modification. Tracking is a fixed part of the system and therefore the tracking settings are included in the system config. The scene however is a modifiable part which can require its own settings which should be put into a separate file. That file can be specified as the scene config file in the command.

Similar to the calibration, a run script has been provided to simplify the command:
```
$ ./run.sh
```
This file also contains an example of how to run the imove executable. Multiple scripts can be created in a similar fashion with different settings for different set-ups.
