###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_Reinforcement
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
#    paramsParticles.ui \
#    paramsNLopt.ui \
#    paramsParticleFilters.ui \
    paramsRandom.ui \
    paramsGA.ui \
    paramsPower.ui \
    paramsDP.ui

HEADERS += \
#    maximizePower.h \
#    maximizeParticles.h \
#    maximizeSwarm.h \
#    maximizeGradient.h \
#    maximizeDonut.h \
#    interfaceParticles.h \
#    interfaceParticleFilters.h \
    gaPeon.h \
    gaTrainer.h \
#    mvnpdf.h \
#    maximizeNLopt.h \
#    interfaceNLopt.h \
    reinforcementPower.h \
    reinforcementRandom.h \
    reinforcementGA.h \
    reinforcementDP.h \
    interfaceRandom.h \
    interfacePower.h \
    interfaceDP.h \
    interfaceGA.h \
    pluginReinforcements.h

SOURCES += \
#    maximizeParticles.cpp \
#    maximizeSwarm.cpp \
#    maximizeGradient.cpp \
#    maximizeDonut.cpp \
#    interfaceParticles.cpp \
#    interfaceParticleFilters.cpp \
    gaPeon.cpp \
    gaTrainer.cpp \
#    maximizeNLopt.cpp \
#    interfaceNLopt.cpp \
    reinforcementPower.cpp \
    reinforcementRandom.cpp \
    reinforcementGA.cpp \
    reinforcementDP.cpp \
    interfaceRandom.cpp \
    interfacePower.cpp \
    interfaceDP.cpp \
    interfaceGA.cpp \
    pluginReinforcements.cpp

OTHER_FILES += \
    plugin.json
