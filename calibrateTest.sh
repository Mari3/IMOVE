#!/bin/bash
set -e
mkdir -p ./config/
./build/calibration/calibration ./config/test.yml 0 800 600
