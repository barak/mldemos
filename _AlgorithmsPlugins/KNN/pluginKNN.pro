###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_KNN
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsKNN.ui \
    paramsKNNDynamic.ui \
    paramsKNNRegress.ui

HEADERS += \
    classifierKNN.h \
    regressorKNN.h \
    dynamicalKNN.h \
    interfaceKNNClassifier.h \
    interfaceKNNRegress.h \
    interfaceKNNDynamic.h \
    pluginKNN.h

SOURCES += \
    classifierKNN.cpp \
    regressorKNN.cpp \
    dynamicalKNN.cpp \
    interfaceKNNClassifier.cpp \
    interfaceKNNRegress.cpp \
    interfaceKNNDynamic.cpp \
    pluginKNN.cpp

OTHER_FILES += \
    plugin.json
