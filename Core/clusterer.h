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
#ifndef _CLUSTERING_H_
#define _CLUSTERING_H_

#include <vector>
#include <iostream>
#include "mymaths.h"

class Clusterer
{
protected:
	u32 dim;
    u32 nbClusters;
	bool bIterative;

public:
    Clusterer() : dim(2), bIterative(false), nbClusters(1) {}
    virtual ~Clusterer(){}
    void Cluster(std::vector< fvec > allsamples) {Train(allsamples);}
    void SetIterative(bool iterative){bIterative = iterative;}
    int NbClusters(){return nbClusters;}
    virtual Clusterer* clone() const{ return new Clusterer(*this);}

    virtual void Train(std::vector< fvec > samples){}
    virtual fvec Test( const fvec &sample){ return fvec(); }
    virtual fvec Test(const fVec &sample){ return Test((fvec)sample); }
    virtual const char *GetInfoString(){ return NULL; }
    virtual void SetNbClusters(int count){ nbClusters = count; }
    virtual float GetLogLikelihood(std::vector<fvec> samples){
        float loglik = 0;
        if(!samples.size()) return 0;
        fvec means(dim);
        // compute the global mean of the data
        FOR ( i, samples.size() ) {
            FOR ( d, dim ) means[d] += samples[i][d];
        }
     //   std::cout<< " GetLogLikelihood " << std::endl;
     //   std::cout<< " samples.size(): " << samples.size() << std::endl;
     //   std::cout<< " means: ";
      //  FOR(i, means.size()){
      //      std::cout<<  means[i] << " ";
      //  }
      //  std::cout<<std::endl;

        fvec scores(nbClusters);
        fvec diff(dim);
        // for every sample a score is computed
        FOR ( i, samples.size() ) {
             scores = Test(samples[i]);
            float rss = 0;
            FOR ( k, nbClusters ) {
                diff = samples[i]-means;//[k]; // center the data
                rss += diff*diff*scores[k];
                if(std::isnan(rss)){
                    std::cout<< " rss is NaN" << std::endl;
                    std::cout<< " diff: (" << diff[0] << "," << diff[1] <<  ")"  << std::endl;
                    std::cout<< " diff*diff: " << diff * diff << std::endl;

                }
            }
            loglik += logf(rss);
        }
        return loglik;
    }
    virtual float GetParameterCount(){return nbClusters*dim;}
};

#endif // _CLUSTERING_H_
