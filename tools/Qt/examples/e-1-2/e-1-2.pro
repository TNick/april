exists(../../local_defs.pri) include(../../local_defs.pri)
INCLUDEPATH += ../../../..
SOURCES += \
    ../../../../april/examples/e-1-2/e-1-2.cc

OTHER_FILES += \
    ../../../../april/docs/examples/e-1-2.dox

LIBS += -L$$PWD/../../../../build

CONFIG(debug, debug|release) {
	LIBS += -lapril_debug -lbbb_debug
} else {
    LIBS += -lapril -lbbb
}
