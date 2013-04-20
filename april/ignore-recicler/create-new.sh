#!/bin/bash -e

NEWNAME=$1
pushd   ../.. > /dev/null
BPTH=$(pwd)
popd > /dev/null

if [ "x$1" == "x" ]; then
    echo "Provide a name as argument"
    exit 0
fi

if [ -d "$BPTH/april/examples/$NEWNAME" ]; then
    echo    "$NEWNAME already exists"
    exit 1
fi
mkdir "$BPTH/april/examples/$NEWNAME"




echo    "
#include <iostream>

using namespace std;

int main ()
{
	cout << \"Hello World!\\n\";
	return 0;
}
" > $BPTH/april/examples/$NEWNAME/$NEWNAME.cc
git add $BPTH/april/examples/$NEWNAME/$NEWNAME.cc




echo "namespace   april    {

/**

\page	$NEWNAME   Example  - 

<br><br><hr>
<table width=100%><tr><td> \ref $NEWNAME </td><td align=right> \ref $NEWNAME </td>
*/

}   //  namespace   april
" > $BPTH/april/docs/examples/$NEWNAME.dox
git add $BPTH/april/docs/examples/$NEWNAME.dox





echo "SUBDIRS += $NEWNAME
" >> $BPTH/tools/Qt/examples/examples.pro
mkdir $BPTH/tools/Qt/examples/$NEWNAME

echo    "exists(../../local_defs.pri) include(../../local_defs.pri)
INCLUDEPATH += ../../../..
SOURCES += ../../../../april/examples/$NEWNAME/$NEWNAME.cc
OTHER_FILES += ../../../../april/docs/examples/$NEWNAME.dox
LIBS += -L\$\$PWD/../../../../build
CONFIG(debug, debug|release) {
	LIBS += -lapril_debug -lbbb_debug
} else {
    LIBS += -lapril -lbbb
}
" > $BPTH/tools/Qt/examples/$NEWNAME/$NEWNAME.pro
git add $BPTH/tools/Qt/examples/$NEWNAME/$NEWNAME.pro
