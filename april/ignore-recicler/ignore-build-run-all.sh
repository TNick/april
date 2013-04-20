#!/bin/bash
export QTDIR=/media/data/trunks/qt/Qt5.0.1-sdk/5.0.1/gcc_64
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/media/data/my-dev/april
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/media/data/my-dev/libbbb-code
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$QTDIR/include/QtCore
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$QTDIR/include
./build-run-all.sh

