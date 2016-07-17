###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_CCA
MLPATH =../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsCCA.ui

HEADERS += \
        pluginCCA.h\
        interfaceCCAProjection.h\
        projectorCCA.h


SOURCES += 	\
    interfaceCCAProjection.cpp\
    projectorCCA.cpp \
    pluginCCA.cpp

OTHER_FILES += \
    plugin.json

