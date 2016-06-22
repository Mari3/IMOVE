#!/bin/bash
set -e
mkdir -p ./config/
./build/bin/calibration ./config/INSYGHTLabShuttle.yml 0 1024 768
