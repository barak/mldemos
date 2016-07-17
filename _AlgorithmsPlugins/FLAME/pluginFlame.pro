###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_Flame
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsFlame.ui

HEADERS +=  \
    clustererFlame.h \
    flame.h \
    interfaceFlameCluster.h \
    pluginFlame.h

SOURCES += \
    clustererFlame.cpp \
    interfaceFlameCluster.cpp \
    pluginFlame.cpp \
    flame.cpp

OTHER_FILES += \
    plugin.json
