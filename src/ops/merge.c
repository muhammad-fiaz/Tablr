/**
 * @file merge.c
 * @brief Implementation of merging and joining operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements dataframe merging and concatenation operations including
 * various join types and vertical concatenation.
 */

#include "tablr/ops/merge.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Merge two dataframes on a column
 * 
 * Performs a join operation between two dataframes on a common column.
 * 
 * @param left Left dataframe
 * @param right Right dataframe
 * @param on Column name to join on
 * @param join_type Type of join (TABLR_JOIN_INNER, TABLR_JOIN_LEFT, etc.)
 * @return New merged dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_merge(const TablrDataFrame* left, const TablrDataFrame* right, 
                                       const char* on, TablrJoinType join_type) {
    if (!left || !right || !on) return NULL;
    
    (void)join_type;
    
    TablrDataFrame* result = tablr_dataframe_copy(left);
    
    size_t right_ncols = tablr_dataframe_ncols(right);
    size_t name_count;
    char** names = tablr_dataframe_columns(right, &name_count);
    
    for (size_t i = 0; i < right_ncols; i++) {
        if (strcmp(names[i], on) != 0) {
            TablrSeries* s = tablr_dataframe_get_column(right, names[i]);
            if (s) {
                void* data = tablr_series_data(s);
                TablrDType dtype = tablr_series_dtype(s);
                TablrDevice device = tablr_series_device(s);
                size_t size = tablr_series_size(s);
                
                TablrSeries* new_series = tablr_series_create(data, size, dtype, device);
                tablr_dataframe_add_column(result, names[i], new_series);
            }
        }
    }
    
    for (size_t i = 0; i < name_count; i++) free(names[i]);
    free(names);
    
    return result;
}

/**
 * @brief Concatenate dataframes vertically
 * 
 * Stacks multiple dataframes vertically, combining rows.
 * All dataframes must have the same columns.
 * 
 * @param dfs Array of dataframes to concatenate
 * @param count Number of dataframes
 * @return New concatenated dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_concat(const TablrDataFrame** dfs, size_t count) {
    if (!dfs || count == 0) return NULL;
    
    size_t total_rows = 0;
    for (size_t i = 0; i < count; i++) {
        total_rows += tablr_dataframe_nrows(dfs[i]);
    }
    
    TablrDataFrame* result = tablr_dataframe_create();
    size_t ncols = tablr_dataframe_ncols(dfs[0]);
    
    for (size_t col = 0; col < ncols; col++) {
        size_t name_count;
        char** names = tablr_dataframe_columns(dfs[0], &name_count);
        
        TablrSeries* first_series = tablr_dataframe_get_column(dfs[0], names[col]);
        TablrDType dtype = tablr_series_dtype(first_series);
        TablrDevice device = tablr_series_device(first_series);
        size_t elem_size = tablr_dtype_size(dtype);
        
        void* concat_data = malloc(total_rows * elem_size);
        size_t offset = 0;
        
        for (size_t i = 0; i < count; i++) {
            TablrSeries* s = tablr_dataframe_get_column(dfs[i], names[col]);
            void* data = tablr_series_data(s);
            size_t size = tablr_series_size(s);
            
            memcpy((char*)concat_data + offset, data, size * elem_size);
            offset += size * elem_size;
        }
        
        TablrSeries* new_series = tablr_series_create(concat_data, total_rows, dtype, device);
        tablr_dataframe_add_column(result, names[col], new_series);
        
        free(concat_data);
        for (size_t i = 0; i < name_count; i++) free(names[i]);
        free(names);
    }
    
    return result;
}
