#!/bin/bash
set -e
rm -r ./config/
mkdir -p ./config/
./dist/calibration ./config/test.yml ./calibration/test/camera_projector_transformation/20160502_171057_640.jpg 480 336 9 6
./dist/scene ./config/test.yml ./calibration/test/camera_projector_transformation/20160502_171057_test_640.jpg
