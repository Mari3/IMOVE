#!/bin/bash
set -e
rm -r ./config/
mkdir -p ./config/
#./dist/calibration ./config/test.yml 1 1024 768
./dist/scene ./config/test.yml 1 
