# Calibration and Configuration
The calibration and configuration gives the framework the ability to adapt to different kinds of setups. To make sure the system functions correctly, it needs to be calibrated and configured regularly. Calibration is a built-in functionality in the framework that can be ran separately to setup elements like the projection field inside the camera frame. The values from calibration are written to a configuration file. The configuration files give access to these values, so they can be edited manually, and other values that are not included in the calibration part.

## Calibration
As mentioned in the documentation on [running the framework](https://github.com/Mari3/ICA/blob/master/Documentation/InstallBuildRun.md), calibration can be started by running the calibration script or command from terminal. This opens up 5 windows. Each window has a different name that describes its purpose:
- **Calibrate projection**: In this window, four crosses need to be placed on the corners of the projection inside the camera frame to mark the boundaries of the projection. When hovering over the frame, the mouse will have a little cross attached to it in the color of the next corner you need to mark. Simply click the corner of the projection with the same color to move it to a new location.
- **Calibrate meter**: The size of a person inside of a frame depends on the height of the camera. To support different heights, calculations for detection and scene are based on the amount of pixels that corresponds to one meter. In this window, two crosses can be moved in place in the same way as the projection. The distance between the two crossed should respond to one physical meter.
- **Eliminate projection, projector, projection**: The framework includes a mechanic to cancel out the projection on the camera frames so the system does not start tracking the movement of what is being projected but only the people. These 3 windows are used to calibrate this projection elimination. This mechanic is currently not operational however.
When everything is calibrated, the application can be exited using *ctrl+c* and the values will be written to the configuration files.

## Configuration
As mentioned in the structure documentation (TODO: add link), the *config* folder contains YAML files used for configuration. These files contain parameter values that can be used in the system and are different for each setup or scene. There are two types of configuration files: system config files and scene config files.

#### System configuration
The system config files contain general information about the setup that is used throughout the system. After calibration, all values are written to the system file specified in the calibration script or command. Apart from the calibration values, these files also contain other parameter values that need to be modified manually. The list below contains all parameters, calibration and manual, that need to be specified when setting up, along with a short description. The parameters that are not mentioned below should be ignored. Keep in mind that calibration parameters can also be changed manually.
- **Debug mode** (manual): When this value is set to 0, the scene window is opened when the main application is started. If it is set to 1, more windows appear that can be used for debugging detection. More on these windows in the *Debug Mode* section below.
- **Camera device** (manual): This is the id of the camera being used. Most laptops have a built-in camera which has id 0. A usb camera will then have id 1. When there is no built-in camera, the external camera will have id 0.
- **Resolution camera** (manual): Resolution of the camera.
- **Resolution projector** (manual): Resolution of the projector.
- **Fullscreen projector** (manual): When this value is set to 1, the scene window will be set to fullscreen when running the system. When set to 0, the scene will remain a separate window.
- **Projection top/bottom left/right** (calibration): Coordinates of the corners of the projection inside the camera frame
- **Meter camera** (calibration): Number of pixels on the camera frame that corresponds a meter in reality.
- **Minimum area blobs** (manual): To detect people in a camera frame, a technique called blob detection is used. This is the parameter that specifies the minimum area a blob must have to qualify as a person in the scene.
- **Minimum distance blobs** (manual): For the same technique, the minimum distance between blobs is also needed and differs for every setup.

An example of a system configuration file is *test.yml* in the *config* folder.

#### Scene configuration
Elements in the scene can also vary for every setup. It is also very useful to have all parameters in a scene in one place so it is easily and highly customizable. Therefore, it is recommended to use a scene configuration file. Scene parameters are different for every scene so scene configuration files have to be custom made. It is not mandatory for a scene to use a config file. An example of a system configuration file is *examplesceneconfig.yml* in the *config* folder. More examples can be found in the *config* folders on the [lighttrails branch](https://github.com/Mari3/ICA/tree/lighttrails) or the [pong branch](https://github.com/Mari3/ICA/tree/pong).

## Debug Mode
When running the framework, one window, the scene window called *frame*, will always open because this contains the graphics that have to be projected. When debug mode is enabled, 4 other windows will open that provide information on different back-end stages of the application. Below is a list of all windows and what they show.

- **Frame:** The frame window displays the scene that needs to be projected onto the floor. When a projector is attached to your computer, the frame should open on the projector and the other windows on your screen. If this is not the case, change the order settings of the screens or rearrange the windows.
- **Detected people on projection/camera:** These windows show two stages of the detection process. One window shows the detection of people through movement and the other shows which people have been identified with a location and id.
- **Eliminate projection camera frame:** This window shows the frame after projection elimination. The projection elimination feature is currently not enabled.
- **Projector:** This window is a zoomed-in version of the frame with detected people showing only what is inside the boundaries of the projection.
