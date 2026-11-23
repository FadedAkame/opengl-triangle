# OpenGL Triangle
Just as a template/reference for a OpenGL triangle with RAII wrappers & abstractions

## Requirements
- **OS:** Linux
- **Compiler:** GCC w/ C++23 support
- **Graphics:** OpenGL-compatible hardware
- **Build System:** CMake + Ninja

> [!NOTE]
> GLFW and GLAD are already included as static libraries, no install required.

## Config & Building
Configure CMake
An optional flag is ```-DENABLE_SANITIZERS=On```
```
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```
Build & run project
```
./run.sh (args)
```
