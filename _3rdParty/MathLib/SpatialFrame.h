/*
 * Copyright (C) 2010 Learning Algorithms and Systems Laboratory, EPFL, Switzerland
 * Author: Eric Sauser
 * email:   eric.sauser@a3.epf.ch
 * website: lasa.epfl.ch
 *
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#ifndef SPATIAL_FRAME_H
#define SPATIAL_FRAME_H

#include "Vector3.h"
#include "Matrix3.h"
#include "SpatialVector.h"
#include "SpatialVelocity.h"
#include "SpatialForce.h"
#include "SpatialInertia.h"

#include "ReferenceFrame.h"

#ifdef USE_MATHLIB_NAMESPACE
namespace MathLib {
#endif


/**
 * \class SpatialFrame
 *
 * \ingroup MathLib
 *
 * \brief An implementation of the template TMatrix class
 *
 * This template square matrix class can be used for doing various matrix manipulation.
 * This should be combined with the TVector class for doing almost anything
 * you ever dreamt of.
 */

class SpatialFrame
{
public:

  ReferenceFrame  mRefFrame;
  ReferenceFrame *mRefFramePtr;

public:
  /// Empty constructor
  inline SpatialFrame(){
    mRefFramePtr = &mRefFrame;
  };
  /// Copy constructor
  inline SpatialFrame(const SpatialFrame &spatialFrame){
    Set(spatialFrame);
  };
  inline SpatialFrame(ReferenceFrame &refFrame){
    Set(refFrame);
  };

  /// Destructor
  inline virtual ~SpatialFrame(){
    mRefFramePtr = NULL;
  }


  inline SpatialFrame& Set(const SpatialFrame& spatialFrame){
    mRefFrame.Set(*(spatialFrame.mRefFramePtr));
    mRefFramePtr = &mRefFrame;
    return *this;
  }

  inline SpatialFrame& Set(ReferenceFrame &refFrame){
    mRefFramePtr = &refFrame;
    return *this;
  };

  inline ReferenceFrame& GetReferenceFrame(){
    return *mRefFramePtr;
  }


  inline SpatialFrame& Identity(){
    mRefFramePtr->Identity();
    return *this;
  }


  /// Assignment operator
  inline SpatialFrame& operator = (const SpatialFrame &frame){
    return Set(frame);
  }

  /// Assignment data-wise operations
  inline SpatialFrame& operator *= (const SpatialFrame &frame){
    return SMult(frame);
  }

  inline SpatialFrame& SMult(const SpatialFrame &frame){
    SpatialFrame copy(*this);
    copy.Mult(frame,*this);
    return *this;
  }

  inline SpatialFrame operator * (const SpatialFrame &frame) const
  {
    SpatialFrame result;
    return Mult(frame,result);
  }

  inline SpatialFrame Mult(const SpatialFrame &frame) const
  {
    SpatialFrame result;
    return Mult(frame,result);
  }


  inline SpatialFrame& Mult(const SpatialFrame &frame, SpatialFrame &result) const
  {
    mRefFramePtr->Mult(*frame.mRefFramePtr,*result.mRefFramePtr);
    return result;
  }


  inline SpatialFrame Inverse() const
  {
    SpatialFrame result;
    return Inverse(result);
  }

  inline SpatialFrame& Inverse(SpatialFrame& result) const
  {
    result.Set(mRefFramePtr->GetInverse());
    return result;
  }




  inline SpatialVelocity operator * (const SpatialVelocity &vector) const
  {
    SpatialVelocity result;
    return Mult(vector,result);
  }

  inline SpatialVelocity Mult(const SpatialVelocity &vector) const {
    SpatialVelocity result;
    return Mult(vector,result);
  }
  inline SpatialVelocity& Mult(const SpatialVelocity &vector, SpatialVelocity &result) const {
    vector.mAngular.Cross(mRefFramePtr->GetOrigin(),result.mAngular); // -(p x w)
    result.mAngular+=(vector.mLinear);        // (v0 - (p x w))
    mRefFramePtr->GetOrient().Mult(result.mAngular,result.mLinear);

    mRefFramePtr->GetOrient().Mult(vector.mAngular,result.mAngular);
    return result;
  }


  inline SpatialVelocity InverseMult(const SpatialVelocity &vector) const {
    SpatialVelocity result;
    return InverseMult(vector,result);
  }
  inline SpatialVelocity& InverseMult(const SpatialVelocity &vector, SpatialVelocity &result) const {
    ReferenceFrame &inv = mRefFramePtr->GetInverse();
    vector.mAngular.Cross(inv.GetOrigin(),result.mAngular); // -(p x w)
    result.mAngular+=(vector.mLinear);        // (v0 - (p x w))
    inv.GetOrient().Mult(result.mAngular,result.mLinear);
    inv.GetOrient().Mult(vector.mAngular,result.mAngular);
    return result;
  }



  inline SpatialForce operator * (const SpatialForce &vector) const{
    SpatialForce result;
    return Mult(vector,result);
  }
  inline SpatialForce Mult(const SpatialForce &vector) const{
    SpatialForce result;
    return Mult(vector,result);
  }
  inline SpatialForce& Mult(const SpatialForce &vector, SpatialForce &result) const{
    vector.mLinear.Cross(mRefFramePtr->GetOrigin(),result.mLinear);   // -(p x f)
    result.mLinear+=(vector.mAngular);        // (v0 - (p x w))
    mRefFramePtr->GetOrient().Mult(result.mLinear,result.mAngular);

    mRefFramePtr->GetOrient().Mult(vector.mLinear,result.mLinear);
    return result;
  }

  inline SpatialForce InverseMult(const SpatialForce &vector) const{
    SpatialForce result;
    return InverseMult(vector,result);
  }
  inline SpatialForce& InverseMult(const SpatialForce &vector, SpatialForce &result) const{
    ReferenceFrame &inv = mRefFramePtr->GetInverse();
    vector.mLinear.Cross(inv.GetOrigin(),result.mLinear);   // -(p x f)
    result.mLinear+=(vector.mAngular);        // (v0 - (p x w))
    inv.GetOrient().Mult(result.mLinear,result.mAngular);
    inv.GetOrient().Mult(vector.mLinear,result.mLinear);
    return result;
  }



  inline SpatialInertia operator * (const SpatialInertia &inertia) const
  {
    SpatialInertia result;
    return Mult(inertia,result);
  }

  inline SpatialInertia Mult(const SpatialInertia &inertia) const
  {
    SpatialInertia result;
    return Mult(inertia,result);
  }

  inline SpatialInertia& Mult(const SpatialInertia &inertia, SpatialInertia &result) const
  {
    /*
    vector.mLinear.Cross(mRefFramePtr->GetOrigin(),result.mLinear);   // -(p x f)
    result.mLinear+=(vector.mAngular);        // (v0 - (p x w))
    mRefFramePtr->GetOrient().Mult(result.mLinear,result.mAngular);

    mRefFramePtr->GetOrient().Mult(vector.mLinear,result.mLinear);
    return result;
    */
    result.mMass = inertia.mMass;

    mRefFramePtr->GetOrient().TransposeMult(inertia.mLinearMoment,result.mLinearMoment);

    Matrix3 sPos; sPos.SkewSymmetric(mRefFramePtr->GetOrigin());
    Matrix3 sMom; sMom.SkewSymmetric(result.mLinearMoment);

    Vector3 tmp;
    tmp = mRefFramePtr->GetOrigin();
    tmp *= inertia.mMass;
    result.mLinearMoment+=(tmp);

    Matrix3 sMom2; sMom2.SkewSymmetric(result.mLinearMoment);

    Matrix3 tmpMat;
    mRefFramePtr->GetInverse().GetOrient().Mult(inertia.mInertiaMoment,tmpMat);
    tmpMat.Mult(mRefFramePtr->GetOrient(),result.mInertiaMoment);

    sPos.Mult(sMom,tmpMat);
    result.mInertiaMoment -= tmpMat;

    sMom2.Mult(sPos,tmpMat);
    result.mInertiaMoment -= tmpMat;

    return result;
  }

  inline TMatrix<6>& ToTMatrix6(TMatrix<6> & result){
    Matrix3 tmpM;  tmpM.Set(mRefFramePtr->GetOrient());
    Matrix3 tmpM2; tmpM2.SkewSymmetric(mRefFramePtr->GetOrigin()); tmpM2.STranspose();
    Matrix3 tmpM3; tmpM.Mult(tmpM2,tmpM3);
    for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
        result._[(i  )*6+j]   = tmpM.          _[i*3+j];
        result._[(i+3)*6+j]   = tmpM3.         _[i*3+j];
        result._[(i  )*6+j+3] = R_ZERO;
        result._[(i+3)*6+j+3] = tmpM.          _[i*3+j];
      }
    }
    return result;
  }








};


#ifdef USE_MATHLIB_NAMESPACE
}
#endif
#endif
