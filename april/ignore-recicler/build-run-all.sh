#!/bin/bash

for dir in */; do 
    pushd $dir > /dev/null
    ./build-run.sh
    popd > /dev/null
done
