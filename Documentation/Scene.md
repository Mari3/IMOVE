# Scene
The scene is what will be projected onto the floor and what participants will be interacting with. It consists of graphics generated based on people's locations.

## Structure
The scene source code can be found in the *imove_scene* folder and consists of 3 parts:
- **Scene:** The core functionality of the scene
- **Windows:** The part responsible for displaying the scene
- **Manager:** The part responsible for receiving, preparing and passing cross-thread information and calibration configurations

#### Scene
In the *Scene* folder, the classes containing the core functionality of a scene can be found. The folder contains some base classes that can be built and expanded upon to create a scene, a *Util* folder containing some utility classes and the folder containing all scene-specific classes, in this case called *Example*. The standard scene is a simple example that uses some basic elements included in the framework for building scenes. It draws a black background and a circle on each person's location.   

#### Windows
The scene window displays the graphics generated in the scene part.

#### Manager
The manager receives the information about detected people in the scene that was sent over from the thread the detection part runs on, prepares it and provides it to the scene. It does the same for calibration and scene configurations. The manager also sends frames that the scene generated to the window to display the result. 

## Creating a new scene
As long as the scene provides a frame to the scene window, it does not matter how the scene is implemented. However, to facilitate creating a new scene, a scene framework is provided. This includes a suggested structure and some helpful classes and it provides an easy way to integrate the scene into the system. 

A list all scene classes and their use:
- **Scene:** First of all, your scene needs a main class that is a child class of the class Scene. In the example, this main scene class is called *ExampleScene*. This class needs to override the functions *draw* and *processPeople*. *draw* specifies how the scene needs to be drawn and *processPeople* specifies how people's locations are processed and used.
- **SceneConfiguration:** It is recommended to use a [configuration file](https://github.com/Mari3/ICA/blob/master/Documentation/CalibrationAndConfiguration.md) to make your scene easily modifiable. All values that need some experimenting to get right or could be dependent on the setting should be written in a configuration file. The *SceneConfiguration* class should then be expanded to read out all the values. If needed, this class also provides a way to access calibration values like the resolution of the projector. 
- **Action and Condition:** The functionality of a scene can be defined using actions and conditions.    
- **Effect:**
- **Util/Repository:** It is recommended to use repositories to store entities, espacially entities that are attatched to people's locations. 
- **Util/VectorRepository:**
- **Util/Timer:**




To see some examples of scenes created with this framework, check out the [pong branch](https://github.com/Mari3/ICA/tree/pong) and the [lighttrails branch](https://github.com/Mari3/ICA/tree/lighttrails) of this repository.
