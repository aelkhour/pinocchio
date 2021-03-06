//
// Copyright (c) 2015 CNRS
// Copyright (c) 2015 Wandercraft, 86 rue de Paris 91400 Orsay, France.
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

#include "pinocchio/multibody/parser/sample-models.hpp"

#ifdef WITH_HPP_FCL
#include <hpp/fcl/shape/geometric_shapes.h>
#endif

namespace se3
{
  namespace buildModels
  {

    void humanoid2d(Model& model)
    {
      model.addBody(model.getBodyId("universe"),JointModelRX(),SE3::Identity(),Inertia::Random(),
                    "ff1_joint", "ff1_body");
      model.addBody(model.getBodyId("ff1_body"),JointModelRY(),SE3::Identity(),Inertia::Random(),
                    "root_joint", "root_body");

      model.addBody(model.getBodyId("root_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                    "lleg1_joint", "lleg1_body");
      model.addBody(model.getBodyId("lleg1_body"),JointModelRY(),SE3::Random(),Inertia::Random(),
                    "lleg2_joint", "lleg2_body");

      model.addBody(model.getBodyId("root_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                    "rleg1_joint", "rleg1_body");
      model.addBody(model.getBodyId("rleg1_body"),JointModelRY(),SE3::Random(),Inertia::Random(),
                    "rleg2_joint", "rleg2_body");

      model.addBody(model.getBodyId("root_body"),JointModelRY(),SE3::Random(),Inertia::Random(),
                    "torso1_joint", "torso1_body");
      model.addBody(model.getBodyId("torso1_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                    "chest_joint", "chest_body");

      model.addBody(model.getBodyId("chest_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    "rarm1_joint", "rarm1_body");
      model.addBody(model.getBodyId("rarm1_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                    "rarm2_joint", "rarm2_body");

      model.addBody(model.getBodyId("chest_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    "larm1_joint", "larm1_body");
      model.addBody(model.getBodyId("larm1_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                    "larm2_joint", "larm2_body");
    }

    void humanoidSimple(Model& model, bool usingFF)
    {
      if(! usingFF )
      {
        model.addBody(model.getBodyId("universe"),JointModelRX(),SE3::Identity(),Inertia::Random(),
                      "ff1_joint", "ff1_body");
        model.addBody(model.getBodyId("ff1_body"),JointModelRY(),SE3::Identity(),Inertia::Random(),
                      "ff2_joint", "ff2_body");
        model.addBody(model.getBodyId("ff2_body"),JointModelRZ(),SE3::Identity(),Inertia::Random(),
                      "ff3_joint", "ff3_body");
        model.addBody(model.getBodyId("ff3_body"),JointModelRZ(),SE3::Random(),Inertia::Random(),
                      "ff4_joint", "ff4_body");
        model.addBody(model.getBodyId("ff4_body"),JointModelRY(),SE3::Identity(),Inertia::Random(),
                      "ff5_joint", "ff5_body");
        model.addBody(model.getBodyId("ff5_body"),JointModelRX(),SE3::Identity(),Inertia::Random(),
                      "root_joint", "root_body");
      }
      else
      {
        model.addBody(model.getBodyId("universe"),JointModelFreeFlyer(),
                      SE3::Identity(),Inertia::Random(),
                      Eigen::VectorXd::Zero(6), 1e3 * (Eigen::VectorXd::Random(6).array() + 1),
                      1e3 * (Eigen::VectorXd::Random(7).array() - 1),
                      1e3 * (Eigen::VectorXd::Random(7).array() + 1),
                      "root_joint", "root_body");
      }

      model.addBody(model.getBodyId("root_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg1_joint", "lleg1_body");
      model.addBody(model.getBodyId("lleg1_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg2_joint", "lleg2_body");
      model.addBody(model.getBodyId("lleg2_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg3_joint", "lleg3_body");
      model.addBody(model.getBodyId("lleg3_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg4_joint", "lleg4_body");
      model.addBody(model.getBodyId("lleg4_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg5_joint", "lleg5_body");
      model.addBody(model.getBodyId("lleg5_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "lleg6_joint", "lleg6_body");

      model.addBody(model.getBodyId("root_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg1_joint", "rleg1_body");
      model.addBody(model.getBodyId("rleg1_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg2_joint", "rleg2_body");
      model.addBody(model.getBodyId("rleg2_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg3_joint", "rleg3_body");
      model.addBody(model.getBodyId("rleg3_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg4_joint", "rleg4_body");
      model.addBody(model.getBodyId("rleg4_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg5_joint", "rleg5_body");
      model.addBody(model.getBodyId("rleg5_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rleg6_joint", "rleg6_body");

      model.addBody(model.getBodyId("root_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "torso1_joint", "torso1_body");
      model.addBody(model.getBodyId("torso1_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "chest_joint", "chest_body");

      model.addBody(model.getBodyId("chest_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm1_joint", "rarm1_body");
      model.addBody(model.getBodyId("rarm1_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm2_joint", "rarm2_body");
      model.addBody(model.getBodyId("rarm2_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm3_joint", "rarm3_body");
      model.addBody(model.getBodyId("rarm3_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm4_joint", "rarm4_body");
      model.addBody(model.getBodyId("rarm4_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm5_joint", "rarm5_body");
      model.addBody(model.getBodyId("rarm5_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "rarm6_joint", "rarm6_body");

      model.addBody(model.getBodyId("chest_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm1_joint", "larm1_body");
      model.addBody(model.getBodyId("larm1_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm2_joint", "larm2_body");
      model.addBody(model.getBodyId("larm2_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm3_joint", "larm3_body");
      model.addBody(model.getBodyId("larm3_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm4_joint", "larm4_body");
      model.addBody(model.getBodyId("larm4_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm5_joint", "larm5_body");
      model.addBody(model.getBodyId("larm5_body"),JointModelRX(),SE3::Random(),Inertia::Random(),
                    Eigen::VectorXd::Random(1).array() + 1, Eigen::VectorXd::Random(1).array() + 1,
                    Eigen::VectorXd::Random(1).array() - 1, Eigen::VectorXd::Random(1).array() + 1,
                    "larm6_joint", "larm6_body");
    }

    #ifdef WITH_HPP_FCL
    void collisionModel( Model& model, GeometryModel& model_geom)
    {
      model.addBody(model.getBodyId("universe"),JointModelPlanar(),SE3::Identity(),Inertia::Random(),
                    "planar1_joint", "planar1_body");
      model.addBody(model.getBodyId("universe"),JointModelPlanar(),SE3::Identity(),Inertia::Random(),
                    "planar2_joint", "planar2_body");

      boost::shared_ptr<fcl::Box> Sample(new fcl::Box(1));
      fcl::CollisionObject box1(Sample, fcl::Transform3f());
      model_geom.addGeomObject(model.getJointId("planar1_joint"),box1, SE3::Identity(),  "ff1_collision_object"); 

      boost::shared_ptr<fcl::Box> Sample2(new fcl::Box(1));
      fcl::CollisionObject box2(Sample, fcl::Transform3f());
      model_geom.addGeomObject(model.getJointId("planar2_joint"),box2, SE3::Identity(),  "ff2_collision_object");

    }
    #endif

  } // namespace buildModels
} // namespace se3
