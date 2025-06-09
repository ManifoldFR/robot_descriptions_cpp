#include "robot_spec.hpp"
#include "load_spec.hpp"

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

std::ostream &operator<<(std::ostream &oss, const robot_spec &spec) {
  oss << "robot_spec {"
      << "\n    urdf_path:      " << spec.urdf_path                       //
      << "\n    srdf_path:      " << spec.srdf_path                       //
      << "\n    ref_posture:    " << spec.ref_posture                     //
      << "\n    package_path:   " << spec.package_path                    //
      << "\n    floating_base:  " << std::boolalpha << spec.floating_base //
      << "\n}";
  return oss;
}

void loadModelFromSpec(const robot_spec &spec, pinocchio::Model &model,
                       bool verbose) {
  pinocchio::urdf::buildModel(spec.urdf_path, model, verbose);
  if (fs::exists(spec.srdf_path)) {
    pinocchio::srdf::loadReferenceConfigurations(model, spec.srdf_path,
                                                 verbose);
    try {
      pinocchio::srdf::loadRotorParameters(model, spec.srdf_path, verbose);
    } catch (const std::invalid_argument &) {
      // catch error
      return;
    }
  }
}

void loadModelsFromSpec(const robot_spec &spec, pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel,
                        bool verbose) {
  loadModelFromSpec(spec, model, verbose);
  auto package_dirs = getPackageDirs(spec);
  if (visualModel)
    pinocchio::urdf::buildGeom(model, spec.urdf_path, pinocchio::VISUAL,
                               *visualModel);
  if (collisionModel) {
    pinocchio::urdf::buildGeom(model, spec.urdf_path, pinocchio::COLLISION,
                               *collisionModel);
    if (fs::exists(spec.srdf_path)) {
      collisionModel->addAllCollisionPairs();
      pinocchio::srdf::removeCollisionPairs(model, *collisionModel,
                                            spec.srdf_path, false);
    }
  }
}

// LOADERS FROM TOML FILE ====================

void loadModelFromToml(const std::string &tomlFile, const std::string &key,
                       pinocchio::Model &model, bool verbose) {
  robot_spec spec = loadErdRobotSpecFromToml(tomlFile, key, verbose);
  loadModelFromSpec(spec, model, verbose);
}

void loadModelsFromToml(const std::string &tomlFile, const std::string &key,
                        pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel,
                        bool verbose) {
  robot_spec spec = loadErdRobotSpecFromToml(tomlFile, key, verbose);
  loadModelsFromSpec(spec, model, visualModel, collisionModel, verbose);
}

} // namespace robot_descriptions
