#!/bin/bash
set -e
rm -r ./config/
mkdir -p ./config/
./dist/calibration ./config/test.yml 0 480 336
./dist/scene ./config/test.yml 0 
