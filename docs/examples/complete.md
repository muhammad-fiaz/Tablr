# Complete Examples - C and C++

## C API Examples

### Basic DataFrame Creation

```c
#include <tablr/tablr.h>

int main(void) {
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create data */
    int ages[] = {25, 30, 35, 40};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f};
    
    /* Create series */
    TablrSeries* age_series = tablr_series_create(ages, 4, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 4, TABLR_FLOAT32, TABLR_CPU);
    
    /* Add columns */
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    /* Print */
    tablr_dataframe_print(df);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    
    return 0;
}
```

### Filtering Data

```c
#include <tablr/tablr.h>

bool age_filter(size_t row, void* ctx) {
    TablrDataFrame* df = (TablrDataFrame*)ctx;
    TablrSeries* age_col = tablr_dataframe_get_column(df, "Age");
    int* ages = (int*)tablr_series_data(age_col);
    return ages[row] >= 30;
}

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("data.csv");
    
    /* Filter rows where age >= 30 */
    TablrDataFrame* filtered = tablr_dataframe_filter(df, age_filter, df);
    tablr_dataframe_print(filtered);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(filtered);
    
    return 0;
}
```

### Sorting Operations

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("data.csv");
    
    /* Sort by age ascending */
    TablrDataFrame* sorted = tablr_dataframe_sort(df, "Age", true);
    tablr_dataframe_print(sorted);
    
    /* Sort by salary descending */
    TablrDataFrame* sorted_desc = tablr_dataframe_sort(df, "Salary", false);
    tablr_dataframe_print(sorted_desc);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(sorted);
    tablr_dataframe_free(sorted_desc);
    
    return 0;
}
```

### Aggregation

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("data.csv");
    
    /* Get descriptive statistics */
    TablrDataFrame* stats = tablr_dataframe_describe(df);
    tablr_dataframe_print(stats);
    
    /* Calculate mean */
    TablrDataFrame* mean = tablr_dataframe_aggregate(df, "Salary", TABLR_AGG_MEAN);
    tablr_dataframe_print(mean);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(stats);
    tablr_dataframe_free(mean);
    
    return 0;
}
```

### Multi-Device Support

```c
#include <tablr/tablr.h>

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    
    /* Create on CPU */
    TablrSeries* cpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_CPU);
    
    /* Create on CUDA GPU */
    TablrSeries* cuda_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_CUDA);
    
    /* Create on Intel XPU */
    TablrSeries* xpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_XPU);
    
    /* Create on NPU */
    TablrSeries* npu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_NPU);
    
    /* Create on TPU */
    TablrSeries* tpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_TPU);
    
    /* Transfer between devices */
    TablrSeries* transferred = tablr_series_to_device(cpu_series, TABLR_CUDA);
    
    /* Cleanup */
    tablr_series_free(cpu_series);
    tablr_series_free(cuda_series);
    tablr_series_free(xpu_series);
    tablr_series_free(npu_series);
    tablr_series_free(tpu_series);
    tablr_series_free(transferred);
    
    return 0;
}
```

## C++ API Examples

### Basic DataFrame Creation

```cpp
#include <tablr/tablr.hpp>
#include <vector>

int main() {
    /* Create dataframe */
    tablr::DataFrame df;
    
    /* Create data */
    std::vector<int> ages = {25, 30, 35, 40};
    std::vector<float> salaries = {50000.0f, 60000.0f, 70000.0f, 80000.0f};
    
    /* Create series */
    tablr::Series age_series(ages);
    tablr::Series salary_series(salaries);
    
    /* Add columns */
    df.add_column("Age", age_series);
    df.add_column("Salary", salary_series);
    
    /* Print */
    df.print();
    
    return 0;
}
```

### Reading and Writing CSV

```cpp
#include <tablr/tablr.hpp>

int main() {
    /* Read CSV */
    auto df = tablr::DataFrame::read_csv("data.csv");
    
    /* Process data */
    auto filtered = df.filter([](size_t row) {
        return row > 0;
    });
    
    /* Sort */
    auto sorted = filtered.sort("Age", true);
    
    /* Write to CSV */
    sorted.to_csv("output.csv");
    
    return 0;
}
```

### Filtering with Lambda

```cpp
#include <tablr/tablr.hpp>

int main() {
    auto df = tablr::DataFrame::read_csv("data.csv");
    
    /* Filter with lambda */
    auto filtered = df.filter([](size_t row) {
        return row % 2 == 0;  // Keep even rows
    });
    
    filtered.print();
    
    return 0;
}
```

### Grouping and Aggregation

```cpp
#include <tablr/tablr.hpp>

int main() {
    auto df = tablr::DataFrame::read_csv("sales.csv");
    
    /* Group by region */
    auto grouped = df.groupby("Region");
    
    /* Get descriptive statistics */
    auto stats = df.describe();
    stats.print();
    
    return 0;
}
```

### Merging DataFrames

```cpp
#include <tablr/tablr.hpp>

int main() {
    auto employees = tablr::DataFrame::read_csv("employees.csv");
    auto departments = tablr::DataFrame::read_csv("departments.csv");
    
    /* Merge on department ID */
    auto merged = employees.merge(departments, "DeptID");
    merged.print();
    
    return 0;
}
```

## Compilation

### C Examples

```bash
# With xmake
xmake build

# With gcc
gcc -o myapp myapp.c -ltablr -I/usr/local/include -L/usr/local/lib

# With MSVC
cl myapp.c /I"C:\path\to\include" /link tablr.lib
```

### C++ Examples

```bash
# With xmake
xmake build

# With g++
g++ -o myapp myapp.cpp -ltablr -I/usr/local/include -L/usr/local/lib -std=c++17

# With MSVC
cl myapp.cpp /std:c++17 /I"C:\path\to\include" /link tablr.lib
```
