
#######################################################
#                 Building a program                  #
#######################################################
TEMPLATE = app
CONFIG(debug, debug|release) {
	TARGET = april-cmd_debug
} else {
	TARGET = april-cmd
}
CONFIG += console warn_on
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
	LIBS += -lbbb_debug -lapril_debug -lapril-cmd_debug
} else {
	LIBS += -lbbb -lapril -lapril-cmd
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
    main-cmd-help.cc

OTHER_FILES += \
    ../../../april/docs/commands/w.dox \
    ../../../april/docs/commands/s.dox \
    ../../../april/docs/commands/r.dox \
    ../../../april/docs/commands/p.dox \
    ../../../april/docs/commands/module.dox.template \
    ../../../april/docs/commands/id.dox \
    ../../../april/docs/commands/e.dox \
    ../../../april/docs/commands/dna.dox \
    ../../../april/docs/commands/b.dox \
    ../../../april/docs/commands/april.dox \
    ../../../april/docs/commands/ak.dox \
    ../../../april/docs/commands/a.dox

