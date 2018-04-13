# Detection
The detection part is responsible for extracting people's locations from camera frames and is referred to as people extractor. It consists of 3 main parts:
- **Image Processing:** The core functionality of the people extractor
- **Windows:** The debug windows that show different stages of detection
- **Manager:** The entity responsible for passing the frames, communication with the interface and passing calibration values.

#### Image Processing
In image processing, each frame will be analysed for movement. It is built up out of 3 parts. The first part is the detector. The detector uses OpenCV's KNN background subtractor on each frame which results in a black frame with white areas, so-called *blobs*, where movement was detected. Next, OpenCV's blob detector is used to identify which blobs are people and which blobs are other movements or disturbances in the frame. The locations of the blobs that represent people are stored and passed to the second part, the identifier. This part matches locations from the previous frame with locations from the current frame to ... It also identifies whether a location/person is inside the projection field, a participant, is inside the camera field but not inside the projection field, a bystander, or has left the scene. The third part is the people extractor class itself which manages the other two parts by preparing the frame and sending it to the detector and passing the locations from the detector to the identifier.

#### (Debug) Windows
When debug mode is enabled, more on that [here](https://github.com/Mari3/ICA/blob/master/Documentation/CalibrationAndConfiguration.md), not only the scene window but 4 other windows will appear when running the main application, 2 of which show different stages of detection for debugging purposes. The list below is an overview of the different windows.
- **Detected people on camera:** This window shows the result of the detector, i.e. the result of the background subtraction and blob detection
- **Detected people on projection:**


#### Manager


