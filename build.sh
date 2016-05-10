#!/bin/bash
set -e
mkdir -p build
pushd build >> /dev/null
	cmake ..
	make
popd >> /dev/null

mkdir -p dist
mv build/calibration dist/calibration
mv build/scene dist/scene
rm -r build
