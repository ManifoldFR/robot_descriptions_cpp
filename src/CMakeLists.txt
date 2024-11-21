find_package(pinocchio REQUIRED)
find_package(example-robot-data REQUIRED)
find_package(fmt REQUIRED)

set(ROBOT_TOML_DIR ${PROJECT_SOURCE_DIR}/assets)
set(PROJECT_USE_CMAKE_EXPORT True)

file(GLOB robot_SOURCES CONFIGURE_DEPENDS ${PROJECT_NAME}/*.cpp)

add_library(robot_descriptions_cpp SHARED ${robot_SOURCES})
target_include_directories(
  robot_descriptions_cpp
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(
  robot_descriptions_cpp
  PUBLIC pinocchio::pinocchio_parsers fmt::fmt
)
target_link_libraries(robot_descriptions_cpp PRIVATE toml11)
target_link_libraries(
  robot_descriptions_cpp
  PUBLIC example-robot-data::example-robot-data
)
target_compile_definitions(
  robot_descriptions_cpp
  PUBLIC ROBOT_TOML_DIR="${ROBOT_TOML_DIR}"
)

install(
  TARGETS robot_descriptions_cpp
  EXPORT ${PROJECT_NAME}
  INCLUDES DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
)

set(
  HEADER_FILES
  robot_descriptions_cpp/robot_load.hpp
  robot_descriptions_cpp/robot_spec.hpp
)
install(
  FILES ${HEADER_FILES}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ OWNER_WRITE
)
