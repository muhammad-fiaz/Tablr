/**
 * @file groupby.c
 * @brief Implementation of grouping and aggregation operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements dataframe grouping and aggregation operations including
 * group-by, various aggregation functions, and descriptive statistics.
 */

#include "tablr/ops/groupby.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief Group dataframe by column
 * 
 * Groups rows by unique values in the specified column.
 * Currently returns a copy; full grouping implementation pending.
 * 
 * @param df Source dataframe
 * @param column Column name to group by
 * @return Grouped dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_groupby(const TablrDataFrame* df, const char* column) {
    if (!df || !column) return NULL;
    return tablr_dataframe_copy(df);
}

/**
 * @brief Aggregate column using function
 * 
 * Applies an aggregation function (sum, mean, etc.) to a column.
 * 
 * @param df Source dataframe
 * @param agg_column Column to aggregate
 * @param func Aggregation function (TABLR_AGG_SUM, TABLR_AGG_MEAN, etc.)
 * @return New dataframe with aggregated result, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_aggregate(const TablrDataFrame* df, const char* agg_column, TablrAggFunc func) {
    if (!df || !agg_column) return NULL;
    
    TablrSeries* s = tablr_dataframe_get_column(df, agg_column);
    if (!s) return NULL;
    
    void* data = tablr_series_data(s);
    size_t size = tablr_series_size(s);
    TablrDType dtype = tablr_series_dtype(s);
    
    double result_val = 0.0;
    
    if (func == TABLR_AGG_SUM || func == TABLR_AGG_MEAN) {
        for (size_t i = 0; i < size; i++) {
            if (dtype == TABLR_INT32) result_val += ((int*)data)[i];
            else if (dtype == TABLR_FLOAT32) result_val += ((float*)data)[i];
            else if (dtype == TABLR_FLOAT64) result_val += ((double*)data)[i];
        }
        if (func == TABLR_AGG_MEAN) result_val /= size;
    }
    
    TablrDataFrame* result = tablr_dataframe_create();
    TablrSeries* result_series = tablr_series_create(&result_val, 1, TABLR_FLOAT64, TABLR_CPU);
    tablr_dataframe_add_column(result, agg_column, result_series);
    
    return result;
}

/**
 * @brief Get descriptive statistics
 * 
 * Computes count, mean, std, min, and max for all numeric columns.
 * 
 * @param df Source dataframe
 * @return New dataframe with statistics, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_describe(const TablrDataFrame* df) {
    if (!df) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_create();
    size_t ncols = tablr_dataframe_ncols(df);
    
    const char* stats[] = {"count", "mean", "std", "min", "max"};
    double* stat_data = (double*)calloc(5, sizeof(double));
    
    for (size_t col = 0; col < ncols; col++) {
        size_t name_count;
        char** names = tablr_dataframe_columns(df, &name_count);
        TablrSeries* s = tablr_dataframe_get_column(df, names[col]);
        
        void* data = tablr_series_data(s);
        size_t size = tablr_series_size(s);
        TablrDType dtype = tablr_series_dtype(s);
        
        stat_data[0] = (double)size;
        
        double sum = 0.0, min_val = INFINITY, max_val = -INFINITY;
        for (size_t i = 0; i < size; i++) {
            double val = 0.0;
            if (dtype == TABLR_INT32) val = ((int*)data)[i];
            else if (dtype == TABLR_FLOAT32) val = ((float*)data)[i];
            else if (dtype == TABLR_FLOAT64) val = ((double*)data)[i];
            
            sum += val;
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
        }
        
        stat_data[1] = sum / size;
        stat_data[3] = min_val;
        stat_data[4] = max_val;
        
        double var = 0.0;
        for (size_t i = 0; i < size; i++) {
            double val = 0.0;
            if (dtype == TABLR_INT32) val = ((int*)data)[i];
            else if (dtype == TABLR_FLOAT32) val = ((float*)data)[i];
            else if (dtype == TABLR_FLOAT64) val = ((double*)data)[i];
            var += (val - stat_data[1]) * (val - stat_data[1]);
        }
        stat_data[2] = sqrt(var / size);
        
        for (size_t i = 0; i < name_count; i++) free(names[i]);
        free(names);
    }
    
    for (size_t i = 0; i < 5; i++) {
        TablrSeries* s = tablr_series_create(&stat_data[i], 1, TABLR_FLOAT64, TABLR_CPU);
        tablr_dataframe_add_column(result, stats[i], s);
    }
    
    free(stat_data);
    return result;
}
