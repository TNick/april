
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
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

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
RC_FILE = ../../../april/aprildream/win-res.rc

# MacOSX specific icon
ICON = ../../../april/aprildream/aprildream.icns

FORMS += \
    ../../../april/AprilDream/gui/mw.ui \
    ../../../april/AprilDream/gui/newworlddlg.ui \
    ../../../april/AprilDream/gui/pluginsdlg.ui \
    ../../../april/AprilDream/gui/dnaeditordlg.ui \
    ../../../april/AprilDream/gui/newactordlg.ui

HEADERS += \
    ../../../april/AprilDream/gui/mw.h \
    ../../../april/AprilDream/propertybrowser/qtvariantproperty.h \
    ../../../april/AprilDream/propertybrowser/qttreepropertybrowser.h \
    ../../../april/AprilDream/propertybrowser/qtpropertymanager.h \
    ../../../april/AprilDream/propertybrowser/qtpropertybrowserutils_p.h \
    ../../../april/AprilDream/propertybrowser/qtpropertybrowser.h \
    ../../../april/AprilDream/propertybrowser/qtgroupboxpropertybrowser.h \
    ../../../april/AprilDream/propertybrowser/qteditorfactory.h \
    ../../../april/AprilDream/propertybrowser/qtbuttonpropertybrowser.h \
    ../../../april/AprilDream/gui/dock.h \
    ../../../april/AprilDream/gui/dockworld.h \
    ../../../april/AprilDream/gui/docktree.h \
    ../../../april/AprilDream/gui/dockids.h \
    ../../../april/AprilDream/gui/dockcrtsel.h \
    ../../../april/AprilDream/gui/sceneviewer.h \
    ../../../april/AprilDream/gui/newworlddlg.h \
    ../../../april/AprilDream/gui/pluginsdlg.h \
    ../../../april/AprilDream/gui/dnaeditordlg.h \
    ../../../april/AprilDream/gui/newactordlg.h

SOURCES += \
    ../../../april/AprilDream/gui/mw.cc \
    ../../../april/AprilDream/aprildream-main.cc \
    ../../../april/AprilDream/propertybrowser/qtvariantproperty.cpp \
    ../../../april/AprilDream/propertybrowser/qttreepropertybrowser.cpp \
    ../../../april/AprilDream/propertybrowser/qtpropertymanager.cpp \
    ../../../april/AprilDream/propertybrowser/qtpropertybrowserutils.cpp \
    ../../../april/AprilDream/propertybrowser/qtpropertybrowser.cpp \
    ../../../april/AprilDream/propertybrowser/qtgroupboxpropertybrowser.cpp \
    ../../../april/AprilDream/propertybrowser/qteditorfactory.cpp \
    ../../../april/AprilDream/propertybrowser/qtbuttonpropertybrowser.cpp \
    ../../../april/AprilDream/gui/dock.cc \
    ../../../april/AprilDream/gui/dockworld.cc \
    ../../../april/AprilDream/gui/docktree.cc \
    ../../../april/AprilDream/gui/dockids.cc \
    ../../../april/AprilDream/gui/dockcrtsel.cc \
    ../../../april/AprilDream/gui/sceneviewer.cc \
    ../../../april/AprilDream/gui/newworlddlg.cc \
    ../../../april/AprilDream/gui/pluginsdlg.cc \
    ../../../april/AprilDream/gui/dnaeditordlg.cc \
    ../../../april/AprilDream/gui/newactordlg.cc

RESOURCES += \
    ../../../april/AprilDream/aprildream.qrc



