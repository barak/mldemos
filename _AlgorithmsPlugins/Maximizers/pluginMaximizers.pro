###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_Maximizers
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsMaximizers.ui \
    paramsGA.ui \
    paramsParticles.ui \
    paramsNLopt.ui \
    paramsParticleFilters.ui

HEADERS += \
    maximizeRandom.h \
    maximizePower.h \
    maximizeGA.h \
    maximizeParticles.h \
    maximizeSwarm.h \
    maximizeGradient.h \
    maximizeDonut.h \
    pluginMaximizers.h \
    interfaceParticles.h \
    interfaceParticleFilters.h \
    interfaceGA.h \
    gaPeon.h \
    gaTrainer.h \
    mvnpdf.h \
    interfaceBasic.h \
    maximizeNLopt.h \
    interfaceNLopt.h

SOURCES += \
    maximizeRandom.cpp \
    maximizePower.cpp \
    maximizeGA.cpp \
    maximizeParticles.cpp \
    maximizeSwarm.cpp \
    maximizeGradient.cpp \
    maximizeDonut.cpp \
    pluginMaximizers.cpp \
    interfaceGA.cpp \
    interfaceParticles.cpp \
    interfaceParticleFilters.cpp \
    gaPeon.cpp \
    gaTrainer.cpp \
    interfaceBasic.cpp \
    maximizeNLopt.cpp \
    interfaceNLopt.cpp

OTHER_FILES += \
    plugin.json
