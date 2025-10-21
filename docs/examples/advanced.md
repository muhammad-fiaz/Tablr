# Advanced Usage Examples

## Sorting and Grouping

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("sales.csv");
    
    /* Sort by sales amount descending */
    TablrDataFrame* sorted = tablr_dataframe_sort(df, "Amount", false);
    
    /* Group by region */
    TablrDataFrame* grouped = tablr_dataframe_groupby(sorted, "Region");
    
    /* Calculate mean sales per region */
    TablrDataFrame* avg_sales = tablr_dataframe_aggregate(grouped, "Amount", TABLR_AGG_MEAN);
    
    tablr_dataframe_print(avg_sales);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(sorted);
    tablr_dataframe_free(grouped);
    tablr_dataframe_free(avg_sales);
    
    return 0;
}
```

## Merging DataFrames

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* employees = tablr_read_csv_default("employees.csv");
    TablrDataFrame* departments = tablr_read_csv_default("departments.csv");
    
    /* Merge on department ID */
    TablrDataFrame* merged = tablr_dataframe_merge(
        employees, departments, "DeptID", TABLR_JOIN_INNER
    );
    
    tablr_dataframe_print(merged);
    
    tablr_dataframe_free(employees);
    tablr_dataframe_free(departments);
    tablr_dataframe_free(merged);
    
    return 0;
}
```

## Statistical Analysis

```c
#include <tablr/tablr.h>

int main(void) {
    TablrDataFrame* df = tablr_read_csv_default("data.csv");
    
    /* Get descriptive statistics */
    TablrDataFrame* stats = tablr_dataframe_describe(df);
    
    printf("Statistical Summary:\n");
    tablr_dataframe_print(stats);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(stats);
    
    return 0;
}
```
