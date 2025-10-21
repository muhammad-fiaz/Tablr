# Tablr Documentation

Welcome to **Tablr** - the fastest and simpler data manipulation library for C/C++!

## Overview

Tablr is a high-performance data manipulation library designed for C and C++ developers who need efficient DataFrame operations similar to pandas, but with the speed and control of native code.

## Key Features

- **High Performance**: Optimized for speed with minimal overhead
- **Simple API**: Clean, intuitive C and C++ interfaces
- **DataFrame Operations**: Filter, group, sort, merge, and aggregate data
- **CSV Support**: Read and write CSV files efficiently
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **Zero Dependencies**: Core library has no external dependencies
- **Memory Efficient**: Smart memory management

## Quick Example

### C API
```c
#include <tablr/tablr.h>

int main() {
    TablrDataFrame* df = tablr_read_csv("data.csv");
    tablr_dataframe_print(df);
    tablr_dataframe_free(df);
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

## Getting Started

Check out the [Installation Guide](getting-started/installation.md) to get started with Tablr!
