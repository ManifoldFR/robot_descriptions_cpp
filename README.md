# robot_descriptions_cpp [name temporary]

## Rationale

This is a library of robot description files (written in TOML) to use with the models and data provided [example-robot-data](https://github.com/gepetto/example-robot-data/).

These files contain the metadata provided by `example-robot-data`'s own [`RobotLoader` subclasses](https://github.com/Gepetto/example-robot-data/blob/master/python/example_robot_data/robots_loader.py), which are just containers for metadata (paths, URDF file name, existence of SRDF files...).

This metadata is used by the base class to build a Pinocchio `RobotWrapper` (a class only existing in Pinocchio's Python bindings) containing the Pinocchio `Model`, and both the visual and collision `GeometryModel` objects.

This library also contains functions and structs which replicate the functionality of the `example_robot_data.RobotLoader` and `pinocchio.RobotWrapper` classes.

## Installation

### Dependencies

* [example-robot-data](https://github.com/gepetto/example-robot-data/)
* [pinocchio](https://github.com/stack-of-tasks/pinocchio#citing-pinocchio)
* [googletest](https://github.com/google/googletest)

### Steps

Just follow the following steps to clone the repository and contained submodule dependencies, create a build directory, build the library and install it:

```bash
git clone https://github.com/ManifoldFR/robot_descriptions_cpp --recursive
cmake -DCMAKE_INSTALL_PREFIX=your/install/prefix -S . -B build/ && cd build/
cmake --build . -jNCPUS --target install
```
