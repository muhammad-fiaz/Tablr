# Data Operations

## Basic Operations

### Adding Columns

```c
bool tablr_dataframe_add_column(TablrDataFrame* df, const char* name, TablrSeries* series);
```

Add a column to the dataframe.

**Example:**
```c
int ages[] = {25, 30, 35};
TablrSeries* s = tablr_series_create(ages, 3, TABLR_INT32, TABLR_CPU);
tablr_dataframe_add_column(df, "Age", s);
```

### Getting Columns

```c
TablrSeries* tablr_dataframe_get_column(const TablrDataFrame* df, const char* name);
```

Get a column by name.

**Example:**
```c
TablrSeries* age_col = tablr_dataframe_get_column(df, "Age");
```

### Removing Columns

```c
bool tablr_dataframe_remove_column(TablrDataFrame* df, const char* name);
```

Remove a column from the dataframe.

**Example:**
```c
tablr_dataframe_remove_column(df, "Age");
```

## DataFrame Information

### Row and Column Counts

```c
size_t tablr_dataframe_nrows(const TablrDataFrame* df);
size_t tablr_dataframe_ncols(const TablrDataFrame* df);
```

Get the number of rows and columns.

**Example:**
```c
printf("Rows: %zu, Columns: %zu\n", 
       tablr_dataframe_nrows(df), 
       tablr_dataframe_ncols(df));
```

### Column Names

```c
char** tablr_dataframe_columns(const TablrDataFrame* df, size_t* count);
```

Get all column names.

**Example:**
```c
size_t count;
char** names = tablr_dataframe_columns(df, &count);
for (size_t i = 0; i < count; i++) {
    printf("%s\n", names[i]);
    free(names[i]);
}
free(names);
```

## Viewing Data

### Head and Tail

```c
TablrDataFrame* tablr_dataframe_head(const TablrDataFrame* df, size_t n);
TablrDataFrame* tablr_dataframe_tail(const TablrDataFrame* df, size_t n);
```

Get first or last n rows.

**Example:**
```c
TablrDataFrame* first_5 = tablr_dataframe_head(df, 5);
TablrDataFrame* last_5 = tablr_dataframe_tail(df, 5);
```

### Printing

```c
void tablr_dataframe_print(const TablrDataFrame* df);
```

Print dataframe to console.

**Example:**
```c
tablr_dataframe_print(df);
```
