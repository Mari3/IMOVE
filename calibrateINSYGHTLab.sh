#!/bin/bash
set -e
mkdir -p ./config/
./dist/calibration ./config/INSYGHTLab.yml 1 1024 750
