/*********************************************************************
FLAME Implementation in MLDemos
Copyright (C) Pierre-Antoine Sondag (pasondag@gmail.com) 2012

Based on the standard implementation of FLAME data clustering algorithm.
Copyright (C) 2007, Fu Limin (phoolimin@gmail.com).
All rights reserved.

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
#ifndef PLUGINFLAME_H
#define PLUGINFLAME_H

using namespace std;

#include <vector>
#include <interfaces.h>

class PluginFlame : public QObject, public CollectionInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PluginFlame" FILE "plugin.json")
    Q_INTERFACES(CollectionInterface)
public:
    PluginFlame();
    QString GetName(){return "My Flame Algorithm";}
};
#endif // PLUGINFLAME_H
