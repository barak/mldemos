/*********************************************************************
MLDemos: A User-Friendly visualization toolkit for machine learning
Copyright (C) 2010  Basilio Noris
Contact: mldemos@b4silio.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*********************************************************************/
#include <public.h>
#include "classifierRVM.h"

using namespace std;
using namespace dlib;

ClassifierRVM::~ClassifierRVM()
{
    if(decFunction)
    {
#define KILLCASE(a) case a:{KillDim<a>();return;}
        switch(dim)
        {
        KILLCASE(2);
        KILLCASE(3);
        KILLCASE(4);
        KILLCASE(5);
        KILLCASE(6);
        KILLCASE(7);
        KILLCASE(8);
        KILLCASE(9);
        KILLCASE(10);
        KILLCASE(11);
        KILLCASE(12);
        default:
            KillDim<0>();
            return;
        }
    }
}

const char *ClassifierRVM::GetInfoString() const
{
	char *text = new char[1024];
	sprintf(text, "Relevance Vector Machine\n");
	sprintf(text, "%sKernel: ", text);
	switch(kernelType)
	{
	case 0:
		sprintf(text, "%s linear", text);
		break;
	case 1:
		sprintf(text, "%s polynomial (deg: %d width: %f)", text, kernelDegree, kernelParam);
		break;
	case 2:
		sprintf(text, "%s rbf (gamma: %f)", text, kernelParam);
		break;
	}
	sprintf(text, "%seps: %f\n", text, epsilon);
	sprintf(text, "%sRelevant Vectors: %lu\n", text, (unsigned long)GetSVs().size());
	return text;
}

void ClassifierRVM::Train(std::vector< fvec > samples, ivec labels)
{
    if(!samples.size()) return;
    dim = samples[0].size();

    classMap.clear();
    int cnt=0;
    FOR(i, labels.size()) if(!classMap.count(labels[i])) classMap[labels[i]] = cnt++;
    for(map<int,int>::iterator it=classMap.begin(); it != classMap.end(); it++) inverseMap[it->second] = it->first;

#define TRAINCASE(a) case a:{TrainDim<a>(samples, labels);return;}
    switch(dim)
    {
    TRAINCASE(2);
    TRAINCASE(3);
    TRAINCASE(4);
    TRAINCASE(5);
    TRAINCASE(6);
    TRAINCASE(7);
    TRAINCASE(8);
    TRAINCASE(9);
    TRAINCASE(10);
    TRAINCASE(11);
    TRAINCASE(12);
    default:
        TrainDim<0>(samples, labels);
        return;
    }
}

float ClassifierRVM::Test( const fvec &_sample ) const
{
#define TESTCASE(a) case a:{return TestDim<a>(_sample);}
    switch(dim)
    {
    TESTCASE(2);
    TESTCASE(3);
    TESTCASE(4);
    TESTCASE(5);
    TESTCASE(6);
    TESTCASE(7);
    TESTCASE(8);
    TESTCASE(9);
    TESTCASE(10);
    TESTCASE(11);
    TESTCASE(12);
    default:
        return TestDim<0>(_sample);
    }
}

std::vector<fvec> ClassifierRVM::GetSVs() const
{
#define SVCASE(a) case a:{return GetSVsDim<a>();}
    switch(dim)
    {
    SVCASE(2);
    SVCASE(3);
    SVCASE(4);
    SVCASE(5);
    SVCASE(6);
    SVCASE(7);
    SVCASE(8);
    SVCASE(9);
    SVCASE(10);
    SVCASE(11);
    SVCASE(12);
    default:
        return GetSVsDim<0>();
    }
}

template <int N>
void ClassifierRVM::KillDim()
{
    if(!decFunction) return;
    switch(kernelTypeTrained)
    {
    case 0:
        if(decFunction) delete [] (linfunc*)decFunction;
        break;
    case 1:
        if(decFunction) delete [] (polfunc*)decFunction;
        break;
    case 2:
        if(decFunction) delete [] (rbffunc*)decFunction;
        break;
    }
    decFunction = 0;
}

template <int N>
void ClassifierRVM::TrainDim(std::vector< fvec > _samples, ivec _labels)
{
    std::vector<sampletype> samples;
    std::vector<double> labels;
    sampletype samp(dim);
    FOR(i, _samples.size()) { FOR(d, dim) samp(d) = _samples[i][d]; samples.push_back(samp); }
    KillDim<N>();

    FOR(i, _samples.size()) labels.push_back(_labels[i] == 1 ? 1 : -1);

    randomize_samples(samples, labels);

    switch(kernelType)
    {
    case 0:
    {
        rvm_trainer<linkernel> train = rvm_trainer<linkernel>();
        train.set_epsilon(epsilon);
        train.set_kernel(linkernel());
        linfunc *fun = new linfunc[1];
        *fun = train.train(samples, labels);
        decFunction = (void *)fun;
        kernelTypeTrained = 0;
    }
        break;
    case 1:
    {
        rvm_trainer<polkernel> train = rvm_trainer<polkernel>();
        train.set_epsilon(epsilon);
        train.set_kernel(polkernel(1./kernelParam, 0, kernelDegree));
        polfunc *fun = new polfunc[1];
        *fun = train.train(samples, labels);
        decFunction = (void *)fun;
        kernelTypeTrained = 1;
    }
        break;
    case 2:
    {
        rvm_trainer<rbfkernel> train = rvm_trainer<rbfkernel>();
        train.set_epsilon(epsilon);
        train.set_kernel(rbfkernel(1./kernelParam));
        rbffunc *fun = new rbffunc[1];
        *fun = train.train(samples, labels);
        decFunction = (void *)fun;
        kernelTypeTrained = 2;
    }
        break;
    }
}

template <int N>
float ClassifierRVM::TestDim(const fvec &_sample) const
{
    float estimate = 0.f;

    sampletype sample(dim);
    FOR(d,dim) sample(d) = _sample[d];
    if(!decFunction) return estimate;
    switch(kernelTypeTrained)
    {
    case 0:
    {
        linfunc fun = *(linfunc*)decFunction;
        estimate = fun(sample);
    }
        break;
    case 1:
    {
        polfunc fun = *(polfunc*)decFunction;
        estimate = fun(sample);
    }
        break;
    case 2:
    {
        rbffunc fun = *(rbffunc*)decFunction;
        estimate = fun(sample);
    }
        break;
    }
    return estimate;
}

template <int N>
std::vector<fvec> ClassifierRVM::GetSVsDim() const
{
    std::vector<fvec> SVs;
    switch(kernelTypeTrained)
    {
    case 0:
    {

        FOR(i, (*(linfunc*)decFunction).basis_vectors.nr())
        {
            fvec sv(dim);
            FOR(d, dim) sv[d] = (*(linfunc*)decFunction).basis_vectors(i)(d);
            SVs.push_back(sv);
        }
    }
        break;
    case 1:
    {

        FOR(i, (*(polfunc*)decFunction).basis_vectors.nr())
        {
            fvec sv(dim);
            FOR(d, dim) sv[d] = (*(polfunc*)decFunction).basis_vectors(i)(d);
            SVs.push_back(sv);
        }
    }
        break;
    case 2:
    {

        FOR(i, (*(rbffunc*)decFunction).basis_vectors.nr())
        {
            fvec sv(dim);
            FOR(d, dim) sv[d] = (*(rbffunc*)decFunction).basis_vectors(i)(d);
            SVs.push_back(sv);
        }
    }
        break;
    }
	return SVs;
}
