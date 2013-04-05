
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
DEFINES += APRIL_LIBRARY
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
    ../../../april/april_debug.cc \
    ../../../april/logic/world.cc \
    ../../../april/logic/uniqueid.cc \
    ../../../april/logic/actor.cc \
    ../../../april/logic/factory.cc \
    ../../../april/logic/component.cc \
    ../../../april/logic/dna.cc \
    ../../../april/logic/dnaview.cc \
    ../../../april/logic/sensorfactory.cc \
    ../../../april/logic/eventfactory.cc \
    ../../../april/logic/actuatorfactory.cc \
    ../../../april/logic/actorfactory.cc \
    ../../../april/logic/sensor.cc \
    ../../../april/logic/reflex.cc \
    ../../../april/logic/event.cc \
    ../../../april/logic/brain.cc \
    ../../../april/logic/actuator.cc \
    ../../../april/logic/brainfactory.cc \
    ../../../april/logic/reflexfactory.cc \
    ../../../april/logic/actorcomp.cc \
    ../../../april/logic/eventline.cc \
    ../../../april/logic/eventdata.cc \
    ../../../april/logic/director.cc

HEADERS += \
    ../../../april/april_version.h \
    ../../../april/aprillibrary.h \
    ../../../april/april_global.h \
    ../../../april/april_debug.h \
    ../../../april/april_config.h \
    ../../../april/april.h \
    ../../../april/logic/world.h \
    ../../../april/logic/uniqueid.h \
    ../../../april/logic/actor.h \
    ../../../april/logic/component.h \
    ../../../april/logic/factory.h \
    ../../../april/logic/dna.h \
    ../../../april/logic/dnaview.h \
    ../../../april/logic/eventfactory.h \
    ../../../april/logic/actuatorfactory.h \
    ../../../april/logic/sensorfactory.h \
    ../../../april/logic/actorfactory.h \
    ../../../april/logic/reflex.h \
    ../../../april/logic/event.h \
    ../../../april/logic/brain.h \
    ../../../april/logic/actuator.h \
    ../../../april/logic/sensor.h \
    ../../../april/logic/brainfactory.h \
    ../../../april/logic/reflexfactory.h \
    ../../../april/logic/actorcomp.h \
    ../../../april/logic/eventline.h \
    ../../../april/logic/eventdata.h \
    ../../../april/logic/director.h

OTHER_FILES += \
    ../../../april/april.dox

