#pragma once

#include <string>

namespace robot_descriptions {

struct robot_spec {
  std::string path;
  std::string urdf_path;
  std::string srdf_path;
  std::string ref_posture;
  bool floating_base;
};

} // namespace robot_descriptions
