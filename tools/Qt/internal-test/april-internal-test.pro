
#######################################################
#        Building a stand-alone GUI application       #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = internal-test_debug
} else {
	TARGET = digibrain-internal-test
	DEFINES += QT_NO_DEBUG
}
CONFIG += console warn_on build_all debug_and_release
INCLUDEPATH += ../../..
QT += core gui network testlib
greaterThan( QT_MAJOR_VERSION, 4 ): QT += widgets


#######################################################
#              Use the dynamic library                #
#######################################################
LIBS += -L../../../build
CONFIG(debug, debug|release) {
	LIBS += -ldigibrain_debug
} else {
	LIBS += -ldigibrain
}



#######################################################
#                     Components                      #
#######################################################

include( "../version.pri" )
include( "../local_defs.pri" )

# google test library
LIBS += -lgtest_main -lgtest

CONFIG(debug, debug|release) {
	LIBS += -lbbb_debug -lmemy_debug -lqtcp_debug
} else {
	LIBS += -lbbb -lmemy -lqtcp
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
	../../../libdigibrain/test/dblibrary_test.cc \
	../../../libdigibrain/test/dbpattern_test.cc \
    ../../../libdigibrain/test/dbadapter_test.cc

SOURCES += \
	../../../libdigibrain/test/dbagent_test.cc

SOURCES += \
    ../../../libdigibrain/test/dbinpqueue_test.cc

