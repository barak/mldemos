###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_SEDS
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += paramsSEDS.ui
HEADERS += \
    SEDS.h \
    dynamicalSEDS.h \
    interfaceSEDSDynamic.h

SOURCES += \
    SEDS.cpp \
    dynamicalSEDS.cpp \
    interfaceSEDSDynamic.cpp

OTHER_FILES += \
    plugin.json
