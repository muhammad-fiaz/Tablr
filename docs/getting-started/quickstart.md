# Quick Start

## C API Example

```c
#include <tablr/tablr.h>
#include <stdio.h>

int main() {
    // Create dataframe
    TablrDataFrame* df = tablr_dataframe_create();
    
    // Create series
    int ages[] = {25, 30, 35, 40};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 4, TABLR_INT32);
    TablrSeries* salary_series = tablr_series_create(salaries, 4, TABLR_FLOAT32);
    
    // Add columns
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    // Print dataframe
    tablr_dataframe_print(df);
    
    // Cleanup
    tablr_dataframe_free(df);
    
    return 0;
}
```

## C++ API Example

```cpp
#include <tablr/tablr.hpp>

int main() {
    // Read CSV
    auto df = tablr::DataFrame::read_csv("data.csv");
    
    // Filter rows
    auto filtered = df.filter([](size_t row) {
        return row > 0;
    });
    
    // Sort by column
    auto sorted = df.sort("Age", true);
    
    // Print results
    sorted.print();
    
    return 0;
}
```

## Compiling

### With xmake

```bash
xmake build
```

### With gcc

```bash
gcc -o myapp myapp.c -ltablr -I/usr/local/include -L/usr/local/lib
```

### With g++

```bash
g++ -o myapp myapp.cpp -ltablr -I/usr/local/include -L/usr/local/lib
```
