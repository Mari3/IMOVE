#!/bin/bash
set -e
mkdir -p ./config/
./build/bin/calibration ./config/INSYGHTLab.yml 1 1024 768
