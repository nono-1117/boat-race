#!/bin/bash

cmake --version

if [ -z $1 ]; then
	echo Missing Config param
	exit 1
fi

src=$(pwd)
prj=$(basename $src)
cfg=$1
opt=$2
installPath=$src/../runApp

echo $installPath

mkdir -p ../build
mkdir -p ../build/$prj
mkdir -p ../build/$prj/$cfg$opt
mkdir -p $installPath

cd ../build/$prj/$cfg$opt

cmake -DCMAKE_BUILD_TYPE=$cfg -DBUILD_SHARED_LIBS=ON -DCMAKE_PREFIX_PATH="~/Documents/coursRoyer/SFML/install/lib/cmake/SFML;~/Documents/coursRoyer/v2/install/libphysics/lib/cmake" -DCMAKE_INSTALL_PREFIX=$installPath $src

