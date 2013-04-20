
#
#	Define BB_MEMTRACK to track memory usage. If this constant is not defined
#	the components are completly removed from output.
#
DEFINES += BB_MEMTRACK=1

# including blocks library
LIBS += -L/media/data/my-dev/libbbb-code/build
INCLUDEPATH += /media/data/my-dev/libbbb-code

# including memy library
LIBS += -L/media/data/my-dev/libmemy/build
INCLUDEPATH += /media/data/my-dev/libmemy

# including qtcp library
LIBS += -L/media/data/my-dev/libqtcp-code/build
INCLUDEPATH += /media/data/my-dev/libqtcp-code

# google test
LIBS += -L/media/data/trunks/google-test/googletest-trunk-build
INCLUDEPATH += /media/data/trunks/google-test/googletest-trunk/include

# eigen
INCLUDEPATH += /usr/local/include/eigen3

# flens
#LIBS += -L
INCLUDEPATH += /media/data/trunks/FLENS/FLENS-2012-10-01


QMAKE_CFLAGS += -std=c++11 # for TCC
QMAKE_CXXFLAGS += -std=c++11

