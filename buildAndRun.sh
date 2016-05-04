#!/bin/bash
set -e
clear
./build.sh
./dist/application ./test/20160502_171057_640.jpg ./test/pattern_480.png
