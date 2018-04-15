# Structure

## Structure of the framework
IMOVE consists of a number of interacting parts. The diagram below shows the high-level structure of the framework.

![Structure](https://github.com/Mari3/ICA/blob/master/IMOVEstructure.png)

###### Calibration
The calibration part can be used to modify settings to make the system adapt to different setups. All settings modified during calibration are written to configuration files.

###### People Extractor
This part is responsible for detecting and identifying people in the scene. It reads out values from the config files to adapt to the situation, for example the height of the camera, and analyses each frame to extract people's locations.## 

###### Interface
The people extractor and scene each run on their own threads which means that an interface is needed for them to be able to communicate. That is what the interface entities are responsible for, communicating the people extractor's results to the scene across threads. It also provides a mapping functionality of locations from camera frame to projection scene.

###### Scene
The scene generates graphics based on the received locations which is what gets projected for the users to see and what they can interact with.

## Structure of the Project
The project consists of many files and folders. This is a quick overview of what contains what and what can be found where.
- **calibration:** All files regarding the calibration application
- **Documentation:** Documentation on the framework
- **imove:** Files for the main application
- **imove_peopleextractor:** All files for the detection part that extracts people's locations, more information on this part [here](https://github.com/Mari3/ICA/blob/master/Documentation/Detection.md).
- **imove_scene:** All files for the scene part which is what will be projected, more information about the scene can be found [here](https://github.com/Mari3/ICA/blob/master/Documentation/Scene.md)
- **modules:** Contains a cmakes file that searches for the SFML library
- **peopleextractor_interface_sma:** Contains files regarding the interface between the people extractor and the shared memory used to communicate across threads.
- **scene_interface_sma:** All files that take care of the communication between the scene and the shared memory.
- **scene_interface:** Standard classes used by entities such as *Projection*, *PeopleExtractor* and *Scene* to adapt to the scene's specifications. 
- **util:** Contains some generic classes that can be used as a base in different parts of the system
