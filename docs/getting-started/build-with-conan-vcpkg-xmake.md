# Building Tablr with Conan, vcpkg, and xmake

This guide shows three ways to build Tablr: using Conan (C/C++ package manager), using vcpkg (Windows-centric package manager), and using xmake (primary project build tool). It includes PowerShell commands for Windows.

## 1) Build with Conan (recommended for CMake-based builds)

Prerequisites:

- Conan installed (https://conan.io)
- CMake installed
- A C++17 compiler (MSVC, GCC, or Clang)

From project root:

```powershell
# Create a build directory and install Conan dependencies
conan install . --output-folder=build --build=missing

# Generate CMake files and build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# (Optional) Run CTest if tests are configured
cmake --build build --target test
```

Troubleshooting:

- If `conan` is not found, install it via pip:

```powershell
python -m pip install --upgrade conan
```

- For profile and settings, use `conan profile` commands to configure compilers and options.

## 2) Build with vcpkg (Windows-focused)

Prerequisites:

- vcpkg (https://github.com/microsoft/vcpkg)
- CMake
- A C++17 compiler (Visual Studio recommended)

From project root:

```powershell
# Bootstrap vcpkg (first time only)
.vcpkg\bootstrap-vcpkg.bat

# Install manifest dependencies
vcpkg install --triplet x64-windows

# Integrate with CMake (optional)
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=$PWD\vcpkg\scripts\buildsystems\vcpkg.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Note: Ensure `vcpkg.json` lists required dependencies. The repository contains `vcpkg.json` which can be extended with dependencies such as `fmt`, `doctest`, etc.

## 3) Build and test with xmake (primary developer workflow)

Prerequisites:

- xmake installed (https://xmake.io)
- A C/C++ compiler

Commands (PowerShell):

```powershell
# Build library and all targets
xmake build

# Run tests
xmake run tests

# Run an example
xmake run example_basic
```

xmake automatically compiles sources under `src/` and links tests and examples. Use `xmake f -m release` to set release mode.

## CI suggestion

If you don't have Conan or vcpkg locally, use GitHub Actions to run builds in CI. See `.github/workflows/ci-conan-vcpkg-xmake.yml` in the repository for an example workflow that installs Conan and vcpkg inside the runner and builds the project.

---

If you want, I can now create the GitHub Actions workflow file that runs: `conan install`, `cmake` build, `vcpkg` bootstrap & install, and `xmake` build + tests on Windows/Linux/macOS runners.