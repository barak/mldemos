###########################
#Configuration            #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_DBSCAN
MLPATH =../..

include($$MLPATH/MLDemos_variables.pri)

DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED

###########################
# Source Files            #
###########################
FORMS += paramsDBSCAN.ui \
    graphDBSCAN.ui

HEADERS += \
    interfaceDBSCAN.h \
    distance.h \
    clustererDBSCAN.h \
    pluginDBSCAN.h

SOURCES += 	\
    interfaceDBSCAN.cpp \
    clustererDBSCAN.cpp \
    pluginDBSCAN.cpp

OTHER_FILES += \
    plugin.json
