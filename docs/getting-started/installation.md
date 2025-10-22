# Installation

## Download Pre-built Binaries

Download the latest release for your platform from [GitHub Releases](https://github.com/muhammad-fiaz/tablr/releases):

- **Linux**: `tablr-linux-x64.tar.gz`
- **Windows**: `tablr-windows-x64.zip`
- **macOS**: `tablr-macos-x64.tar.gz`

### Linux/macOS

```bash
tar -xzf tablr-linux-x64.tar.gz
sudo cp -r lib/* /usr/local/lib/
sudo cp -r include/* /usr/local/include/
```

### Windows

Extract the zip file and add the `lib` and `include` directories to your project paths.

## Using xmake (Recommended)

```bash
wget https://github.com/muhammad-fiaz/tablr/releases/download/v0.1.0/tablr-xmake-0.1.0.tar.gz
tar -xzf tablr-xmake-0.1.0.tar.gz
cd tablr-xmake-0.1.0
xmake install
```

Or add to your `xmake.lua`:

```lua
add_includedirs("/path/to/tablr/include")
add_linkdirs("/path/to/tablr/lib")
add_links("tablr")
```

## Using Conan

```bash
conan install tablr/0.1.0@
```

## Using vcpkg

```bash
vcpkg install tablr
```

## From Source

### Basic Build

```bash
git clone https://github.com/muhammad-fiaz/tablr.git
cd tablr
xmake build
xmake install
```

### Build with Accelerator Support

#### CUDA (NVIDIA GPUs)

```bash
xmake f --cuda=y
xmake build
xmake install
```

Requires: NVIDIA GPU with CUDA Toolkit installed

#### Intel XPU

```bash
xmake f --xpu=y
xmake build
xmake install
```

Requires: Intel GPU with SYCL/DPC++ support

#### NPU (Neural Processing Units)

```bash
xmake f --npu=y
xmake build
xmake install
```

Requires: NPU hardware (Qualcomm, MediaTek, etc.)

#### TPU (Tensor Processing Units)

```bash
xmake f --tpu=y
xmake build
xmake install
```

Requires: TPU hardware (Google TPU, similar accelerators)

#### Multiple Accelerators

```bash
xmake f --cuda=y --xpu=y --npu=y --tpu=y
xmake build
xmake install
```

### CMake Build

```bash
mkdir build && cd build
cmake -DTABLR_CUDA_SUPPORT=ON -DTABLR_XPU_SUPPORT=ON ..
make
make install
```

## Verifying Installation

```bash
# Run tests
xmake run tests

# Check device support
xmake run example_device_switching
```
