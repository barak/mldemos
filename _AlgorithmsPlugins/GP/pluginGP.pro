###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_GP
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsGPClassifier.ui \
    paramsGPR.ui \
    paramsGPRdynamic.ui \

HEADERS += \
    pluginGP.h \
    interfaceGPClassifier.h \
    classifierGP.h \
    SOGP_aux.h \
    SOGP.h \
    regressorGPR.h \
    interfaceGPRRegress.h \
    interfaceGPRDynamic.h \
    dynamicalGPR.h \
    SECovarianceFunction.h

SOURCES += \
    pluginGP.cpp \
    interfaceGPClassifier.cpp \
    classifierGP.cpp \
    SOGP_aux.cpp \
    SOGP.cpp \
    regressorGPR.cpp \
    interfaceGPRRegress.cpp \
    interfaceGPRDynamic.cpp \
    dynamicalGPR.cpp \
    SECovarianceFunction.cpp

OTHER_FILES += \
    plugin.json
