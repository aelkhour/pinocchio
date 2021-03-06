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

#ifndef __se3_joint_prismatic_unaligned_hpp__
#define __se3_joint_prismatic_unaligned_hpp__

#include "pinocchio/multibody/joint/joint-base.hpp"
#include "pinocchio/multibody/joint/joint-dense.hpp"
#include "pinocchio/multibody/constraint.hpp"
#include "pinocchio/spatial/inertia.hpp"

namespace se3
{

  struct JointDataPrismaticUnaligned;
  struct JointModelPrismaticUnaligned;

  struct MotionPrismaticUnaligned;
  
  template <>
  struct traits <MotionPrismaticUnaligned>
  {
    typedef double Scalar_t;
    typedef Eigen::Matrix<Scalar_t,3,1,0> Vector3;
    typedef Eigen::Matrix<Scalar_t,4,1,0> Vector4;
    typedef Eigen::Matrix<Scalar_t,6,1,0> Vector6;
    typedef Eigen::Matrix<Scalar_t,3,3,0> Matrix3;
    typedef Eigen::Matrix<Scalar_t,4,4,0> Matrix4;
    typedef Eigen::Matrix<Scalar_t,6,6,0> Matrix6;
    typedef Vector3 Angular_t;
    typedef Vector3 Linear_t;
    typedef Matrix6 ActionMatrix_t;
    typedef Eigen::Quaternion<Scalar_t,0> Quaternion_t;
    typedef SE3Tpl<Scalar_t,0> SE3;
    typedef ForceTpl<Scalar_t,0> Force;
    typedef MotionTpl<Scalar_t,0> Motion;
    typedef Symmetric3Tpl<Scalar_t,0> Symmetric3;
    enum {
      LINEAR = 0,
      ANGULAR = 3
    };
  }; // traits MotionPrismaticUnaligned

  struct MotionPrismaticUnaligned : MotionBase <MotionPrismaticUnaligned>
  {
    SPATIAL_TYPEDEF_NO_TEMPLATE(MotionPrismaticUnaligned);

    MotionPrismaticUnaligned () : axis(Vector3::Constant(NAN)), v(NAN) {}
    MotionPrismaticUnaligned (const Vector3 & axis, const Scalar_t v) : axis(axis), v(v) {}

    Vector3 axis;
    Scalar_t v;

    operator Motion() const { return Motion(axis*v, Vector3::Zero());}
  }; // struct MotionPrismaticUnaligned

  inline const MotionPrismaticUnaligned & operator+ (const MotionPrismaticUnaligned & m, const BiasZero &)
  { return m; }

  inline Motion operator+ (const MotionPrismaticUnaligned & m1, const Motion & m2)
  {
    return Motion(m1.v*m1.axis + m2.linear(), m2.angular());
  }

  struct ConstraintPrismaticUnaligned;
  template <>
  struct traits <ConstraintPrismaticUnaligned>
  {
    typedef double Scalar_t;
    typedef Eigen::Matrix<Scalar_t,3,1,0> Vector3;
    typedef Eigen::Matrix<Scalar_t,4,1,0> Vector4;
    typedef Eigen::Matrix<Scalar_t,6,1,0> Vector6;
    typedef Eigen::Matrix<Scalar_t,3,3,0> Matrix3;
    typedef Eigen::Matrix<Scalar_t,4,4,0> Matrix4;
    typedef Eigen::Matrix<Scalar_t,6,6,0> Matrix6;
    typedef Matrix3 Angular_t;
    typedef Vector3 Linear_t;
    typedef Matrix6 ActionMatrix_t;
    typedef Eigen::Quaternion<Scalar_t,0> Quaternion_t;
    typedef SE3Tpl<Scalar_t,0> SE3;
    typedef ForceTpl<Scalar_t,0> Force;
    typedef MotionTpl<Scalar_t,0> Motion;
    typedef Symmetric3Tpl<Scalar_t,0> Symmetric3;
    enum {
      LINEAR = 0,
      ANGULAR = 3
    };
    typedef Eigen::Matrix<Scalar_t,1,1,0> JointMotion;
    typedef Eigen::Matrix<Scalar_t,1,1,0> JointForce;
    typedef Eigen::Matrix<Scalar_t,6,1> DenseBase;
  }; // traits ConstraintPrismaticUnaligned

    struct ConstraintPrismaticUnaligned : ConstraintBase <ConstraintPrismaticUnaligned>
    {
      SPATIAL_TYPEDEF_NO_TEMPLATE(ConstraintPrismaticUnaligned);
      enum { NV = 1, Options = 0 };
      typedef traits<ConstraintPrismaticUnaligned>::JointMotion JointMotion;
      typedef traits<ConstraintPrismaticUnaligned>::JointForce JointForce;
      typedef traits<ConstraintPrismaticUnaligned>::DenseBase DenseBase;
      
      ConstraintPrismaticUnaligned () : axis (Vector3::Constant(NAN)) {}
      ConstraintPrismaticUnaligned (const Vector3 & axis) : axis(axis) {}
               
      Vector3 axis;

      template<typename D>
      MotionPrismaticUnaligned operator* (const Eigen::MatrixBase<D> & v) const
      { 
      	EIGEN_STATIC_ASSERT_VECTOR_SPECIFIC_SIZE(D,1);
      	return MotionPrismaticUnaligned(axis,v[0]); 
      }

      Vector6 se3Action (const SE3 & m) const
      {
        Vector6 res;
        res.head<3> () = m.rotation()*axis;
        res.tail<3>().setZero();
        return res;
      }

      int nv_impl() const { return NV; }

      struct TransposeConst
      {
        typedef traits<ConstraintPrismaticUnaligned>::Scalar_t Scalar_t;
        typedef traits<ConstraintPrismaticUnaligned>::Force Force;
        typedef traits<ConstraintPrismaticUnaligned>::Vector6 Vector6;
        
      	const ConstraintPrismaticUnaligned & ref; 
      	TransposeConst(const ConstraintPrismaticUnaligned & ref) : ref(ref) {}
        
      	const Eigen::Matrix<Scalar_t, 1, 1>
      	operator* (const Force & f) const
      	{
      	  return ref.axis.transpose()*f.linear();
      	}

        /* [CRBA]  MatrixBase operator* (Constraint::Transpose S, ForceSet::Block) */
        template<typename D>
        friend
        typename Eigen::ProductReturnType<
        Eigen::Transpose<const Eigen::Matrix<typename Eigen::MatrixBase<D>::Scalar, 3, 1> >,
        Eigen::Block<const Eigen::Block<Eigen::Matrix<typename Eigen::MatrixBase<D>::Scalar,6,-1>,-1,-1>, 3, -1>
        >::Type
        operator* (const TransposeConst & tc, const Eigen::MatrixBase<D> & F)
        {
          /* Return ax.T * F[1:3,:] */
          assert(F.rows()==6);
          return tc.ref.axis.transpose () * F.template topRows<3> ();
        }

      };
      TransposeConst transpose() const { return TransposeConst(*this); }


      /* CRBA joint operators
       *   - ForceSet::Block = ForceSet
       *   - ForceSet operator* (Inertia Y,Constraint S)
       *   - MatrixBase operator* (Constraint::Transpose S, ForceSet::Block)
       *   - SE3::act(ForceSet::Block)
       */
      operator ConstraintXd () const
      {
        Vector6 S;
      	S << axis, Vector3::Zero();
      	return ConstraintXd(S);
      }
      
    }; // struct ConstraintPrismaticUnaligned


    inline Motion operator^ (const Motion & m1, const MotionPrismaticUnaligned & m2)
    {
      /* m1xm2 = [ v1xw2 + w1xv2; w1xw2 ] = [ v1xw2; w1xw2 ] */
      const Motion::Vector3 & w1 = m1.angular();
      const Motion::Vector3 & v2 = m2.axis * m2.v;
      return Motion (w1.cross(v2), Motion::Vector3::Zero());
    }

    /* [CRBA] ForceSet operator* (Inertia Y,Constraint S) */
    inline Eigen::Matrix<double,6,1>
    operator* (const Inertia & Y, const ConstraintPrismaticUnaligned & cpu)
    { 
      /* YS = [ m -mcx ; mcx I-mcxcx ] [ v ; 0 ] = [ mv ; mcxv ] */
      const double & m                = Y.mass();
      const Inertia::Vector3 & c      = Y.lever();

      Eigen::Matrix<double,6,1> res;
      res.head<3>() = m*cpu.axis;
      res.tail<3>() = c.cross(res.head<3>());
      return res;
    }
  
    namespace internal 
    {
      template<>
      struct ActionReturn<ConstraintPrismaticUnaligned >  
      { typedef Eigen::Matrix<double,6,1> Type; };
    }

    struct JointPrismaticUnaligned;
    template<>
    struct traits<JointPrismaticUnaligned>
    {
      typedef JointDataPrismaticUnaligned JointData;
      typedef JointModelPrismaticUnaligned JointModel;
      typedef ConstraintPrismaticUnaligned Constraint_t;
      typedef SE3 Transformation_t;
      typedef MotionPrismaticUnaligned Motion_t;
      typedef BiasZero Bias_t;
      typedef Eigen::Matrix<double,6,1> F_t;
      enum {
        NQ = 1,
        NV = 1
      };
    };

  template<> struct traits<JointDataPrismaticUnaligned> { typedef JointPrismaticUnaligned Joint; };
  template<> struct traits<JointModelPrismaticUnaligned> { typedef JointPrismaticUnaligned Joint; };

  struct JointDataPrismaticUnaligned : public JointDataBase <JointDataPrismaticUnaligned>
  {
    typedef JointPrismaticUnaligned Joint;
    SE3_JOINT_TYPEDEF;

    Transformation_t M;
    Constraint_t S;
    Motion_t v;
    Bias_t c;

    F_t F;

    JointDataPrismaticUnaligned() :
      M(1),
      S(Eigen::Vector3d::Constant(NAN)),
      v(Eigen::Vector3d::Constant(NAN),NAN)
    {}
    
    JointDataPrismaticUnaligned(const Motion_t::Vector3 & axis) :
      M(1),
      S(axis),
      v(axis,NAN)
    {}

    JointDataDense<NQ, NV> toDense_impl() const
    {
      return JointDataDense<NQ, NV>(S, M, v, c, F);
    }
  }; // struct JointDataPrismaticUnaligned

  struct JointModelPrismaticUnaligned : public JointModelBase <JointModelPrismaticUnaligned>
  {
    typedef JointPrismaticUnaligned Joint;
    SE3_JOINT_TYPEDEF;

    using JointModelBase<JointModelPrismaticUnaligned>::id;
    using JointModelBase<JointModelPrismaticUnaligned>::idx_q;
    using JointModelBase<JointModelPrismaticUnaligned>::idx_v;
    using JointModelBase<JointModelPrismaticUnaligned>::lowerPosLimit;
    using JointModelBase<JointModelPrismaticUnaligned>::upperPosLimit;
    using JointModelBase<JointModelPrismaticUnaligned>::maxEffortLimit;
    using JointModelBase<JointModelPrismaticUnaligned>::maxVelocityLimit;
    using JointModelBase<JointModelPrismaticUnaligned>::setIndexes;
    typedef Motion::Vector3 Vector3;
    typedef double Scalar_t;
    
    JointModelPrismaticUnaligned() : axis(Vector3::Constant(NAN))   {}
    JointModelPrismaticUnaligned(Scalar_t x, Scalar_t y, Scalar_t z)
    {
      axis << x, y, z ;
      axis.normalize();
      assert(axis.isUnitary() && "Translation axis is not unitary");
    }
    
    JointModelPrismaticUnaligned(const Vector3 & axis) : axis(axis)
    {
      assert(axis.isUnitary() && "Translation axis is not unitary");
    }

    JointData createData() const { return JointData(axis); }
    
    void calc(JointData & data, const Eigen::VectorXd & qs) const
    {
      const double & q = qs[idx_q()];

      /* It should not be necessary to copy axis in jdata, however a current bug
       * in the fusion visitor prevents a proper access to jmodel::axis. A
       * by-pass is to access to a copy of it in jdata. */
      data.M.translation() = axis * q;
    }

    void calc(JointData & data,
              const Eigen::VectorXd & qs,
              const Eigen::VectorXd & vs) const
    {
      const Scalar_t & q = qs[idx_q()];
      const Scalar_t & v = vs[idx_v()];

      /* It should not be necessary to copy axis in jdata, however a current bug
       * in the fusion visitor prevents a proper access to jmodel::axis. A
       * by-pass is to access to a copy of it in jdata. */
      data.M.translation() = axis * q;
      data.v.v = v;
    }

    Vector3 axis;

    JointModelDense<NQ, NV> toDense_impl() const
    {
      return JointModelDense<NQ, NV>( id(),
                                      idx_q(),
                                      idx_v(),
                                      lowerPosLimit(),
                                      upperPosLimit(),
                                      maxEffortLimit(),
                                      maxVelocityLimit()
                                    );
    }

    static const std::string shortname()
    {
      return std::string("JointModelPrismaticUnaligned");
    }

    template <class D>
    bool operator== (const JointModelBase<D> &) const
    {
      return false;
    }
    
    bool operator== (const JointModelBase<JointModelPrismaticUnaligned> & jmodel) const
    {
      return jmodel.id() == id()
              && jmodel.idx_q() == idx_q()
              && jmodel.idx_v() == idx_v()
              && jmodel.lowerPosLimit() == lowerPosLimit()
              && jmodel.upperPosLimit() == upperPosLimit()
              && jmodel.maxEffortLimit() == maxEffortLimit()
              && jmodel.maxVelocityLimit() == maxVelocityLimit();
    }
  }; // struct JointModelPrismaticUnaligned

} //namespace se3


#endif // ifndef __se3_joint_prismatic_unaligned_hpp__
