#include "robot_load.hpp"
#include "load_spec.hpp"
#include "robot_spec.hpp"

#include <filesystem>
#include <pinocchio/parsers/srdf.hpp>
#include <pinocchio/parsers/urdf.hpp>

namespace robot_descriptions {

std::vector<std::string> getPackageDirs(const robot_spec &spec) {
  return std::vector<std::string>{
      spec.package_path,
      fs::path(spec.package_path).parent_path(),
      fs::path(spec.urdf_path).parent_path(),
  };
}

void loadModelFromSpec(const robot_spec &spec, pinocchio::Model &model,
                       bool verbose) {
  pinocchio::urdf::buildModel(spec.urdf_path, model, verbose);
  if (!spec.srdf_path.empty()) {
    pinocchio::srdf::loadReferenceConfigurations(model, spec.srdf_path,
                                                 verbose);
  }
}

void loadGeomFromSpec(const robot_spec &spec, const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type) {
  pinocchio::urdf::buildGeom(model, spec.urdf_path, type, geomModel,
                             getPackageDirs(spec));
}

void loadModelFromToml(const std::string &tomlFile, const std::string &key,
                       pinocchio::Model &model, bool verbose) {
  robot_spec spec = loadErdRobotSpecFromToml(tomlFile, key, verbose);
  loadModelFromSpec(spec, model, verbose);
}

void loadGeomFromToml(const std::string &tomlFile, const std::string &key,
                      const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type) {
  robot_spec spec = loadErdRobotSpecFromToml(tomlFile, key);
  loadGeomFromSpec(spec, model, geomModel, type);
}

void loadModelsFromToml(const std::string &tomlFile, const std::string &key,
                        pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel) {
  robot_spec spec = loadErdRobotSpecFromToml(tomlFile, key);
  loadModelsFromSpec(spec, model, visualModel, collisionModel);
}

} // namespace robot_descriptions
