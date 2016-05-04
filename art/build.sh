#!/bin/bash
set -e
mkdir -p build
pushd build >> /dev/null
	cmake ../src
	make
popd >> /dev/null

mkdir -p dist
mv build/application dist/application
rm -r build
