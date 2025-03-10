#pragma once

#include "robot_spec.hpp"
#include <filesystem>
#include <string_view>

namespace robot_descriptions {
namespace fs = std::filesystem;

static const fs::path EXAMPLE_ROBOT_DATA_PACKAGE_DIRS =
    fs::path(EXAMPLE_ROBOT_DATA_MODEL_DIR) / "../..";

robot_spec loadErdRobotSpecFromToml(std::string_view filename,
                                    std::string_view key, bool verbose = false);

} // namespace robot_descriptions
