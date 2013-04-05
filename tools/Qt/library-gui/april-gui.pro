
#######################################################
#             Building a dynamic library              #
#######################################################
TEMPLATE = lib
CONFIG(debug, debug|release) {
	TARGET = april-gui_debug
} else {
	TARGET = april-gui
}
CONFIG += dll warn_on
DEFINES += APRIL_LIBRARY
DEFINES += APRIL_GUI_LIBRARY
QT += core gui
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets
INCLUDEPATH += ../../..

#######################################################
#                     Components                      #
#######################################################

include( "../version.pri" )
include( "../local_defs.pri" )


# This is a hack
# On windows gcc(?) appends a 0 to the name of the
# generated file, so users of the library are
# unable to find it.
# The version is defined in version.pri file
win32 {

VERSION=

}

CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug
} else {
	LIBS += -lbbb
}


#######################################################
#       Where to output the files we generate?        #
#######################################################
isEmpty( DESTDIR ) {
	DESTDIR	= ../../../build
}
isEmpty( OBJECTS_DIR ) {
	OBJECTS_DIR = ./tmp
}
isEmpty( MOC_DIR ) {
	MOC_DIR = ./tmp
}
isEmpty( UI_DIR ) {
	UI_DIR = ./tmp
}


#######################################################
#                    Components                       #
#######################################################

SOURCES += \
    ../../../april/gui/worlds/worldqscene.cc

HEADERS += \
    ../../../april/gui/worlds/worldqscene.h

