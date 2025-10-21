# C++ API Reference

## DataFrame Class

### Constructor

```cpp
DataFrame();
```

Create an empty dataframe.

### read_csv

```cpp
static DataFrame read_csv(const std::string& filename);
```

Read CSV file into dataframe.

### to_csv

```cpp
void to_csv(const std::string& filename) const;
```

Write dataframe to CSV file.

### add_column

```cpp
void add_column(const std::string& name, const Series& series);
```

Add a column to the dataframe.

### get_column

```cpp
Series get_column(const std::string& name) const;
```

Get a column by name.

### nrows

```cpp
size_t nrows() const;
```

Get number of rows.

### ncols

```cpp
size_t ncols() const;
```

Get number of columns.

### filter

```cpp
DataFrame filter(std::function<bool(size_t)> predicate) const;
```

Filter rows based on predicate function.

### groupby

```cpp
DataFrame groupby(const std::string& column) const;
```

Group dataframe by column.

### sort

```cpp
DataFrame sort(const std::string& column, bool ascending = true) const;
```

Sort dataframe by column.

### merge

```cpp
DataFrame merge(const DataFrame& other, const std::string& on) const;
```

Merge two dataframes on a column.

### describe

```cpp
DataFrame describe() const;
```

Get descriptive statistics.

### print

```cpp
void print() const;
```

Print dataframe to console.
