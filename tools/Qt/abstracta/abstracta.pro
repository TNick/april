
#######################################################
#     Building a stand-alone console application      #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = abstracta_debug
} else {
	TARGET = abstracta
	DEFINES += QT_NO_DEBUG
}
CONFIG += console warn_on
INCLUDEPATH += ../../..
QT += core
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

#######################################################
#              Use the dynamic library                #
#######################################################
LIBS += -L../build
CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lapril_debug
} else {
	LIBS += -lbbb -lapril
}


#######################################################
#                     Components                      #
#######################################################

include( "../version.pri" )
include( "../local_defs.pri" )

# argtable
LIBS += -largtable2

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


# Windows specific icon
RC_FILE = ../../../april/abstracta/win-res.rc

# MacOSX specific icon
ICON = ../../../april/abstracta/abstracta.icns


SOURCES += \
    ../../../april/abstracta/abstracta-main.cc \
    ../../../april/abstracta/aaoutput.cc \
    ../../../april/abstracta/aatokenizer.cc \
    ../../../april/abstracta/commandmap.cc \
    ../../../april/abstracta/abstractapril.cc \
    ../../../april/abstracta/modules/aaworld.cc \
    ../../../april/abstracta/aamodule.cc

RESOURCES += \
    ../../../april/abstracta/abstracta.qrc

HEADERS += \
    ../../../april/abstracta/aaoutput.h \
    ../../../april/abstracta/aatokenizer.h \
    ../../../april/abstracta/commandmap.h \
    ../../../april/abstracta/abstractapril.h \
    ../../../april/abstracta/modules/aaworld.h \
    ../../../april/abstracta/aamodule.h



