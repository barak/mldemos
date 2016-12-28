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
#ifndef _BASICMATH_H_
#define _BASICMATH_H_

#include "public.h"
#include <vector>
#include <float.h>
#include <math.h>

#ifndef PIf
#define PIf	3.1415926535897932384626433832795f
#endif

/*!
 * Cubic interpolation class adapted from an algorithm by Marino 'Mutilate' Alge
 * works with cvVec2 and Vec3 types
 */
template <class T>
class CCubic
{
private:
    T a, b, c, d;

public:
    /*!
  Constructor, takes 4 points as input for the interpolation
  \param x0-x3 the input points for interpolation
 */
    CCubic(T x0, T x1, T x2, T x3)
    {
        //		a = x1;
        //		b = (x2 - x0)*0.5f;
        //		c = x0 - x1*2.5f + x2*2.0f - x3*0.5f;
        //		d = (x3 - x0)*0.5f - (x2 - x1)*1.5f;
        a = x1;
        b = MulS(Sub(x2,x0),0.5f);
        c = Add(Sub(x0,MulS(x1,2.5f)),Sub(MulS(x2,2.0f),MulS(x3,0.5f)));
        d = Sub(MulS(Sub(x3,x0),0.5f),MulS(Sub(x2,x1),1.5f));
    }

    /*!
  The interpolation prediction function
  \param t the input time
  \return returns the value expected at time t
 */
    T X(float t) const
    {
        //return a + (b + (c + d*t)*t)*t;
        return Add(a,MulS(Add(b,MulS(Add(c,MulS(d,t)),t)),t));
    }

    /*!
  All in one interpolation function
  \param x0-x3 the input points for interpolation
  \param t the input time
  \return returns the value expected at time t, using points x0-x3 for interpolation
 */
    static T X(T x0, T x1, T x2, T x3, float t)
    {
        //return x1 + ((x2 - x0)*0.5f + (x0 - x1*2.5f + x2*2.0f - x3*0.5f + (x3 - x0)*0.5f - (x2 - x1)*1.5f*t)*t)*t;
        T asd7 = Sub(x0, MulS(x1,2.5f));
        T asd6 = Sub(MulS(x2,2.0f), MulS(x3,0.5f));
        T asd5 = Sub(MulS(Sub(x3,x0),0.5f), MulS(Sub(x2,x1),1.5f*t));
        T asd4 = Add(asd5,Add(asd6,asd7));
        T asd3 = MulS(asd4,t);
        T asd2 = Add(MulS(Sub(x2,x0),0.5f), asd3);
        T asd  = MulS(asd2,t);
        return Add(x1, asd);
    }
};

/*!
 Random Permutations array
 \param length the length of the output array
 \param seed random seed (optional) clock used otherwise
 \return returns an array of indices between 0 and 'length' randomly sorted
*/
static u32 *randPerm(u32 length, s32 seed=-1)
{
    u32 i=0;
    u32 *perm = new u32[length];
    u32 *usable = new u32[length];
    int uLength = length;
    if(seed != -1) srand(seed);

    for(int i=0; i<length; i++)
    {
        perm[i] = 0;
        usable[i] = i;
    }

    for (int i=0; i<length; i++)
    {
        int r = 0;
        if(RAND_MAX <= 0x7fff)
            r = ((rand()<< 7) + rand()) % uLength;
        else
            r = rand() % uLength;

        perm[i] = usable[r];
        uLength--;
        usable[r] = usable[uLength];
        usable[uLength] = 0;
        if(!uLength) break;
    }
    delete [] usable;

    return perm;
}

enum distEnum {DIST_EUCLIDEAN, DIST_MANHATTAN, DIST_INFINITE} ;

inline float Distance(float *a, float *b, u32 dim, distEnum metric)
{
    float dist = 0;
    switch(metric)
    {
    case DIST_EUCLIDEAN:
        FOR(i, dim) dist += powf(a[i]-b[i],2);
        dist = sqrtf(dist);
        break;
    case DIST_MANHATTAN:
        FOR(i, dim) dist += (float)abs((double)a[i]-(double)b[i]);
        break;
    case DIST_INFINITE:
        FOR(i, dim) dist = max(dist, (float)abs((double)a[i]-(double)b[i]));
        break;
    }
    return dist;
}

/**
  * Performs soft-kmeans clustering. The number of clusters is inferred from the dimension of means
  * it is advisable to normalize the data in order to avoid numerical problems due to the negative exp function
  *	\param points the input points
  * \param means, the starting cluster positions
  * \param dim, the dimension of the point data
  * \param beta, the stiffness of the soft-kmeans boundary
  * \return returns the weights for each points for each cluster
  *

*/
inline std::vector<fvec> SoftKMeans(const std::vector<float *> points, std::vector<float *> *means, unsigned int dim, float beta)
{
    unsigned int clusters = means->size();

    std::vector<fvec> weights;
    for (unsigned int i=0; i < points.size(); i++)
    {
        weights.push_back(fvec());
        for (unsigned int j=0; j < clusters; j++) weights[i].push_back(0);
    }

    fvec distances;
    for (unsigned int i=0; i < clusters; i++) distances.push_back(0);


    // Expectation Step
    for (unsigned int i=0; i < points.size(); i++)
    {
        float distanceSum = 0;
        for (unsigned int j=0; j < clusters; j++)
        {
            distances[j] = expf(-beta*Distance(points[i], (*means)[j], dim, DIST_EUCLIDEAN));
            distanceSum += distances[j];
        }

        for (unsigned int j=0; j < clusters; j++)
        {
            weights[i][j] = distances[j] / distanceSum;
        }
    }

    // Maximization Step
    fvec perCluster;

    for (unsigned int i=0; i < clusters; i++)
    {
        for (unsigned int j=0; j < dim; j++) (*means)[i][j] = 0;
        perCluster.push_back(0);
    }

    for (unsigned int i=0; i < points.size(); i++)
    {
        for (unsigned int j=0; j < clusters; j++)
        {
            for (unsigned int k=0; k < dim; k++)
            {
                (*means)[j][k] += points[i][k] * weights[i][j];
            }
            perCluster[j] += weights[i][j];
        }
    }

    for (unsigned int i=0; i < clusters; i++)
    {
        if(perCluster[i] != 0)
        {
            for (unsigned int j=0; j < dim; j++)
            {
                (*means)[i][j] /= perCluster[i];
            }
        }
    }

    return weights;
}

static std::vector<float> Quartiles(std::vector<float> srcdata)
{
    std::vector<float> quartiles;
    if(!srcdata.size())
    {
        quartiles.resize(5,0);
        return quartiles;
    }
    // we take out all non-zero elements
    std::vector<float> data;
    FOR(i, srcdata.size()) if(srcdata[i] != 0) data.push_back(srcdata[i]);
    if(!data.size())
    {
        quartiles.resize(5,0);
        return quartiles;
    }
    if(data.size()==1)
    {
        quartiles.resize(5,data[0]);
        return quartiles;
    }
    float mean = 0;
    float sigma = 0;
    FOR(i, data.size()) mean += data[i] / data.size();
    FOR(i, data.size()) sigma += powf(data[i]-mean,2);
    sigma = sqrtf(sigma/data.size());

    std::vector<float> outliers;
    std::vector<float> sorted;
    if(sigma==0)
    {
        sorted = data;
    }
    else
    {
        // we look for outliers using the 3*sigma rule
        FOR(i, data.size())
        {
            if (data[i] - mean < 3*sigma)
                sorted.push_back(data[i]);
            else outliers.push_back(data[i]);
        }
    }
    if(!sorted.size())
    {
        quartiles.resize(5,0);
        return quartiles;
    }
    sort(sorted.begin(), sorted.end());
    int count = sorted.size();
    int half = count/2;
    float bottom = sorted[0];
    float top = sorted[sorted.size()-1];

    float median = count%2 ? sorted[half] : (sorted[half] + sorted[half - 1])/2;
    float quartLow, quartHi;
    if(count < 4)
    {
        quartLow = bottom;
        quartHi = top;
    }
    else
    {
        quartLow = half%2 ? sorted[half/2] : (sorted[half/2] + sorted[half/2 - 1])/2;
        quartHi = half%2 ? sorted[half*3/2] : (sorted[half*3/2] + sorted[half*3/2 - 1])/2;
    }
    quartiles.push_back(bottom);
    quartiles.push_back(quartLow);
    quartiles.push_back(median);
    quartiles.push_back(quartHi);
    quartiles.push_back(top);
    return quartiles;
}

static std::vector<float> MeanStd(std::vector<float> srcdata)
{
    std::vector<float> results;
    results.resize(2,0);
    if(!srcdata.size())
    {
        return results;
    }
    if(srcdata.size() == 1)
    {
        results[0] = srcdata[0];
        results[1] = 0;
        return results;
    }
    float mean = 0;
    float stdev = 0;
    FOR(i, srcdata.size())
    {
        mean += srcdata[i];
    }
    mean /= srcdata.size();
    FOR(i, srcdata.size())
    {
        stdev += (srcdata[i]-mean)*(srcdata[i]-mean);
    }
    stdev = sqrtf(stdev);
    results[0] = mean;
    results[1] = stdev;
    return results;
}


#endif // _BASICMATH_H_
