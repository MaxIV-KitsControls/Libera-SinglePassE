TEMPLATE = app
TARGET = LiberaSinglePassE
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++0x
QMAKE_CXXFLAGS += -std=c++0x
INCLUDEPATH += /usr/local/include/tango /usr/include/omniORB4 /usr/include/libera-2.8
LIBS += -L/opt/libera/lib -L/usr/local/lib -ltango -llog4tango -lomniORB4 -lomnithread -lomniDynamic4 -lliberamci2.8 -lliberaistd2.8 -lpthread
release:LIBS += -Wl,-rpath,.
QMAKE_CXXFLAGS += -Wextra -Wall

HEADERS += LiberaSinglePassEDataTask.h \
    LiberaSinglePassEClass.h \
    LiberaSinglePassE.h \
    LiberaCommon.h \
    documentation.h
SOURCES += main.cpp \
    LiberaSinglePassEStateMachine.cpp \
    LiberaSinglePassEDataTask.cpp \
    LiberaSinglePassEClass.cpp \
    LiberaSinglePassE.cpp \
    ClassFactory.cpp

OTHER_FILES += \
    debian_control/prerm \
    debian_control/preinst \
    debian_control/postinst \
    debian_control/control \
    Doxyfile \
    build.xml \
    LiberaSinglePass.sh \
    configure.sh \
    LiberaSinglePassE.xmi
