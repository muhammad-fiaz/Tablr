# DataFrame Creation

## Creating DataFrames

### tablr_dataframe_create

```c
TablrDataFrame* tablr_dataframe_create(void);
```

Create an empty dataframe.

**Example:**
```c
TablrDataFrame* df = tablr_dataframe_create();
```

### tablr_read_csv

```c
TablrDataFrame* tablr_read_csv(const char* filename, char delimiter, bool has_header);
```

Read CSV file into dataframe.

**Example:**
```c
TablrDataFrame* df = tablr_read_csv("data.csv", ',', true);
```

## Creating Series

### tablr_series_create

```c
TablrSeries* tablr_series_create(const void* data, size_t size, TablrDType dtype, TablrDevice device);
```

Create series from array data.

**Example:**
```c
int data[] = {1, 2, 3, 4, 5};
TablrSeries* s = tablr_series_create(data, 5, TABLR_INT32, TABLR_CPU);
```

### tablr_series_zeros

```c
TablrSeries* tablr_series_zeros(size_t size, TablrDType dtype, TablrDevice device);
```

Create series filled with zeros.

**Example:**
```c
TablrSeries* s = tablr_series_zeros(100, TABLR_FLOAT64, TABLR_CPU);
```

### tablr_series_ones

```c
TablrSeries* tablr_series_ones(size_t size, TablrDType dtype, TablrDevice device);
```

Create series filled with ones.

**Example:**
```c
TablrSeries* s = tablr_series_ones(50, TABLR_FLOAT32, TABLR_CPU);
```

### tablr_series_arange

```c
TablrSeries* tablr_series_arange(double start, double stop, double step, TablrDevice device);
```

Create series with range of values.

**Example:**
```c
TablrSeries* s = tablr_series_arange(0.0, 10.0, 0.5, TABLR_CPU);
```
