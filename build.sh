#!/bin/bash
set -e
mkdir -p build
pushd build >> /dev/null
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j
#	make
popd >> /dev/null

mkdir -p dist
mv build/calibration/calibration dist/calibration
mv build/imove-scene/src/imove-scene dist/imove-scene
mv build/imove-peopleextractor/src/imove-peopleextractor dist/imove-peopleextractor
