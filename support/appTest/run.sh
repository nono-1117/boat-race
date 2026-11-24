#!/bin/bash

export LD_LIBRARY_PATH=./libs:./libphysics/Debug

echo "Running App"
./Debug/bin/apptest
