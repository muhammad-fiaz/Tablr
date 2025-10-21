# Filtering & Selection

## Filter by Condition

```c
TablrDataFrame* tablr_dataframe_filter(const TablrDataFrame* df, TablrFilterFunc predicate, void* ctx);
```

Filter rows based on a predicate function.

**Example:**
```c
bool filter_func(size_t row, void* ctx) {
    return row % 2 == 0;  /* Keep even rows */
}

TablrDataFrame* filtered = tablr_dataframe_filter(df, filter_func, NULL);
```

## Select Rows

```c
TablrDataFrame* tablr_dataframe_select_rows(const TablrDataFrame* df, const size_t* indices, size_t count);
```

Select specific rows by index.

**Example:**
```c
size_t indices[] = {0, 2, 4, 6};
TablrDataFrame* selected = tablr_dataframe_select_rows(df, indices, 4);
```

## Select Columns

```c
TablrDataFrame* tablr_dataframe_select_columns(const TablrDataFrame* df, const char** columns, size_t count);
```

Select specific columns by name.

**Example:**
```c
const char* cols[] = {"Age", "Salary"};
TablrDataFrame* selected = tablr_dataframe_select_columns(df, cols, 2);
```

## Drop Missing Values

```c
TablrDataFrame* tablr_dataframe_dropna(const TablrDataFrame* df);
```

Remove rows with missing values.

**Example:**
```c
TablrDataFrame* clean = tablr_dataframe_dropna(df);
```
