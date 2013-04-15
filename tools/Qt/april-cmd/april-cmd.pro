
#######################################################
#             Building a dynamic library              #
#######################################################
TEMPLATE = lib
CONFIG(debug, debug|release) {
	TARGET = april-cmd_debug
} else {
	TARGET = april-cmd
}
CONFIG += dll warn_on
DEFINES += APRIL_LIBRARY
QT += core gui
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

LIBS += -L../build
CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lapril_debug
} else {
	LIBS += -lbbb -lapril
}


#######################################################
#       Where to output the files we generate?        #
#######################################################
isEmpty( DESTDIR ) {
	DESTDIR	= ../build
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
    ../../../april/cmd/commandmap.cc \
    ../../../april/cmd/aatokenizer.cc \
    ../../../april/cmd/aamodule.cc \
    ../../../april/cmd/modules/aaworld.cc \
    ../../../april/cmd/modules/aaplugins.cc \
    ../../../april/cmd/modules/aadna.cc \
    ../../../april/cmd/modules/aaapril.cc

HEADERS += \
    ../../../april/cmd/commandmap.h \
    ../../../april/cmd/aatokenizer.h \
    ../../../april/cmd/aamodule.h \
    ../../../april/cmd/modules/aaworld.h \
    ../../../april/cmd/modules/aaplugins.h \
    ../../../april/cmd/modules/aadna.h \
    ../../../april/cmd/modules/aaapril.h

