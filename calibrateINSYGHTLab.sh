#!/bin/bash
set -e
mkdir -p ./config/
./dist/calibration ./config/INSYGHTLab.yml 1 800 800 
