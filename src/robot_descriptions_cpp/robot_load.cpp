#include "robot_load.hpp"
#include "robot_spec.hpp"
#include <pinocchio/parsers/urdf.hpp>

namespace robot_descriptions {

void loadModelFromSpec(const robot_spec &spec, pinocchio::Model &model,
                       bool verbose) {
  pinocchio::urdf::buildModel(spec.urdfPath, model, verbose);
}

void loadGeomFromSpec(const robot_spec &spec, const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type) {
  std::vector<std::string> package_dirs = {PACKAGE_DIRS_BASE};
  pinocchio::urdf::buildGeom(model, spec.urdfPath, type, geomModel,
                             package_dirs);
}

void loadModelFromToml(const std::string &tomlFile, const std::string &key,
                       pinocchio::Model &model, bool verbose) {
  robot_spec spec = loadRobotSpecFromToml(tomlFile, key, verbose);
  loadModelFromSpec(spec, model, verbose);
}

void loadGeomFromToml(const std::string &tomlFile, const std::string &key,
                      const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type) {
  robot_spec spec = loadRobotSpecFromToml(tomlFile, key);
  loadGeomFromSpec(spec, model, geomModel, type);
}

void loadModelsFromToml(const std::string &tomlFile, const std::string &key,
                        pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel) {
  robot_spec spec = loadRobotSpecFromToml(tomlFile, key);
  loadModelsFromSpec(spec, model, visualModel, collisionModel);
}

} // namespace robot_descriptions
