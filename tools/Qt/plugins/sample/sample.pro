#######################################################
#             Building a dynamic library              #
#######################################################
TEMPLATE = lib
CONFIG(debug, debug|release) {
	TARGET = sample_debug
} else {
	TARGET = sample
}
CONFIG += plugin warn_on
QT += core gui
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets
PLUGIN_NAME = sample
INCLUDEPATH += ../../../..

#######################################################
#                     Components                      #
#######################################################

include( "../../version.pri" )
include( "../../local_defs.pri" )


# This is a hack
# On windows gcc(?) appends a 0 to the name of the
# generated file, so users of the library are
# unable to find it.
# The version is defined in version.pri file
win32 {

VERSION=

}

LIBS += -L../../build
CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lapril_debug
} else {
	LIBS += -lbbb -lapril
}

#######################################################
#       Where to output the files we generate?        #
#######################################################
isEmpty( DESTDIR ) {
	DESTDIR	= ../../build
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
    sample.cc

HEADERS += sample.h

