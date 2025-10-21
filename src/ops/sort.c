/**
 * @file sort.c
 * @brief Implementation of sorting operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements dataframe sorting operations including single-column
 * and multi-column sorting with ascending/descending order support.
 */

#include "tablr/ops/sort.h"
#include "tablr/ops/filter.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Internal structure for sorting
 * 
 * Pairs row indices with their sort key values.
 */
typedef struct {
    size_t index;  /**< Original row index */
    double value;  /**< Sort key value */
} SortPair;

/**
 * @brief Comparison function for ascending sort
 * @param a First element
 * @param b Second element
 * @return Comparison result
 */
static int compare_asc(const void* a, const void* b) {
    double diff = ((SortPair*)a)->value - ((SortPair*)b)->value;
    return (diff > 0) - (diff < 0);
}

/**
 * @brief Comparison function for descending sort
 * @param a First element
 * @param b Second element
 * @return Comparison result
 */
static int compare_desc(const void* a, const void* b) {
    double diff = ((SortPair*)b)->value - ((SortPair*)a)->value;
    return (diff > 0) - (diff < 0);
}

/**
 * @brief Sort dataframe by column
 * 
 * Creates a new dataframe with rows sorted by the specified column.
 * 
 * @param df Source dataframe
 * @param column Column name to sort by
 * @param ascending Sort order (true for ascending, false for descending)
 * @return New sorted dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_sort(const TablrDataFrame* df, const char* column, bool ascending) {
    if (!df || !column) return NULL;
    
    TablrSeries* sort_col = tablr_dataframe_get_column(df, column);
    if (!sort_col) return NULL;
    
    size_t nrows = tablr_series_size(sort_col);
    SortPair* pairs = (SortPair*)malloc(nrows * sizeof(SortPair));
    
    void* data = tablr_series_data(sort_col);
    TablrDType dtype = tablr_series_dtype(sort_col);
    
    for (size_t i = 0; i < nrows; i++) {
        pairs[i].index = i;
        if (dtype == TABLR_INT32) {
            pairs[i].value = (double)((int*)data)[i];
        } else if (dtype == TABLR_FLOAT32) {
            pairs[i].value = (double)((float*)data)[i];
        } else if (dtype == TABLR_FLOAT64) {
            pairs[i].value = ((double*)data)[i];
        }
    }
    
    qsort(pairs, nrows, sizeof(SortPair), ascending ? compare_asc : compare_desc);
    
    size_t* indices = (size_t*)malloc(nrows * sizeof(size_t));
    for (size_t i = 0; i < nrows; i++) {
        indices[i] = pairs[i].index;
    }
    
    TablrDataFrame* result = tablr_dataframe_select_rows(df, indices, nrows);
    
    free(pairs);
    free(indices);
    
    return result;
}

/**
 * @brief Sort dataframe by multiple columns
 * 
 * Sorts by multiple columns in order, with individual sort directions.
 * 
 * @param df Source dataframe
 * @param columns Array of column names to sort by
 * @param ascending Array of sort orders for each column
 * @param count Number of columns
 * @return New sorted dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_sort_multi(const TablrDataFrame* df, const char** columns, 
                                            const bool* ascending, size_t count) {
    if (!df || !columns || count == 0) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_copy(df);
    
    for (size_t i = count; i > 0; i--) {
        TablrDataFrame* temp = tablr_dataframe_sort(result, columns[i-1], ascending[i-1]);
        tablr_dataframe_free(result);
        result = temp;
    }
    
    return result;
}
