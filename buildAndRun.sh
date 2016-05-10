#!/bin/bash
set -e
clear
./build.sh
./dist/calibration ./calibration/test/camera_projector_transformation/20160502_171057_640.jpg 480 336 9 6
./dist/art
