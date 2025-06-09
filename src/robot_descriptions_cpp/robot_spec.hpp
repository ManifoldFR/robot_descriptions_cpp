#pragma once

#include <pinocchio/multibody/geometry.hpp>
#include <pinocchio/multibody/model.hpp>
#include <string>

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

/// \brief Load a single model from robot_spec.
void loadModelFromSpec(const robot_spec &spec, pinocchio::Model &model,
                       bool verbose = false);

/// \copybrief loadModelFromSpec().
///
/// This version allocates and returns a model.
inline pinocchio::Model loadModelFromSpec(const robot_spec &spec,
                                          bool verbose = false) {
  pinocchio::Model model;
  loadModelFromSpec(spec, model, verbose);
  return model;
}

void loadGeomFromSpec(const robot_spec &spec, const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type);

inline pinocchio::GeometryModel loadGeomFromSpec(const robot_spec &spec,
                                                 const pinocchio::Model &model,
                                                 pinocchio::GeometryType type) {
  pinocchio::GeometryModel geomModel;
  loadGeomFromSpec(spec, model, geomModel, type);
  return geomModel;
}

/// \param spec Robot description
/// \param model Pinocchio model to load into.
/// \param visualModel If not NULL, then Pinocchio geometry model for visuals.
/// \param collisionModel If not NULL, then Pinocchio geometry model for
/// \param verbose Passed to the loaders.
/// collisions.
void loadModelsFromSpec(const robot_spec &spec, pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel,
                        bool verbose = false);

/** LOAD MODEL FROM TOML FILE **/

void loadModelFromToml(const std::string &filename, const std::string &key,
                       pinocchio::Model &model, bool verbose = false);

void loadGeomFromToml(const std::string &filename, const std::string &key,
                      const pinocchio::Model &model,
                      pinocchio::GeometryModel &geomModel,
                      pinocchio::GeometryType type);

inline pinocchio::Model loadModelFromToml(const std::string &filename,
                                          const std::string &key,
                                          bool verbose = false) {
  pinocchio::Model model;
  loadModelFromToml(filename, key, model, verbose);
  return model;
}

void loadModelsFromToml(const std::string &filename, const std::string &key,
                        pinocchio::Model &model,
                        pinocchio::GeometryModel *visualModel,
                        pinocchio::GeometryModel *collisionModel,
                        bool verbose = false);

} // namespace robot_descriptions
