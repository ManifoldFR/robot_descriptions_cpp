#include <pinocchio/parsers/urdf.hpp>

namespace pinocchio {
namespace urdf {
template Model &
buildModel<double, context::Options>(const std::string &filename, Model &model,
                                     const bool verbose);
} // namespace urdf
} // namespace pinocchio
