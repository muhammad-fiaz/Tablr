# I/O Operations

## CSV Operations

### Read CSV

```c
TablrDataFrame* tablr_read_csv(const char* filename, char delimiter, bool has_header);
```

Read CSV file into dataframe with custom settings.

**Example:**
```c
/* Read with comma delimiter and header */
TablrDataFrame* df = tablr_read_csv("data.csv", ',', true);

/* Read with tab delimiter, no header */
TablrDataFrame* df2 = tablr_read_csv("data.tsv", '\t', false);
```

### Read CSV (Default)

```c
TablrDataFrame* tablr_read_csv_default(const char* filename);
```

Read CSV with default settings (comma delimiter, with header).

**Example:**
```c
TablrDataFrame* df = tablr_read_csv_default("data.csv");
```

### Write CSV

```c
bool tablr_to_csv(const TablrDataFrame* df, const char* filename, char delimiter, bool write_header);
```

Write dataframe to CSV file with custom settings.

**Example:**
```c
/* Write with comma delimiter and header */
tablr_to_csv(df, "output.csv", ',', true);

/* Write with semicolon delimiter, no header */
tablr_to_csv(df, "output.csv", ';', false);
```

### Write CSV (Default)

```c
bool tablr_to_csv_default(const TablrDataFrame* df, const char* filename);
```

Write CSV with default settings (comma delimiter, with header).

**Example:**
```c
tablr_to_csv_default(df, "output.csv");
```
