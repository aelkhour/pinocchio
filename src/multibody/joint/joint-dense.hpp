//
// Copyright (c) 2015 CNRS
//
// This file is part of Pinocchio
// Pinocchio is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// Pinocchio is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Lesser Public License for more details. You should have
// received a copy of the GNU Lesser General Public License along with
// Pinocchio If not, see
// <http://www.gnu.org/licenses/>.

#ifndef __se3_joint_dense_hpp__
#define __se3_joint_dense_hpp__

#include "pinocchio/multibody/joint/joint-base.hpp"

namespace se3
{

  template<int _NQ, int _NV>
  struct traits< JointDense<_NQ, _NV > >
  {
    typedef JointDataDense<_NQ, _NV> JointData;
    typedef JointModelDense<_NQ, _NV> JointModel;
    typedef ConstraintXd Constraint_t;
    typedef SE3 Transformation_t;
    typedef Motion Motion_t;
    typedef BiasZero Bias_t;
    typedef Eigen::Matrix<double,6,Eigen::Dynamic> F_t;
    enum {
      NQ = _NQ, // pb 
      NV = _NV
    };
  };

  template<int _NQ, int _NV> struct traits< JointDataDense<_NQ, _NV > > { typedef JointDense<_NQ,_NV > Joint; };
  template<int _NQ, int _NV> struct traits< JointModelDense<_NQ, _NV > > { typedef JointDense<_NQ,_NV > Joint; };

  template <int _NQ, int _NV>
  struct JointDataDense : public JointDataBase< JointDataDense<_NQ, _NV > >
  {
    typedef JointDense<_NQ, _NV > Joint;
    SE3_JOINT_TYPEDEF_TEMPLATE;

    Constraint_t S;
    Transformation_t M;
    Motion_t v;
    Bias_t c;

    F_t F;

    /// Removed Default constructor of JointDataDense because it was calling default constructor of
    /// ConstraintXd -> eigen_static_assert
    /// JointDataDense should always be instanciated from a JointDataXX.toDense()
    // JointDataDense() : M(1)
    // {
    //   M.translation(SE3::Vector3::Zero());
    // }

    JointDataDense() {};

    JointDataDense( Constraint_t S,
                    Transformation_t M,
                    Motion_t v,
                    Bias_t c,
                    F_t F
                    )
    : S(S)
    , M(M)
    , v(v)
    , c(c)
    , F(F)
    {}

    JointDataDense<_NQ, _NV> toDense_impl() const
    {
      assert(false && "Trying to convert a jointDataDense to JointDataDense : useless"); // disapear with release optimizations
      return *this;
    }

  }; // struct JointDataDense

  template <int _NQ, int _NV>
  struct JointModelDense : public JointModelBase< JointModelDense<_NQ, _NV > >
  {
    typedef JointDense<_NQ, _NV > Joint;
    SE3_JOINT_TYPEDEF_TEMPLATE;

    using JointModelBase<JointModelDense<_NQ, _NV > >::id;
    using JointModelBase<JointModelDense<_NQ, _NV > >::idx_q;
    using JointModelBase<JointModelDense<_NQ, _NV > >::idx_v;
    using JointModelBase<JointModelDense<_NQ, _NV > >::lowerPosLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::upperPosLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::maxEffortLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::maxVelocityLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::setLowerPositionLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::setUpperPositionLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::setMaxEffortLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::setMaxVelocityLimit;
    using JointModelBase<JointModelDense<_NQ, _NV > >::setIndexes;
    using JointModelBase<JointModelDense<_NQ, _NV > >::i_v;
    using JointModelBase<JointModelDense<_NQ, _NV > >::i_q;

    int nv_dyn,nq_dyn;
    
    JointData createData() const
    {
      //assert(false && "JointModelDense is read-only, should not createData");
      return JointData();
    }
    void calc( JointData& , 
     const Eigen::VectorXd &  ) const
    {
      assert(false && "JointModelDense is read-only, should not perform any calc");
    }

    void calc( JointData&  ,
     const Eigen::VectorXd & , 
     const Eigen::VectorXd &  ) const
    {
      assert(false && "JointModelDense is read-only, should not perform any calc");
    }

    JointModelDense()
    {
      setLowerPositionLimit(Eigen::Matrix<double,NQ,1>(1));
      setUpperPositionLimit(Eigen::Matrix<double,NQ,1>(1));
      setMaxEffortLimit(Eigen::Matrix<double,NV,1>(1));
      setMaxVelocityLimit(Eigen::Matrix<double,NV,1>(1));
    }
    JointModelDense(  Index idx,
                      int idx_q,
                      int idx_v,
                      Eigen::Matrix<double,NQ,1> lowPos,
                      Eigen::Matrix<double,NQ,1> upPos,
                      Eigen::Matrix<double,NV,1> maxEff,
                      Eigen::Matrix<double,NV,1> maxVel
                    )
    {
      setIndexes(idx, idx_q, idx_v);
      setLowerPositionLimit(lowPos);
      setUpperPositionLimit(upPos);
      setMaxEffortLimit(maxEff);
      setMaxVelocityLimit(maxVel);
    }

    int     nv_impl() const { return nv_dyn; }
    int     nq_impl() const { return nq_dyn; }

    template<typename D>
    typename SizeDepType<NQ>::template SegmentReturn<D>::ConstType
    jointConfigSelector_impl(const Eigen::MatrixBase<D>& a) const { return a.template segment(i_q,nq_dyn); }
    template<typename D>
    typename SizeDepType<NQ>::template SegmentReturn<D>::Type
    jointConfigSelector_impl( Eigen::MatrixBase<D>& a) const { return a.template segment(i_q,nq_dyn); }

    template<typename D>
    typename SizeDepType<NV>::template SegmentReturn<D>::ConstType
    jointVelocitySelector_impl(const Eigen::MatrixBase<D>& a) const { return a.template segment(i_v,nv_dyn); }
    template<typename D>
    typename SizeDepType<NV>::template SegmentReturn<D>::Type
    jointVelocitySelector_impl( Eigen::MatrixBase<D>& a) const { return a.template segment(i_v,nv_dyn); }

    template<typename D>
    typename SizeDepType<NV>::template ColsReturn<D>::ConstType 
    jointCols_impl(const Eigen::MatrixBase<D>& A) const { return A.template middleCols<NV>(i_v); }
    template<typename D>
    typename SizeDepType<NV>::template ColsReturn<D>::Type 
    jointCols_impl(Eigen::MatrixBase<D>& A) const { return A.template middleCols<NV>(i_v); }

    JointModelDense<_NQ, _NV> toDense_impl() const
    {
      assert(false && "Trying to convert a jointModelDense to JointModelDense : useless");
      return *this;
    }

    static const std::string shortname()
    {
      return std::string("JointModelDense");
    }

    template <class D>
    bool operator == (const JointModelBase<D> &) const
    {
      return false;
    }
    
    bool operator == (const JointModelBase<JointModelDense> & jmodel) const
    {
      return jmodel.id() == id()
              && jmodel.idx_q() == idx_q()
              && jmodel.idx_v() == idx_v()
              && jmodel.lowerPosLimit() == lowerPosLimit()
              && jmodel.upperPosLimit() == upperPosLimit()
              && jmodel.maxEffortLimit() == maxEffortLimit()
              && jmodel.maxVelocityLimit() == maxVelocityLimit();
    }

  }; // struct JointModelDense

  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template SegmentReturn<D>::ConstType
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointConfigSelector_impl(const Eigen::MatrixBase<D>& a) const { return a.segment(i_q,nq_dyn); }
  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template SegmentReturn<D>::Type
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointConfigSelector_impl(Eigen::MatrixBase<D>& a) const { return a.segment(i_q,nq_dyn); }
  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template SegmentReturn<D>::ConstType
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointVelocitySelector_impl(const Eigen::MatrixBase<D>& a) const { return a.segment(i_v,nv_dyn); }
  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template SegmentReturn<D>::Type
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointVelocitySelector_impl(Eigen::MatrixBase<D>& a) const { return a.segment(i_v,nv_dyn); }

  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template ColsReturn<D>::ConstType 
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointCols_impl(const Eigen::MatrixBase<D>& A) const { return A.middleCols(i_v,nv_dyn); }
  template<>
  template<typename D>
  typename SizeDepType<Eigen::Dynamic>::template ColsReturn<D>::Type 
  JointModelDense<Eigen::Dynamic,Eigen::Dynamic>::
  jointCols_impl(Eigen::MatrixBase<D>& A) const { return A.middleCols(i_v,nv_dyn); }

} // namespace se3

#endif // ifndef __se3_joint_dense_hpp__
