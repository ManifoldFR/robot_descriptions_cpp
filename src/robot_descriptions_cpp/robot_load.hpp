#pragma once

#include <pinocchio/multibody/geometry.hpp>
#include <pinocchio/multibody/model.hpp>

namespace robot_descriptions {
/** LOAD MODEL FROM SPEC STRUCT **/

// fwd decl
struct robot_spec;

void loadModelFromSpec(const robot_spec &spec, pinocchio::Model &model,
                       bool verbose = false);

void loadGeomFromSpec(const robot_spec &spec, const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type);

inline pinocchio::Model loadModelFromSpec(const robot_spec &spec,
                                          bool verbose = false) {
  pinocchio::Model model;
  loadModelFromSpec(spec, model, verbose);
  return model;
}

inline pinocchio::GeometryModel loadGeomFromSpec(const robot_spec &spec,
                                                 const pinocchio::Model &model,
                                                 pinocchio::GeometryType type) {
  pinocchio::GeometryModel geomModel;
  loadGeomFromSpec(spec, model, geomModel, type);
  return geomModel;
}

inline void loadModelsFromSpec(const robot_spec &spec, pinocchio::Model &model,
                               pinocchio::GeometryModel *visualModel,
                               pinocchio::GeometryModel *collisionModel) {
  loadModelFromSpec(spec, model, false);
  if (visualModel)
    loadGeomFromSpec(spec, model, *visualModel, pinocchio::VISUAL);
  if (collisionModel)
    loadGeomFromSpec(spec, model, *collisionModel, pinocchio::COLLISION);
}

/** LOAD MODEL FROM TOML FILE **/

void loadModelFromToml(const std::string &tomlFile, const std::string &key,
                       pinocchio::Model &model, bool verbose = false);

void loadGeomFromToml(const std::string &tomlFile, const std::string &key,
                      const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type);

inline pinocchio::Model loadModelFromToml(const std::string &tomlFile,
                                          const std::string &key,
                                          bool verbose = false) {
  pinocchio::Model model;
  loadModelFromToml(tomlFile, key, model, verbose);
  return model;
}

void loadModelsFromToml(const std::string &tomlFile, const std::string &key,
                        pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel);
} // namespace robot_descriptions
