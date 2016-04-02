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
#ifndef _CLASSIFIER_MLP_H_
#define _CLASSIFIER_MLP_H_

#include <vector>
#include "classifier.h"
#include "basicOpenCV.h"

class ClassifierMLP : public Classifier
{
private:
	u32 functionType; // 1: sigmoid, 2: gaussian
	u32 neuronCount;
	u32 layerCount;
    u32 trainingType; // 0: Backprop, 1: RPROP
	float alpha, beta;
	CvANN_MLP *mlp;
public:
    ClassifierMLP() : functionType(1), neuronCount(2), mlp(0), alpha(0), beta(0), trainingType(1){}
	~ClassifierMLP();
	void Train(std::vector< fvec > samples, ivec labels);
    float Test( const fvec &sample) const ;
    const char *GetInfoString() const ;
    void SetParams(u32 functionType, u32 neuronCount, u32 layerCount, f32 alpha, f32 beta, u32 trainingType);
};

#endif // _CLASSIFIER_MLP_H_
