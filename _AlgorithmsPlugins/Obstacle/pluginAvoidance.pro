###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_DSAvoid
MLPATH = ../..

include("$$MLPATH/MLDemos_variables.pri")

###########################
# Source Files            #
###########################
HEADERS += \
    DSAvoid.h \
    interfaceAvoidance.h

SOURCES += \
    DSAvoid.cpp \
    interfaceAvoidance.cpp

OTHER_FILES += \
    plugin.json
