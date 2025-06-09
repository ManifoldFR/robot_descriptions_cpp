#include "load_spec.hpp"
#include "third-party/toml.hpp"
#include <iostream>
#include <optional>

namespace robot_descriptions {

template <typename T>
auto sesecnoval_inplace(const std::optional<T> &v1, std::optional<T> &v2) {
  v2 = v1.has_value() ? v1 : v2;
}

#define _REPLACE_FIELD(name) sesecnoval_inplace(other.name, this->name)

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

spec_load_data from_toml(const toml::table &tbl) {
  spec_load_data out;
  out.path = tbl["path"].value<std::string>();
  out.urdf_subpath = tbl["urdf_subpath"].value<std::string>();
  out.urdf_filename = tbl["urdf_filename"].value<std::string>();
  out.srdf_subpath = tbl["srdf_subpath"].value<std::string>();
  out.srdf_filename = tbl["srdf_filename"].value<std::string>();
  out.ref_posture = tbl["ref_posture"].value<std::string>();
  out.free_flyer = tbl["free_flyer"].value<bool>();
  return out;
}

robot_spec loadErdRobotSpecFromToml(std::string_view fname,
                                    std::string_view key, bool verbose) {
  const fs::path tomlPath = fs::path{DEFAULT_TOML_DIR} / fname;
  if (verbose)
    printf("Loading robot spec from TOML file %s\n", tomlPath.c_str());
  toml::table data;
  try {
    data = toml::parse_file(tomlPath.string());
  } catch (const toml::parse_error &err) {
    std::cerr << "Error parsing file " << err.source().path //
              << ":\n"
              << err.description() << "\n (" << err.source().begin << ")\n";
    throw;
  }

  const spec_load_data parent = from_toml(data);
  spec_load_data child;
  if (auto child_tbl = data[key].as_table()) {
    child = from_toml(*child_tbl);
  } else {
    throw std::runtime_error("Child table now found.");
  }
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
      path / c2.urdf_subpath.value_or("robots") / c2.urdf_filename.value(),
      has_srdf
          ? path / c2.srdf_subpath.value_or("srdf") / c2.srdf_filename.value()
          : "",
      c2.ref_posture.value_or("standing"),
      EXAMPLE_ROBOT_DATA_PACKAGE_DIRS,
      c2.free_flyer.value_or(false),
  };

  if (verbose)
    std::cout << result << std::endl;

  return result;
}

} // namespace robot_descriptions
