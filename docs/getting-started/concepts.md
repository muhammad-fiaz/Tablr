# Basic Concepts

## DataFrame

A DataFrame is a 2-dimensional labeled data structure with columns of potentially different types. It's similar to a spreadsheet or SQL table.

## Series

A Series is a one-dimensional array with labeled data. Each column in a DataFrame is a Series.

## Data Types

Tablr supports the following data types:

- `TABLR_INT32` - 32-bit integer
- `TABLR_INT64` - 64-bit integer
- `TABLR_FLOAT32` - 32-bit floating point
- `TABLR_FLOAT64` - 64-bit floating point
- `TABLR_STRING` - String data

## Device Support

Tablr supports multiple compute devices:

- `TABLR_CPU` - Standard CPU execution
- `TABLR_CUDA` - NVIDIA GPU acceleration
- `TABLR_XPU` - Intel XPU support
- `TABLR_NPU` - Neural Processing Unit
- `TABLR_TPU` - Tensor Processing Unit

## Memory Management

Always free DataFrames and Series when done:

```c
tablr_dataframe_free(df);
tablr_series_free(series);
```

In C++, memory is managed automatically through destructors.
