# Basic Usage Examples

## Creating a DataFrame

```c
#include <tablr/tablr.h>

int main(void) {
    /* Create empty dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create data */
    int ages[] = {25, 30, 35, 40, 45};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f, 90000.0f};
    
    /* Create series */
    TablrSeries* age_series = tablr_series_create(ages, 5, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 5, TABLR_FLOAT32, TABLR_CPU);
    
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

## Reading from CSV

```c
#include <tablr/tablr.h>

int main(void) {
    /* Read CSV file */
    TablrDataFrame* df = tablr_read_csv_default("employees.csv");
    
    if (df) {
        /* Print first 10 rows */
        TablrDataFrame* head = tablr_dataframe_head(df, 10);
        tablr_dataframe_print(head);
        
        /* Cleanup */
        tablr_dataframe_free(head);
        tablr_dataframe_free(df);
    }
    
    return 0;
}
```

## Filtering Data

```c
#include <tablr/tablr.h>

bool age_filter(size_t row, void* ctx) {
    TablrDataFrame* df = (TablrDataFrame*)ctx;
    TablrSeries* age_col = tablr_dataframe_get_column(df, "Age");
    int* ages = (int*)tablr_series_data(age_col);
    return ages[row] >= 30;  /* Keep rows where age >= 30 */
}

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("employees.csv");
    
    /* Filter rows */
    TablrDataFrame* filtered = tablr_dataframe_filter(df, age_filter, df);
    
    tablr_dataframe_print(filtered);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(filtered);
    
    return 0;
}
```
