#!/bin/bash
set -e
mkdir -p ./config/
./dist/calibration ./config/test.yml 0 1920 1027
