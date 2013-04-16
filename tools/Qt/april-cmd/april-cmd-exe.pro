
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
    ../../../april/cmd/aprilmodule.cc \
    ../../../april/cmd/apriltokenizer.cc \
    ../../../april/cmd/modules/amodapril.cc \
    ../../../april/cmd/modules/amoddna.cc \
    ../../../april/cmd/modules/amodplugins.cc \
    ../../../april/cmd/modules/amodworld.cc \
    ../../../april/cmd/modules/amodid.cc \
    ../../../april/cmd/modules/amodactor.cc

HEADERS += \
    ../../../april/cmd/commandmap.h \
    ../../../april/cmd/aprilmodule.h \
    ../../../april/cmd/apriltokenizer.h \
    ../../../april/cmd/modules/amodapril.h \
    ../../../april/cmd/modules/amoddna.h \
    ../../../april/cmd/modules/amodplugins.h \
    ../../../april/cmd/modules/amodworld.h \
    ../../../april/cmd/modules/amodid.h \
    ../../../april/cmd/modules/amodactor.h

