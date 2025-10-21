/**
 * @file filter.c
 * @brief Implementation of filtering operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements dataframe filtering and selection operations including
 * predicate-based filtering, row selection, and column selection.
 */

#include "tablr/ops/filter.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Filter dataframe rows using predicate function
 * 
 * Applies a predicate function to each row and keeps only rows where
 * the predicate returns true. Creates a new dataframe with filtered rows.
 * 
 * @param df Source dataframe to filter
 * @param predicate Function that returns true for rows to keep
 * @param ctx User context passed to predicate function
 * @return New dataframe with filtered rows, or NULL on error
 */
TablrDataFrame* tablr_dataframe_filter(const TablrDataFrame* df, TablrFilterFunc predicate, void* ctx) {
    if (!df || !predicate) return NULL;
    
    size_t nrows = tablr_dataframe_nrows(df);
    
    /* Evaluate predicate for each row */
    bool* keep = (bool*)malloc(nrows * sizeof(bool));
    size_t keep_count = 0;
    
    for (size_t i = 0; i < nrows; i++) {
        keep[i] = predicate(i, ctx);
        if (keep[i]) keep_count++;
    }
    
    /* Build array of indices to keep */
    size_t* indices = (size_t*)malloc(keep_count * sizeof(size_t));
    size_t idx = 0;
    for (size_t i = 0; i < nrows; i++) {
        if (keep[i]) indices[idx++] = i;
    }
    
    /* Select rows by indices */
    TablrDataFrame* result = tablr_dataframe_select_rows(df, indices, keep_count);
    
    free(keep);
    free(indices);
    
    return result;
}

/**
 * @brief Select specific rows by index array
 * 
 * Creates a new dataframe containing only the rows at the specified indices.
 * Preserves all columns and maintains the order of indices provided.
 * 
 * @param df Source dataframe
 * @param indices Array of row indices to select
 * @param count Number of indices in array
 * @return New dataframe with selected rows, or NULL on error
 */
TablrDataFrame* tablr_dataframe_select_rows(const TablrDataFrame* df, const size_t* indices, size_t count) {
    if (!df || !indices) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_create();
    size_t ncols = tablr_dataframe_ncols(df);
    
    /* Process each column */
    for (size_t col = 0; col < ncols; col++) {
        size_t name_count;
        char** names = tablr_dataframe_columns(df, &name_count);
        TablrSeries* s = tablr_dataframe_get_column(df, names[col]);
        
        void* data = tablr_series_data(s);
        TablrDType dtype = tablr_series_dtype(s);
        TablrDevice device = tablr_series_device(s);
        size_t elem_size = tablr_dtype_size(dtype);
        
        /* Copy selected rows */
        void* new_data = malloc(count * elem_size);
        for (size_t i = 0; i < count; i++) {
            memcpy((char*)new_data + i * elem_size, 
                   (char*)data + indices[i] * elem_size, elem_size);
        }
        
        TablrSeries* new_series = tablr_series_create(new_data, count, dtype, device);
        tablr_dataframe_add_column(result, names[col], new_series);
        
        free(new_data);
        for (size_t i = 0; i < name_count; i++) free(names[i]);
        free(names);
    }
    
    return result;
}

/**
 * @brief Select specific columns by name array
 * 
 * Creates a new dataframe containing only the specified columns.
 * Preserves all rows and maintains the order of columns provided.
 * 
 * @param df Source dataframe
 * @param columns Array of column names to select
 * @param count Number of columns in array
 * @return New dataframe with selected columns, or NULL on error
 */
TablrDataFrame* tablr_dataframe_select_columns(const TablrDataFrame* df, const char** columns, size_t count) {
    if (!df || !columns) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_create();
    
    /* Copy each requested column */
    for (size_t i = 0; i < count; i++) {
        TablrSeries* s = tablr_dataframe_get_column(df, columns[i]);
        if (s) {
            void* data = tablr_series_data(s);
            TablrDType dtype = tablr_series_dtype(s);
            TablrDevice device = tablr_series_device(s);
            size_t size = tablr_series_size(s);
            
            TablrSeries* new_series = tablr_series_create(data, size, dtype, device);
            tablr_dataframe_add_column(result, columns[i], new_series);
        }
    }
    
    return result;
}

/**
 * @brief Drop rows with missing values
 * 
 * Creates a new dataframe with rows containing missing values removed.
 * Currently returns a copy as missing value detection is not yet implemented.
 * 
 * @param df Source dataframe
 * @return New dataframe without missing values, or NULL on error
 */
TablrDataFrame* tablr_dataframe_dropna(const TablrDataFrame* df) {
    if (!df) return NULL;
    /* TODO: Implement missing value detection */
    return tablr_dataframe_copy(df);
}
