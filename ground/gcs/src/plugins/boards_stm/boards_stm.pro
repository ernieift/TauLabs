TEMPLATE = lib
TARGET = Stm
include(../../taulabsgcsplugin.pri)
include(../../plugins/uavobjects/uavobjects.pri)
include(../../plugins/coreplugin/coreplugin.pri)

OTHER_FILES += Stm.pluginspec

HEADERS += \
    stmplugin.h \
    flyingf3.h \
    flyingf4.h \
    flyingf7.h \
    discoveryf4.h

SOURCES += \
    stmplugin.cpp \
    flyingf3.cpp \
    flyingf4.cpp \
    flyingf7.cpp \
    discoveryf4.cpp

RESOURCES += \
    stm.qrc

