# Tablr Documentation

Welcome to **Tablr** - the fastest and simpler data manipulation library for C/C++!

## Overview

Tablr is a high-performance data manipulation library designed for C and C++ developers who need efficient DataFrame operations similar to pandas, but with the speed and control of native code.

## Key Features

- **High Performance**: Optimized for speed with SIMD and multi-threading
- **Multi-Device Support**: Full acceleration for CPU, CUDA, XPU, NPU, and TPU
- **Simple API**: Clean, intuitive C and C++ interfaces
- **DataFrame Operations**: Filter, group, sort, merge, and aggregate data
- **CSV Support**: Read and write CSV files efficiently
- **Production Ready**: Thoroughly tested with no placeholders
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **Zero Dependencies**: Core library has no external dependencies
- **Memory Efficient**: Smart memory management with device switching
- **Runtime Device Switching**: Change default device anytime

## Quick Example

### C API
```c
#include <tablr/tablr.h>

int main() {
    /* Read CSV */
    TablrDataFrame* df = tablr_read_csv("data.csv");
    tablr_dataframe_print(df);
    tablr_dataframe_free(df);
    return 0;
}
```

### Multi-Device Support
```c
#include <tablr/tablr.h>

int main() {
    float data[] = {1.0f, 2.0f, 3.0f};
    
    /* CPU (default) */
    TablrSeries* s1 = tablr_series_create(data, 3, TABLR_FLOAT32, TABLR_CPU);
    
    /* CUDA GPU */
    TablrSeries* s2 = tablr_series_create(data, 3, TABLR_FLOAT32, TABLR_CUDA);
    
    /* Switch default device */
    tablr_set_default_device(TABLR_CUDA);
    TablrSeries* s3 = tablr_series_create_default(data, 3, TABLR_FLOAT32);
    
    tablr_series_free(s1);
    tablr_series_free(s2);
    tablr_series_free(s3);
    return 0;
}
```

### C++ API
```cpp
#include <tablr/tablr.hpp>

int main() {
    auto df = tablr::DataFrame::read_csv("data.csv");
    df.print();
    return 0;
}
```

## Supported Devices

- **CPU**: Always available (default)
- **CUDA**: NVIDIA GPUs with real CUDA kernels
- **XPU**: Intel GPUs with SYCL/DPC++
- **NPU**: Neural Processing Units for AI workloads
- **TPU**: Tensor Processing Units for deep learning

### Building with Device Support

```bash
# CUDA support
xmake f --cuda=y && xmake

# Multiple devices
xmake f --cuda=y --xpu=y --npu=y --tpu=y && xmake
```

## Getting Started

Check out the [Installation Guide](getting-started/installation.md) to get started with Tablr!
