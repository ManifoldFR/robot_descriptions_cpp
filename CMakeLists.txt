cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME robot_descriptions_cpp)
set(PROJECT_URL "https://github.com/ManifoldFR/${PROJECT_NAME}.git")
set(PROJECT_DESCRIPTION "Robot descriptions in C++.")
set(PROJECT_CUSTOM_HEADER_EXTENSION "hpp")
set(PROJECT_CUSTOM_HEADER_DIR ${PROJECT_NAME})
set(PROJECT_GENERATED_HEADERS_SKIP_WARNING True)
set(PROJECT_GENERATED_HEADERS_SKIP_DEPRECATED True)

set(CMAKE_DISABLE_WERROR True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROJECT_USE_CMAKE_EXPORT True)

include(cmake/base.cmake)
COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
project(${PROJECT_NAME} ${PROJECT_ARGS})
set(CMAKE_VERBOSE_MAKEFILE False)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo"
  )
endif()

add_subdirectory(third-party/toml11)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(src)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})
