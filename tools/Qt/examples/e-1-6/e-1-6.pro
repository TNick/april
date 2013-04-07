exists(../../local_defs.pri) include(../../local_defs.pri)
INCLUDEPATH += ../../../..
SOURCES += ../../../../april/examples/e-1-6/e-1-6.cc
OTHER_FILES += ../../../../april/docs/examples/e-1-6.dox
LIBS += -L../../build
CONFIG(debug, debug|release) {
	LIBS += -lapril_debug -lbbb_debug
} else {
    LIBS += -lapril -lbbb
}

