#!/bin/bash
set -e
mkdir -p ./config/
./build/bin/calibration ./config/AulaShuttle.yml 1 1920 1080
