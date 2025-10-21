# Merging & Joining

## Merge DataFrames

```c
TablrDataFrame* tablr_dataframe_merge(const TablrDataFrame* left, const TablrDataFrame* right, 
                                       const char* on, TablrJoinType join_type);
```

Merge two dataframes on a common column.

**Join Types:**
- `TABLR_JOIN_INNER` - Inner join (intersection)
- `TABLR_JOIN_LEFT` - Left outer join
- `TABLR_JOIN_RIGHT` - Right outer join
- `TABLR_JOIN_OUTER` - Full outer join (union)

**Example:**
```c
TablrDataFrame* merged = tablr_dataframe_merge(df1, df2, "ID", TABLR_JOIN_INNER);
```

## Concatenate DataFrames

```c
TablrDataFrame* tablr_dataframe_concat(const TablrDataFrame** dfs, size_t count);
```

Concatenate multiple dataframes vertically.

**Example:**
```c
TablrDataFrame* dfs[] = {df1, df2, df3};
TablrDataFrame* combined = tablr_dataframe_concat(dfs, 3);
```
