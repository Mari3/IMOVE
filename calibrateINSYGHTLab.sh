#!/bin/bash
set -e
mkdir -p ./config/
./build/calibration/calibration ./config/INSYGHTLab.yml 1 1024 750
