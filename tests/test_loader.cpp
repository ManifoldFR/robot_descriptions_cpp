#include "robot_descriptions_cpp/load_spec.hpp"
#include "robot_descriptions_cpp/robot_load.hpp"
#include "robot_descriptions_cpp/robot_spec.hpp"

#include <gtest/gtest.h>

using namespace robot_descriptions;
namespace fs = std::filesystem;

GTEST_TEST(LoadSpec, UR5) {
  robot_spec spec = loadErdRobotSpecFromToml("ur.toml", "ur5", true);
  EXPECT_TRUE(fs::exists(spec.urdf_path));
}

GTEST_TEST(LoadSpec, ANYmalB) {
  robot_spec spec = loadErdRobotSpecFromToml("ANYmal.toml", "anymal_b", true);
  EXPECT_TRUE(fs::exists(spec.urdf_path));
}

GTEST_TEST(LoadSpec, ANYmalC) {
  robot_spec spec = loadErdRobotSpecFromToml("ANYmal.toml", "anymal_c", true);
  EXPECT_TRUE(fs::exists(spec.urdf_path));
}

GTEST_TEST(LoadTest, UR5) {
  pinocchio::Model model;
  pinocchio::GeometryModel geomModel;
  robot_descriptions::loadModelFromToml("ur.toml", "ur5", model);
  robot_descriptions::loadGeomFromToml("ur.toml", "ur5", model, geomModel,
                                       pinocchio::VISUAL);
  EXPECT_EQ(model.njoints, 7);
  EXPECT_EQ(model.nq, 6);
  EXPECT_EQ(model.name, "ur5");
  EXPECT_EQ(geomModel.ngeoms, 7);
}

GTEST_TEST(LoadTest, UR5_gripper) {
  pinocchio::Model model;
  robot_descriptions::loadModelFromToml("ur.toml", "ur5_gripper", model);
  EXPECT_EQ(model.njoints, 7);
  EXPECT_EQ(model.nq, 6);
  EXPECT_EQ(model.name, "ur5");
}

GTEST_TEST(LoadTest, UR5_limited) {
  pinocchio::Model model;
  robot_descriptions::loadModelFromToml("ur.toml", "ur5_limited", model);
  EXPECT_EQ(model.njoints, 7);
  EXPECT_EQ(model.nq, 6);
  EXPECT_EQ(model.name, "ur5");
}

GTEST_TEST(LoadTest, UR3) {
  pinocchio::Model model;
  robot_descriptions::loadModelFromToml("ur.toml", "ur3", model);
  EXPECT_EQ(model.njoints, 7);
  EXPECT_EQ(model.nq, 6);
  EXPECT_EQ(model.name, "ur3");
}

GTEST_TEST(LoadTest, DoublePendulum) {
  pinocchio::Model model;
  robot_descriptions::loadModelFromToml("double_pendulum.toml",
                                        "double_pendulum", model);
  EXPECT_EQ(model.njoints, 3);
  EXPECT_EQ(model.nq, 2);
  EXPECT_EQ(model.nv, 2);
  EXPECT_EQ(model.name, "2dof_planar");
}

GTEST_TEST(LoadTest, DoublePendulumContinuous) {
  pinocchio::Model model;
  robot_descriptions::loadModelFromToml("double_pendulum.toml",
                                        "double_pendulum_continuous", model);
  EXPECT_EQ(model.njoints, 3);
  EXPECT_EQ(model.nq, 4);
  EXPECT_EQ(model.nv, 2);
  EXPECT_EQ(model.name, "2dof_planar");
}
