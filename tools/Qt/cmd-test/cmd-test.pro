
#######################################################
#        Building a stand-alone GUI application       #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = cmd-test_debug
} else {
	TARGET = cmd-test
	DEFINES += QT_NO_DEBUG
}
CONFIG += console warn_on
INCLUDEPATH += .
QT += core
QT += widgets
QT -= gui

#######################################################
#              Use the dynamic library                #
#######################################################
# LIBS += -L../build
# CONFIG(debug, debug|release) {
#	LIBS += -lbbb_debug -lapril_debug -lapril-cmd_debug -lapril-gui_debug
#} else {
#	LIBS += -lbbb -lapril -lapril-cmd -lapril-gui
#}


#######################################################
#                     Components                      #
#######################################################

include( "../local_defs.pri" )

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
    main-cmd-test.cc \
    target.cc \
    cmdtest.cc \
    doevents.cc

HEADERS += \
    target.h \
    cmdtest.h \
    doevents.h

