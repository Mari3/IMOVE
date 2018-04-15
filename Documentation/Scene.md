# Scene
The scene is what will be projected onto the floor and what participants will be interacting with. It consists of graphics generated based on people's locations.

## Structure
The scene consists of 3 parts:
- **Scene:** The core functionality of the scene
- **Windows:** The part responsible for displaying the scene
- **Manager:** The part responsible for receiving, preparing and passing cross-thread information and calibration configurations

#### Scene

#### Windows
The scene window displays the graphics generated in the scene part.

#### Manager
The manager receives the information about detected people in the scene that was sent over from the thread the detection part runs on, prepares it and provides it to the scene. It does the same for calibration and scene configurations. The manager also sends frames that the scene generated to the window to display the result. 

## Creating a new scene
