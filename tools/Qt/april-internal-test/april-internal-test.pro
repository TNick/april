
#######################################################
#        Building a stand-alone GUI application       #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = internal-test_debug
} else {
	TARGET = internal-test
	DEFINES += QT_NO_DEBUG
}
CONFIG += console warn_on
DEFINES += APRIL_INTERNAL_TESTS=1
INCLUDEPATH += ../../..
QT += core gui network
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets


#######################################################
#              Use the dynamic library                #
#######################################################
LIBS += -L../build
CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lapril_debug -lapril-cmd_debug -lapril-gui_debug
} else {
	LIBS += -lbbb -lapril -lapril-cmd -lapril-gui
}


#######################################################
#                     Components                      #
#######################################################

include( "../version.pri" )
include( "../local_defs.pri" )

# google test library
LIBS += -lgtest_main -lgtest


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
    ../../../april/tests/aprillibrary.cc \
    ../../../april/tests/world.cc \
    ../../../april/tests/dna.cc \
    ../../../april/tests/actor.cc \
    ../../../april/tests/actuator.cc \
    ../../../april/tests/sensor.cc \
    ../../../april/tests/reflex.cc \
    ../../../april/tests/event.cc \
    ../../../april/tests/brain.cc \
    ../../../april/tests/simplerun.cpp \
    ../../../april/tests/eventline.cc \
    ../../../april/tests/plugins.cc \
    ../../../april/tests/saveload.cc \
    ../../../april/tests/saveload2.cc \
    ../../../april/tests/apriltokenizer.cc
 

