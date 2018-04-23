#!/bin/bash
set -e
mkdir -p ./config/
./build/bin/calibration ./config/test.yml 0 1920 1200
