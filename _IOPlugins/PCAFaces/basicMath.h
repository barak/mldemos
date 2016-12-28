/*!
 * \file basicMath.h
 * \author Basilio Noris
 * \date 27-11-06
 */
#ifndef _BASICMATH_H_
#define _BASICMATH_H_

#include <vector>
#include "basicOpenCV.h"

#define PIf	3.1415926535897932384626433832795f
//#define cvVec2 CvPoint2D32f
#define Vec3 CvPoint3D32f
#define cvvec2(a,b) cvPoint2D32f(a,b)
#define vec3(a,b,c) cvPoint3D32f(a,b,c)
#define point2(a) cvPoint((int)a.x, (int)a.y)

class cvVec2: public CvPoint2D32f{
public:
	float x, y;
	// constructors
	cvVec2() : x(0), y(0) {}
	cvVec2(int a, int b): x((float)a), y((float)b) {}
	cvVec2(float a, float b): x(a), y(b) {}
	cvVec2(double a, double b): x((float)a), y((float)b) {}
	cvVec2(CvPoint a): x((float)a.x), y((float)a.y) {}
	cvVec2(CvPoint2D32f a): x(a.x), y(a.y) {}
	CvPoint2D32f to32f(){return cvPoint2D32f(x,y);}
	CvPoint to2d(){return cvPoint((int)x,(int)y);}

	//operators
	cvVec2 operator+(const cvVec2&v) const {
		return cvVec2(x + v.x, y + v.y);
	}

	cvVec2& operator+=(const cvVec2&v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	cvVec2 operator-(const cvVec2&v) const {
		return cvVec2(x - v.x, y - v.y);
	}

	cvVec2& operator-=(const cvVec2&v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	cvVec2 operator*(const float &d) const {
		return cvVec2(x * d, y * d);
	}

	cvVec2& operator*=(const float &d) {
		x *= d;
		y *= d;
		return *this;
	}

	cvVec2 operator/(const float &d) const {
		return cvVec2(x / d, y / d);
	}

	cvVec2& operator/=(const float &d) {
		assert(d!=0);
		float inv = 1.f / d;
		x *= inv;
		y *= inv;
		return *this;
	}

	bool operator==(const cvVec2&v) const {
		return x == v.x && y == v.y;
	}

	bool operator!=(const cvVec2&v) const {
		return x != v.x || y != v.y;
	}

	cvVec2 operator-() const {
		return cvVec2(-x, -y);
	}

	// other functions
	cvVec2 normalize() { 
		if(length() <= 0) return cvVec2(1,0);
		float l = length();
		x /= l;
		y /= l;
		return *this;
	}

	float lengthSquared() {
		return x * x + y * y;
	}

	float length() {
		return sqrt(lengthSquared());
	}

	float dot(const cvVec2&v) const {
		return x * v.x + y * v.y;
	}
};

static float Distance(CvPoint2D32f a, CvPoint2D32f b)
{
	return (float)sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
}

static float Distance(Vec3 a, Vec3 b)
{
	return (float)sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y) + (b.z - a.z)*(b.z - a.z));
}

static u32 *FindMatches(CvPoint2D32f *src, u32 srccnt, CvPoint2D32f *dst, u32 dstcnt){
	f32 *distances = new f32[dstcnt*srccnt];
	FOR(i, dstcnt){
		f32 distotal = 0;
		FOR(j, srccnt){
			distances[i*srccnt + j] = Distance(src[j],dst[i]);
			distotal += distances[i*srccnt + j];
		}
		FOR(j,srccnt){
			distances[i*srccnt + j] /= distotal;
		}
	}
	u32 *indices = new u32[dstcnt];
	FOR(j,dstcnt){
		u32 minind = 0;
		FOR(i,dstcnt*srccnt){
			if(distances[i] < distances[minind]) minind = i;
		}
		indices[minind/srccnt] = minind%srccnt;
		FOR(i,srccnt){
			distances[(minind/srccnt)*srccnt + i] = 1.0f;
		}
		FOR(i,dstcnt){
			distances[i*srccnt + minind%srccnt] = 1.0f;
		}
	}
	delete [] distances;
	return indices;
}

static float Angle(Vec3 a, Vec3 b)
{
	// acos( a.b / |a|.|b|)
	float phi = (a.x*b.x+a.y*b.y+a.z+b.z) / sqrtf((a.x*a.x+a.y*a.y+a.z*a.z)*(b.x*b.x+b.y*b.y+b.z*b.z));
	return acos(phi);
}

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
	u32 *perm = new u32[length];
	memset(perm, 0, length*sizeof(u32));

	u32 *usable = new u32[length];
	FOR(i, length) usable[i] = i;

	if(seed == -1) srand((u32)cvGetTickCount());
	else srand((u32)seed);

	u32 uLength = length;
	for (register u32 i=0; i<length; i++)
	{
		register u32 r = ((rand()<< 7) + rand()) % uLength;

		perm[i] = usable[r];
		uLength--;
		usable[r] = usable[uLength];
		usable[uLength] = 0;
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
		FOR(i, dim) dist += abs(a[i]-b[i]);
		break;
	case DIST_INFINITE:
		FOR(i, dim) dist = max(dist, (float)abs(a[i]-b[i]));
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
inline std::vector< std::vector<float> > SoftKMeans(const std::vector<float *> points, std::vector<float *> *means, unsigned int dim, float beta)
{
	unsigned int clusters = means->size();

	std::vector< std::vector<float> > weights;
	for (unsigned int i=0; i < points.size(); i++)
	{
		weights.push_back(std::vector<float>());
		for (unsigned int j=0; j < clusters; j++) weights[i].push_back(0);
	}

	std::vector<float> distances;
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
	std::vector<float> perCluster;

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

#endif // _BASICMATH_H_
