# C API Reference

## Series Functions

### tablr_series_create

```c
TablrSeries* tablr_series_create(void* data, size_t size, TablrDType dtype);
```

Create a new series from array data.

**Parameters:**
- `data` - Pointer to array data
- `size` - Number of elements
- `dtype` - Data type

**Returns:** Pointer to new series or NULL on failure

### tablr_series_free

```c
void tablr_series_free(TablrSeries* series);
```

Free series memory.

### tablr_series_size

```c
size_t tablr_series_size(const TablrSeries* series);
```

Get the number of elements in the series.

## DataFrame Functions

### tablr_dataframe_create

```c
TablrDataFrame* tablr_dataframe_create(void);
```

Create an empty dataframe.

### tablr_dataframe_free

```c
void tablr_dataframe_free(TablrDataFrame* df);
```

Free dataframe memory.

### tablr_dataframe_add_column

```c
bool tablr_dataframe_add_column(TablrDataFrame* df, const char* name, TablrSeries* series);
```

Add a column to the dataframe.

### tablr_dataframe_get_column

```c
TablrSeries* tablr_dataframe_get_column(const TablrDataFrame* df, const char* name);
```

Get a column by name.

### tablr_dataframe_nrows

```c
size_t tablr_dataframe_nrows(const TablrDataFrame* df);
```

Get number of rows.

### tablr_dataframe_ncols

```c
size_t tablr_dataframe_ncols(const TablrDataFrame* df);
```

Get number of columns.

## I/O Functions

### tablr_read_csv

```c
TablrDataFrame* tablr_read_csv(const char* filename);
```

Read CSV file into dataframe.

### tablr_to_csv

```c
bool tablr_to_csv(const TablrDataFrame* df, const char* filename);
```

Write dataframe to CSV file.
