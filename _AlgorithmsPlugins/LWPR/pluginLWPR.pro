###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_LWPR
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsLWPRDynamic.ui \
    paramsLWPRRegress.ui

HEADERS += \
    regressorLWPR.h \
    dynamicalLWPR.h \
    interfaceLWPRRegress.h \
    interfaceLWPRDynamic.h \
    pluginLWPR.h

SOURCES += \
    regressorLWPR.cpp \
    dynamicalLWPR.cpp \
    interfaceLWPRRegress.cpp \
    interfaceLWPRDynamic.cpp \
    pluginLWPR.cpp

OTHER_FILES += \
    plugin.json

