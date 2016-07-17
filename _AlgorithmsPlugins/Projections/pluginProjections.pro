###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_Projections
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsProjections.ui \
    paramsICA.ui \
    paramsLDA.ui \
    paramsKPCA.ui \
    paramsSammon.ui \
    paramsPCA.ui \
    contourPlots.ui \
    paramsNormalize.ui \
    paramsLLE.ui

HEADERS += \
    basicOpenCV.h \
    eigen_pca.h \
    classifierLinear.h \
    classifierKPCA.h \
    interfaceProjections.h \
    pluginProjections.h \
    interfaceICAProjection.h \
    interfaceLDAProjection.h \
    interfacePCAProjection.h \
    interfaceKPCAProjection.h \
    interfaceSammonProjection.h \
    projectorPCA.h \
    projectorKPCA.h \
    projectorICA.h \
    projectorSammon.h \
    projectorLDA.h \
    projectorNormalize.h \
    interfaceNormalizeProjection.h \
    projectorLLE.h \
    interfaceLLEProjection.h

SOURCES += \
    basicOpenCV.cpp \
    eigen_pca_kernel.cpp \
    classifierLinear.cpp \
    classifierKPCA.cpp \
    interfaceProjections.cpp \
    pluginProjections.cpp \
    interfaceICAProjection.cpp \
    interfaceLDAProjection.cpp \
    interfacePCAProjection.cpp \
    interfaceKPCAProjection.cpp \
    interfaceSammonProjection.cpp \
    projectorPCA.cpp \
    projectorKPCA.cpp \
    projectorICA.cpp \
    projectorSammon.cpp \
    projectorLDA.cpp \
    projectorNormalize.cpp \
    interfaceNormalizeProjection.cpp \
    interfaceLLEProjection.cpp \
    projectorLLE.cpp

#INCLUDEPATH += /opt/local/include
#LIBS += -llapack -lblas
HEADERS +=  isomap/fibheap.h \
            isomap/isomap.h
SOURCES +=  isomap/dijkstra.cpp \
            isomap/isomap.cpp

OTHER_FILES += \
    plugin.json
