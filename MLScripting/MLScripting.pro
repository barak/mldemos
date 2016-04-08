###########################
# Configuration           #
###########################
TEMPLATE = app

TARGET = mlscript
NAME = mlscript
MLPATH = ..
DESTDIR = $$MLPATH

CONFIG += mainApp
include($$MLPATH/MLDemos_variables.pri)

###########################
# Source Files            #
###########################
SOURCES += \
    main.cpp
