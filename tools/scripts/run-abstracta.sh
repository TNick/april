#!/bin/bash

# path for libbbb dynamic library
BBB_PATH=""

# path for april binaries
APRIL_PATH=""

# set to empty string to work with release
# set to "_debug" to work with debug version
WITH_DEBUG="_debug"

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$BBB_PATH:$APRIL_PATH
$APRIL_PATH/abstracta$WITH_DEBUG
