
#######################################################
#        Building a stand-alone GUI application       #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = AprilDream_debug
} else {
	TARGET = AprilDream
	DEFINES += QT_NO_DEBUG
}
CONFIG += warn_on
INCLUDEPATH += ../../..
QT += core gui
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets


#######################################################
#              Use the dynamic library                #
#######################################################
LIBS += -L../../../build
CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lapril_debug -lapril-gui_debug
} else {
	LIBS += -lbbb -lapril -lapril-gui
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


# Windows specific icon
RC_FILE = ../../../april/aprildream/win-res.rc

# MacOSX specific icon
ICON = ../../../april/aprildream/aprildream.icns



