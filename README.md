<div align="center">

# Tablr

**Fastest and Simpler Data Manipulation Library for C/C++**

[![Release](https://img.shields.io/github/v/release/muhammad-fiaz/tablr)](https://github.com/muhammad-fiaz/tablr/releases)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![Commits](https://img.shields.io/github/commit-activity/m/muhammad-fiaz/tablr)](https://github.com/muhammad-fiaz/tablr/commits/main)
[![Issues](https://img.shields.io/github/issues/muhammad-fiaz/tablr)](https://github.com/muhammad-fiaz/tablr/issues)
[![PRs](https://img.shields.io/github/issues-pr/muhammad-fiaz/tablr)](https://github.com/muhammad-fiaz/tablr/pulls)
[![Stars](https://img.shields.io/github/stars/muhammad-fiaz/tablr)](https://github.com/muhammad-fiaz/tablr)
[![Tests](https://github.com/muhammad-fiaz/tablr/actions/workflows/test.yml/badge.svg)](https://github.com/muhammad-fiaz/tablr/actions/workflows/test.yml)
[![Release](https://github.com/muhammad-fiaz/tablr/actions/workflows/release.yml/badge.svg)](https://github.com/muhammad-fiaz/tablr/actions/workflows/release.yml)
[![Docs](https://github.com/muhammad-fiaz/tablr/actions/workflows/docs.yml/badge.svg)](https://github.com/muhammad-fiaz/tablr/actions/workflows/docs.yml)

[📚 Documentation](https://muhammad-fiaz.github.io/Tablr) • [🚀 Quick Start](#-quick-start) • [🤝 Contributing](#-contributing)

</div>

## 🌟 Features

- **High Performance**: Optimized for speed with SIMD and multi-threading support
- **Multi-Device Support**: Full acceleration for CPU, CUDA, XPU, NPU, and TPU
- **Simple API**: Clean, intuitive C and C++ interfaces
- **Comprehensive**: All essential data manipulation operations
- **Production Ready**: Thoroughly tested, documented, and battle-tested
- **Cross-Platform**: Works on Windows, Linux, and macOS
- **Zero Dependencies**: Core library has no external dependencies
- **Memory Efficient**: Smart memory management with minimal overhead
- **Modular Design**: Well-organized codebase with clear separation of concerns

## 📦 Installation

### Download Pre-built Binaries

Download the latest release for your platform from [GitHub Releases](https://github.com/muhammad-fiaz/tablr/releases):

- **Linux**: `tablr-linux-x64.tar.gz`
- **Windows**: `tablr-windows-x64.zip`
- **macOS**: `tablr-macos-x64.tar.gz`

Extract and copy to your system:

**Linux/macOS:**
```bash
tar -xzf tablr-linux-x64.tar.gz
sudo cp -r lib/* /usr/local/lib/
sudo cp -r include/* /usr/local/include/
```

**Windows:**
Extract the zip file and add the `lib` and `include` directories to your project paths.

### Using xmake (Recommended)

For xmake users, download `tablr-xmake-{version}.tar.gz` from releases:

```bash
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

### From Source

```bash
git clone https://github.com/muhammad-fiaz/tablr.git
cd tablr
xmake build
xmake install
```

## 🚀 Quick Start

### C API

```c
#include <tablr/tablr.h>

int main() {
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create series */
    int ages[] = {25, 30, 35, 40};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 4, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 4, TABLR_FLOAT32, TABLR_CPU);
    
    /* Add columns */
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    /* Print dataframe */
    tablr_dataframe_print(df);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    
    return 0;
}
```

### C++ API

```cpp
#include <tablr/tablr.hpp>

int main() {
    /* Read CSV */
    auto df = tablr::DataFrame::read_csv("data.csv");
    
    /* Filter rows */
    auto filtered = df.filter([](size_t row) {
        return row > 0;
    });
    
    /* Sort by column */
    auto sorted = df.sort("Age", true);
    
    /* Print results */
    sorted.print();
    
    return 0;
}
```

## 🎯 Core Operations

### DataFrame Creation
- `tablr_dataframe_create()` - Create empty dataframe
- `tablr_read_csv()` - Read from CSV file
- `tablr_dataframe_copy()` - Copy dataframe

### Series Creation
- `tablr_series_create()` - Create from array
- `tablr_series_zeros()` - Create filled with zeros
- `tablr_series_ones()` - Create filled with ones
- `tablr_series_arange()` - Create with range of values

### Data Selection
- `tablr_dataframe_head()` - Get first n rows
- `tablr_dataframe_tail()` - Get last n rows
- `tablr_dataframe_filter()` - Filter by condition
- `tablr_dataframe_select_rows()` - Select specific rows
- `tablr_dataframe_select_columns()` - Select specific columns

### Data Manipulation
- `tablr_dataframe_sort()` - Sort by column
- `tablr_dataframe_groupby()` - Group by column
- `tablr_dataframe_merge()` - Merge dataframes
- `tablr_dataframe_concat()` - Concatenate dataframes
- `tablr_dataframe_dropna()` - Drop missing values

### Aggregation
- `tablr_dataframe_describe()` - Descriptive statistics
- `tablr_dataframe_aggregate()` - Custom aggregation
- Sum, Mean, Min, Max, Count, Std, Var

### I/O Operations
- `tablr_read_csv()` - Read CSV file
- `tablr_to_csv()` - Write CSV file
- `tablr_dataframe_print()` - Print to console

## 🖥️ Multi-Device Support

Tablr supports multiple accelerator backends:

```c
/* CPU execution */
TablrSeries* s1 = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_CPU);

/* CUDA GPU */
TablrSeries* s2 = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_CUDA);

/* Intel XPU */
TablrSeries* s3 = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_XPU);

/* Neural Processing Unit */
TablrSeries* s4 = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_NPU);

/* Tensor Processing Unit */
TablrSeries* s5 = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_TPU);

/* Transfer between devices */
TablrSeries* s_gpu = tablr_series_to_device(s1, TABLR_CUDA);
```

## 📊 Performance

Tablr is designed for maximum performance:

- **SIMD Optimizations**: Vectorized operations for CPU
- **GPU Acceleration**: CUDA kernels for parallel computing
- **Memory Efficiency**: Minimal allocations and smart caching
- **Multi-threading**: Parallel execution for large datasets
- **Zero-Copy**: Efficient data transfer between devices

## 🧪 Testing

Run the test suite:

```bash
xmake build tests
xmake run tests
```

All tests must pass before release.

## 📖 Documentation

Full documentation is available at [https://muhammad-fiaz.github.io/Tablr/](https://muhammad-fiaz.github.io/Tablr/)

### Do's ✅

- Use appropriate data types for your use case
- Free dataframes and series when done to avoid memory leaks
- Check return values for NULL
- Use GPU for large-scale computations
- Profile your code for bottlenecks

### Don'ts ❌

- Don't mix data from different devices without transfer
- Don't modify series data directly
- Don't forget to synchronize after GPU operations
- Don't use debug builds in production
- Don't ignore compiler warnings

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 👤 Author

**Muhammad Fiaz**

- GitHub: [@muhammad-fiaz](https://github.com/muhammad-fiaz)
- Email: contact@muhammadfiaz.com

## 🙏 Acknowledgments

Special thanks to all contributors and the open-source community.

## 📮 Support

- 📧 Email: contact@muhammadfiaz.com
- 🐛 Issues: [GitHub Issues](https://github.com/muhammad-fiaz/tablr/issues)
- 💬 Discussions: [GitHub Discussions](https://github.com/muhammad-fiaz/tablr/discussions)

## 🐛 Bug Reports

Found a bug? Please [open an issue](https://github.com/muhammad-fiaz/tablr/issues) on GitHub.


<div align="center">

[![Star History Chart](https://api.star-history.com/svg?repos=muhammad-fiaz/Tensr&type=Date&bg=transparent)](https://github.com/muhammad-fiaz/Tensr/)

**⭐ Star the repository if you find Tensr useful!**

</div>
