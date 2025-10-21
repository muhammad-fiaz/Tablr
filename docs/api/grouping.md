# Grouping & Aggregation

## Group By

```c
TablrDataFrame* tablr_dataframe_groupby(const TablrDataFrame* df, const char* column);
```

Group dataframe by column values.

**Example:**
```c
TablrDataFrame* grouped = tablr_dataframe_groupby(df, "Department");
```

## Aggregate

```c
TablrDataFrame* tablr_dataframe_aggregate(const TablrDataFrame* df, const char* agg_column, TablrAggFunc func);
```

Apply aggregation function to grouped data.

**Aggregation Functions:**
- `TABLR_AGG_SUM` - Sum of values
- `TABLR_AGG_MEAN` - Mean/average
- `TABLR_AGG_MIN` - Minimum value
- `TABLR_AGG_MAX` - Maximum value
- `TABLR_AGG_COUNT` - Count of values
- `TABLR_AGG_STD` - Standard deviation
- `TABLR_AGG_VAR` - Variance

**Example:**
```c
TablrDataFrame* grouped = tablr_dataframe_groupby(df, "Department");
TablrDataFrame* avg_salary = tablr_dataframe_aggregate(grouped, "Salary", TABLR_AGG_MEAN);
```

## Describe

```c
TablrDataFrame* tablr_dataframe_describe(const TablrDataFrame* df);
```

Get descriptive statistics for all numeric columns.

**Example:**
```c
TablrDataFrame* stats = tablr_dataframe_describe(df);
tablr_dataframe_print(stats);
```

Returns statistics including:
- count
- mean
- std (standard deviation)
- min
- max
