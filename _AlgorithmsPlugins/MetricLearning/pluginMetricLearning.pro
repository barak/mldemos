###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin

NAME = mld_MetricLearning
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += paramsCVO.ui

HEADERS += \
    projectorCVO.h \
    interfaceCVOProjection.h \
    pluginMetricLearning.h \
    CVOLearner.h

SOURCES += \
    projectorCVO.cpp \
    interfaceCVOProjection.cpp \
    pluginMetricLearning.cpp \
    CVOLearner.cpp

OTHER_FILES += \
    plugin.json
