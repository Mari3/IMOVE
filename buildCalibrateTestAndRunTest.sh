#!/bin/bash
set -e
clear
./build.sh
./calibrateTest.sh
./runTest.sh
