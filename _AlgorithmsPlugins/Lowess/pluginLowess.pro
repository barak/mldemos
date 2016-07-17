###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_Lowess
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += paramsLowess.ui

HEADERS += \
    regressorLowess.h \
    interfaceLowess.h \
    pluginLowess.h \
    lowessHelpers.h

SOURCES += \
    regressorLowess.cpp \
    interfaceLowess.cpp \
    pluginLowess.cpp

OTHER_FILES += \
    plugin.json
