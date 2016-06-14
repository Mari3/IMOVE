#!/bin/bash
set -e
mkdir -p build
pushd build >> /dev/null
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j4
#	make
popd >> /dev/null

#mkdir -p dist
#mv build/calibration/calibration dist/calibration
#mv build/imove_scene/src/imove_scene dist/imove-scene
#mv build/imove_peopleextractor/src/imove_peopleextractor dist/imove-peopleextractor
