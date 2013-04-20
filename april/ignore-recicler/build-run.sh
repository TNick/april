#!/bin/bash -e

SOURCE=./e-1-2.cc
EXEOUT=./e-1-2

# generate the executable
g++ $SOURCE -o $EXEOUT

# run the executable
$EXEOUT

# remove the resulted executable; supress warnings
rm $EXEOUT > /dev/null

