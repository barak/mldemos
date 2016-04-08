##############################
#                            #
#       MLDemos Bundle       #
#                            #
##############################
greaterThan(QT_MAJOR_VERSION, 4) {
	cache();
}

TEMPLATE = subdirs
# the main software
CONFIG += ordered
SUBDIRS = Core 3rdParty MLDemos UnitTesting
Core.file = Core/Core.pro
3rdParty.file = _3rdParty/3rdParty.pro
MLDemos.file = MLDemos/MLDemos.pro
MLDemos.depends = Core
MLScripting.file = MLScripting/MLScripting.pro
MLScripting.depends = Core
UnitTesting.file = UnitTesting/UnitTesting.pro
UnitTesting.depends = Core MLDemos

# algorithm plugins
ALGOPATH = _AlgorithmsPlugins
SUBDIRS += Obstacle GMM Kernel GP KNN LWPR Maximizers Reinforcements SEDS FLAME DBSCAN Lowess CCA ASVM GHSOM RandomKernel MetricLearning
SUBDIRS += OpenCV MLR QTMeans Projections
SUBDIRS += Example

GMM.file = $$ALGOPATH/GMM/pluginGMM.pro
ASVM.file = $$ALGOPATH/ASVM/pluginASVM.pro
Kernel.file = $$ALGOPATH/KernelMethods/pluginKernel.pro
GP.file = $$ALGOPATH/GP/pluginGP.pro
KNN.file = $$ALGOPATH/KNN/pluginKNN.pro
Projections.file = $$ALGOPATH/Projections/pluginProjections.pro
LWPR.file = $$ALGOPATH/LWPR/pluginLWPR.pro
Obstacle.file = $$ALGOPATH/Obstacle/pluginAvoidance.pro
SEDS.file = $$ALGOPATH/SEDS/pluginSEDS.pro
Maximizers.file = $$ALGOPATH/Maximizers/pluginMaximizers.pro
Reinforcements.file = $$ALGOPATH/Reinforcements/pluginReinforcements.pro
Lowess.file = $$ALGOPATH/Lowess/pluginLowess.pro
FLAME.file = $$ALGOPATH/FLAME/pluginFlame.pro
DBSCAN.file = $$ALGOPATH/DBSCAN/pluginDBSCAN.pro
HMM.file = $$ALGOPATH/HMM/pluginHMM.pro
CCA.file = $$ALGOPATH/CCA/pluginCCA.pro
GHSOM.file = $$ALGOPATH/GHSOM/pluginGHSOM.pro
RandomKernel.file = $$ALGOPATH/RandomKernel/pluginRandomKernel.pro
MetricLearning.file = $$ALGOPATH/MetricLearning/pluginMetricLearning.pro
# experimental or buggy
OpenCV.file = $$ALGOPATH/OpenCV/pluginOpenCV.pro
MLR.file = $$ALGOPATH/MLR/pluginMLR.pro
QTMeans.file = $$ALGOPATH/QTMeans/pluginQTMeans.pro
# example template
Example.file = $$ALGOPATH/Example/pluginExample.pro

# input plugins
INPUTPATH = _IOPlugins
SUBDIRS += PCAFaces
#SUBDIRS += ImportTimeseries
PCAFaces.file = $$INPUTPATH/PCAFaces/pluginPCAFaces.pro
RandomEmitter.file = $$INPUTPATH/RandomEmitter/pluginRandomEmitter.pro
WebImport.file = $$INPUTPATH/WebImport/pluginWebImport.pro
CSVImport.file = $$INPUTPATH/CSVImport/pluginCSVImport.pro
ImportTimeseries.file = $$INPUTPATH/ImportTimeseries/pluginImportTimeseries.pro

