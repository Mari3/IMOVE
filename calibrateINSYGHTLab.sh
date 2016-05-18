#!/bin/bash
set -e
mkdir -p ./config/
./dist/calibration ./config/test.yml 1 "./calibration/test/camera_projector_transformation/big_buck_bunny_1080p_h264.mov"
