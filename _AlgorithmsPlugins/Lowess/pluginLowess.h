/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2010  Basilio Noris
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License,
version 3 as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#ifndef _PLUGINLOWESS_H_
#define _PLUGINLOWESS_H_

/**
  This is a collection of plugins, if you want to have a classifier, regressor, clusterer etc.. all in one single plugin.
  They will appear as separate interfaces in mldemos, but they're nicely grouped into one single file/project
  */

#include <vector>
#include <interfaces.h>

class PluginLowess : public QObject, public CollectionInterface
{
	Q_OBJECT
    Q_PLUGIN_METADATA(IID "PluginLowess" FILE "plugin.json")
    Q_INTERFACES(CollectionInterface)
public:
    PluginLowess();
    QString GetName(){return "Lowess Algorithm";}
};

#endif // _PLUGINLOWESS_H_
