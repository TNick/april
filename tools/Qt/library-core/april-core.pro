
#######################################################
#             Building a dynamic library              #
#######################################################
TEMPLATE = lib
CONFIG(debug, debug|release) {
	TARGET = april_debug
} else {
	TARGET = april
}
CONFIG += dll warn_on
DEFINES += DIGIB_LIBRARY
QT += core gui
INCLUDEPATH += ../../..


#######################################################
#                     Components                      #
#######################################################

include( "../version.pri" )
include( "../local_defs.pri" )
include( "../library-sources.pri" )

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
    ../../../april/aprillibrary.cc \
    ../../../april/april_debug.cc

HEADERS += \
    ../../../april/april_version.h \
    ../../../april/aprillibrary.h \
    ../../../april/april_global.h \
    ../../../april/april_debug.h \
    ../../../april/april_config.h \
    ../../../april/april.h

OTHER_FILES += \
    ../../../april/april.dox

