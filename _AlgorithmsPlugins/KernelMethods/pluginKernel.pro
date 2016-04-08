###########################
# Configuration           #
###########################
TEMPLATE = lib
CONFIG += plugin
NAME = mld_KernelMethods
MLPATH = ../..

include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
FORMS += \
    paramsSVM.ui \
    paramsSVMcluster.ui \
    paramsSVMregr.ui \
    paramsSVMdynamic.ui \
    paramsKM.ui \
    paramsMVM.ui \
    paramsRVM.ui \
    paramsRVMregr.ui \
    paramsMRVM.ui

HEADERS += \
    svm.h \
    classifierSVM.h \
    classifierMVM.h \
    classifierRVM.h \
    classifierPegasos.h \
    clustererKKM.h \
    clustererKM.h \
    kmeans.h \
    clustererSVR.h \
    regressorSVR.h \
    regressorRVM.h \
    regressorKRLS.h \
    dynamicalSVR.h \
    interfaceMVM.h \
    interfaceSVMClassifier.h \
    interfaceSVMCluster.h \
    interfaceSVMRegress.h \
    interfaceSVMDynamic.h \
    interfaceRVMClassifier.h \
    interfaceRVMRegress.h \
    interfaceKMCluster.h \
    dlibTypes.h \
    pluginKernel.h \
    interfaceMRVMClassifier.h \
    classifierMRVM.h

SOURCES += \
    svm.cpp \
    classifierSVM.cpp \
    classifierMVM.cpp \
    classifierRVM.cpp \
    classifierPegasos.cpp \
    clustererKKM.cpp \
    clustererKM.cpp \
    kmeans.cpp \
    clustererSVR.cpp \
    regressorSVR.cpp \
    regressorRVM.cpp \
    regressorKRLS.cpp \
    dynamicalSVR.cpp \
    interfaceMVM.cpp \
    interfaceSVMClassifier.cpp \
    interfaceSVMCluster.cpp \
    interfaceSVMRegress.cpp \
    interfaceSVMDynamic.cpp \
    interfaceRVMClassifier.cpp \
    interfaceRVMRegress.cpp \
    interfaceKMCluster.cpp \
    pluginKernel.cpp \
    interfaceMRVMClassifier.cpp \
    classifierMRVM.cpp

OTHER_FILES += \
    plugin.json
