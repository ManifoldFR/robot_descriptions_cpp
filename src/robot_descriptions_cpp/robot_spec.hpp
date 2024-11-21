#pragma once

#include <filesystem>
#include <string>

namespace robot_descriptions {
namespace fs = std::filesystem;

extern const fs::path PACKAGE_DIRS_BASE;

struct robot_spec {
  std::string path;
  std::string urdfPath;
  std::string srdfPath;
  std::string refPosture;
  bool floatingBase;
};

robot_spec loadRobotSpecFromToml(const std::string &fname,
                                 const std::string &key, bool verbose = false);

} // namespace robot_descriptions
