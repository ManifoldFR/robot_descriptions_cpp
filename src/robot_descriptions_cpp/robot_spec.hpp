#pragma once

#include <string>
#include <vector>

namespace robot_descriptions {

/// \brief Intermediate data format for the metadat to use when loading the
/// robot: URDF and SRDF file, package dirs.
struct robot_spec {
  std::string urdf_path;
  std::string srdf_path;
  std::string ref_posture;
  std::string package_path;
  bool floating_base;
};

/// \brief Get list of package dirs for the given robot_spec.
std::vector<std::string> getPackageDirs(const robot_spec &spec);

std::ostream &operator<<(std::ostream &oss, const robot_spec &spec);

} // namespace robot_descriptions
