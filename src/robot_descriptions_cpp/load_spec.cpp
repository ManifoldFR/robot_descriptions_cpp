#include "load_spec.hpp"
#include <optional>
#include <toml11/conversion.hpp>
#include <toml11/parser.hpp>

namespace robot_descriptions {

template <typename T>
auto sesecnoval_inplace(const std::optional<T> &v1, std::optional<T> &v2) {
  v2 = v1.has_value() ? v1 : v2;
}

template <typename V, typename U>
void _ssnv_apply_self(V U::*mptr, U &self, const U &other) {
  sesecnoval_inplace(other.*mptr, self.*mptr);
}

#define _REPLACE_FIELD(name)                                                   \
  _ssnv_apply_self(&spec_load_data::name, *this, other)

struct spec_load_data {
  std::optional<std::string> path;
  std::optional<std::string> urdf_subpath;
  std::optional<std::string> urdf_filename;
  std::optional<std::string> srdf_subpath;
  std::optional<std::string> srdf_filename;
  std::optional<std::string> ref_posture;
  std::optional<bool> free_flyer;

  spec_load_data &join(const spec_load_data &other) {
    _REPLACE_FIELD(path);
    _REPLACE_FIELD(urdf_subpath);
    _REPLACE_FIELD(urdf_filename);
    _REPLACE_FIELD(srdf_subpath);
    _REPLACE_FIELD(srdf_filename);
    _REPLACE_FIELD(ref_posture);
    _REPLACE_FIELD(free_flyer);
    return *this;
  }
};
} // namespace robot_descriptions
TOML11_DEFINE_CONVERSION_NON_INTRUSIVE(robot_descriptions::spec_load_data, path,
                                       urdf_subpath, urdf_filename,
                                       srdf_subpath, srdf_filename, ref_posture,
                                       free_flyer)

namespace robot_descriptions {

robot_spec loadErdRobotSpecFromToml(std::string_view fname,
                                    std::string_view key, bool verbose) {
  const fs::path tomlPath = fs::path{ROBOT_TOML_DIR} / fname;
  printf("Loading robot spec from TOML file %s\n", tomlPath.c_str());
  const toml::value data = toml::parse(tomlPath);

  const spec_load_data parent = toml::get<spec_load_data>(data);
  const spec_load_data child = toml::find<spec_load_data>(data, key.data());
  spec_load_data c2 = parent;
  c2.join(child);

  if (!c2.path)
    throw std::runtime_error("Robot TOML file contained no \"path\" key.");

  const fs::path path =
      fs::path(EXAMPLE_ROBOT_DATA_MODEL_DIR) / c2.path.value();

  if (!c2.urdf_filename.has_value())
    throw std::runtime_error(
        "Robot TOML file contained no \"urdf_filename\" key.");
  const bool has_srdf = c2.srdf_filename.has_value();

  robot_spec result{
      path,
      path / c2.urdf_subpath.value_or("robots") / c2.urdf_filename.value(),
      has_srdf
          ? path / c2.srdf_subpath.value_or("srdf") / c2.srdf_filename.value()
          : "",
      c2.ref_posture.value_or("standing"),
      EXAMPLE_ROBOT_DATA_PACKAGE_DIRS,
      c2.free_flyer.value_or(false),
  };

  if (verbose) {
    printf("Loaded robot:\n > URDF file %s\n", result.urdf_path.c_str());
    if (!result.srdf_path.empty())
      printf(" > SRDF file %s\n", result.srdf_path.c_str());
    if (result.floating_base)
      printf(" > Robot has floating base\n");
  }
  return result;
}

} // namespace robot_descriptions
