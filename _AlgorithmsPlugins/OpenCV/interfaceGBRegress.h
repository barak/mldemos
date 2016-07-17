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
#ifndef _INTERFACEGBREGRESS_H_
#define _INTERFACEGBREGRESS_H_

#include <vector>
#include <interfaces.h>
#include "regressorGB.h"
#include "ui_paramsGBRegress.h"

class RegrGB : public QObject, public RegressorInterface
{
	Q_OBJECT
	Q_INTERFACES(RegressorInterface)
private:
	QWidget *widget;
    Ui::ParametersGBRegress *params;
public:
    RegrGB();
    ~RegrGB();
	// virtual functions to manage the algorithm creation
	Regressor *GetRegressor();
    void DrawInfo(Canvas *canvas, QPainter &painter, Regressor *regressor){}
	void DrawModel(Canvas *canvas, QPainter &painter, Regressor *regressor);
    void DrawGL(Canvas *canvas, GLWidget *glw, Regressor *regressor){}
    void DrawConfidence(Canvas *canvas, Regressor *regressor);

	// virtual functions to manage the GUI and I/O
    QString GetName(){return QString("Gradient Boosting");}
	QString GetAlgoString();
    QString GetInfoFile(){return "GB.html";}
    QWidget *GetParameterWidget(){return widget;}
	void SetParams(Regressor *regressor);
	void SaveOptions(QSettings &settings);
	bool LoadOptions(QSettings &settings);
	void SaveParams(QTextStream &stream);
	bool LoadParams(QString name, float value);
    void SetParams(Regressor *regressor, fvec parameters);
    fvec GetParams();
    void GetParameterList(std::vector<QString> &parameterNames,
                                 std::vector<QString> &parameterTypes,
                                 std::vector< std::vector<QString> > &parameterValues);
};

#endif // _INTERFACEGBREGRESS_H_
