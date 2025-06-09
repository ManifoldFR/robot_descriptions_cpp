#pragma once

#include <string>
#include <vector>

namespace robot_descriptions {

struct robot_spec {
  std::string urdf_path;
  std::string srdf_path;
  std::string ref_posture;
  std::string package_path;
  bool floating_base;
};

std::vector<std::string> get_package_dirs(const robot_spec &spec);

std::ostream &operator<<(std::ostream &oss, const robot_spec &spec);

} // namespace robot_descriptions
