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
- **Action and Condition:** The functionality of a scene can be defined using actions and conditions. As the names suggest, a condition checks if a certain event occurs and an action describes what needs to happen as a result of an action. The *Scene* class has a vector of actions and conditions and so does your new scene since it is a child of the *Scene* class. It also has an update function where actions and conditions are processed. In *update*, the *check* methods are called on each condition. This method checks each condition and adds the resulting actions to the provided vector. Next in the *update* function, the *execute* method is called on each action to perform it and the *isDone* function to check if the action should stop and if there are any follow-up actions. Conditions can be created from base class *Condition* and can be added to the scene by adding it to the conditions vector in the main class of the new scene. Actiond can be created from base class *Action*. If it is a constant action or an action that starts when the system starts, it can be added to the actions vector in the main class of the new scene. If it depends on a condition, it can be added to the actions vector in the condition's *check* method. A good example of how to work with conditions and actions can be seen in the [pong branch](https://github.com/Mari3/ICA/tree/pong/imove_scene/src/Scene/Pong).  
- **Effect:** Effects are extra parts that can be added to an action. On an action, the *execute* method can be called to carry out the action and *updateEffects* can be called to perform the attached effects.
- **Util/Repository:** It is recommended to use repositories to store entities, espacially entities that are attatched to people's locations. Repositories are custom wrappers that can be used with any container. To store locations, it is convenient to use a repository with a map as attribute. An example of a custom repository can be seen [here](https://github.com/Mari3/ICA/blob/master/imove_scene/src/Scene/Example/CircleRepository.h) and how it is used in a scene, [here](https://github.com/Mari3/ICA/blob/master/imove_scene/src/Scene/Example/ExampleScene.cpp). 
- **Util/VectorRepository:** This is more specific version of a repository that already has a vector incorporated in it.
- **Util/Timer:** The timer class can be used in the case of timed conditions, action, effects, etc.

To integrate a new scene, a few changes need to be made in the file [ImoveSceneManager.cpp](https://github.com/Mari3/ICA/blob/master/imove_scene/src/ImoveSceneManager.cpp). Your new scene needs to be included at the top of the file. In the constructor of the manager, *this->scene* needs to be initialized as an entity of your new scene. That causes the system to switch to the new scene.

To see some examples of scenes created with this framework, check out the [pong branch](https://github.com/Mari3/ICA/tree/pong/imove_scene/src) and the [lighttrails branch](https://github.com/Mari3/ICA/tree/lighttrails/imove_scene/src) of this repository.
