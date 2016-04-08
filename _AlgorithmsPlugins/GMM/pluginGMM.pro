###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_GMM
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsGMM.ui \
    paramsGMMcluster.ui \
    paramsGMMregr.ui \
    paramsGMMdynamic.ui \
    marginalWidget.ui

HEADERS += \
    classifierGMM.h \
    clustererGMM.h \
    regressorGMR.h \
    dynamicalGMR.h \
    interfaceGMMClassifier.h \
    interfaceGMMCluster.h \
    interfaceGMMRegress.h \
    interfaceGMMDynamic.h \
    pluginGMM.h \
    marginalwidget.h

SOURCES += \
    classifierGMM.cpp \
    clustererGMM.cpp \
    regressorGMR.cpp \
    dynamicalGMR.cpp \
    interfaceGMMClassifier.cpp \
    interfaceGMMCluster.cpp \
    interfaceGMMRegress.cpp \
    interfaceGMMDynamic.cpp \
    pluginGMM.cpp \
    marginalwidget.cpp

OTHER_FILES += \
    plugin.json
