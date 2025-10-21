# Sorting & Ranking

## Sort by Column

```c
TablrDataFrame* tablr_dataframe_sort(const TablrDataFrame* df, const char* column, bool ascending);
```

Sort dataframe by a single column.

**Example:**
```c
/* Sort by Age ascending */
TablrDataFrame* sorted = tablr_dataframe_sort(df, "Age", true);

/* Sort by Salary descending */
TablrDataFrame* sorted_desc = tablr_dataframe_sort(df, "Salary", false);
```

## Sort by Multiple Columns

```c
TablrDataFrame* tablr_dataframe_sort_multi(const TablrDataFrame* df, const char** columns, 
                                            const bool* ascending, size_t count);
```

Sort by multiple columns with different orders.

**Example:**
```c
const char* cols[] = {"Department", "Salary"};
bool asc[] = {true, false};
TablrDataFrame* sorted = tablr_dataframe_sort_multi(df, cols, asc, 2);
```
