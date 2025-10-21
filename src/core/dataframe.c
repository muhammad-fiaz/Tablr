/**
 * @file dataframe.c
 * @brief Implementation of dataframe operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements all dataframe-related operations including creation,
 * column management, and data access for the Tablr library.
 */

#include "tablr/core/dataframe.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Internal column structure
 * 
 * Represents a named column containing a series of data.
 */
typedef struct {
    char* name;          /**< Column name */
    TablrSeries* series; /**< Column data */
} Column;

/**
 * @brief Internal dataframe structure
 * 
 * Contains an array of columns with metadata about dimensions.
 */
struct TablrDataFrame {
    Column* columns;  /**< Array of columns */
    size_t ncols;     /**< Number of columns */
    size_t nrows;     /**< Number of rows */
};

/**
 * @brief Create empty dataframe
 * 
 * Allocates and initializes a new empty dataframe with no columns or rows.
 * 
 * @return Pointer to new dataframe, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_create(void) {
    TablrDataFrame* df = (TablrDataFrame*)malloc(sizeof(TablrDataFrame));
    if (!df) return NULL;
    
    df->columns = NULL;
    df->ncols = 0;
    df->nrows = 0;
    
    return df;
}

/**
 * @brief Free dataframe memory
 * 
 * Deallocates all memory including columns, series, and structure.
 * 
 * @param df DataFrame to free (can be NULL)
 */
void tablr_dataframe_free(TablrDataFrame* df) {
    if (!df) return;
    
    for (size_t i = 0; i < df->ncols; i++) {
        free(df->columns[i].name);
        tablr_series_free(df->columns[i].series);
    }
    free(df->columns);
    free(df);
}

/**
 * @brief Add column to dataframe
 * 
 * Adds a named column with series data. Series size must match existing rows.
 * 
 * @param df DataFrame to modify
 * @param name Column name
 * @param series Series data
 * @return true on success, false on failure
 */
bool tablr_dataframe_add_column(TablrDataFrame* df, const char* name, TablrSeries* series) {
    if (!df || !name || !series) return false;
    
    size_t series_size = tablr_series_size(series);
    if (df->ncols > 0 && series_size != df->nrows) return false;
    
    Column* new_cols = (Column*)realloc(df->columns, (df->ncols + 1) * sizeof(Column));
    if (!new_cols) return false;
    
    df->columns = new_cols;
    df->columns[df->ncols].name = _strdup(name);
    df->columns[df->ncols].series = series;
    df->ncols++;
    
    if (df->nrows == 0) df->nrows = series_size;
    
    return true;
}

/**
 * @brief Get column by name
 * 
 * Returns the series for the specified column name.
 * 
 * @param df DataFrame to query
 * @param name Column name
 * @return Series pointer, or NULL if not found
 */
TablrSeries* tablr_dataframe_get_column(const TablrDataFrame* df, const char* name) {
    if (!df || !name) return NULL;
    
    for (size_t i = 0; i < df->ncols; i++) {
        if (strcmp(df->columns[i].name, name) == 0) {
            return df->columns[i].series;
        }
    }
    
    return NULL;
}

/**
 * @brief Remove column from dataframe
 * 
 * Removes the column with the specified name and frees its memory.
 * 
 * @param df DataFrame to modify
 * @param name Column name
 * @return true if removed, false if not found
 */
bool tablr_dataframe_remove_column(TablrDataFrame* df, const char* name) {
    if (!df || !name) return false;
    
    for (size_t i = 0; i < df->ncols; i++) {
        if (strcmp(df->columns[i].name, name) == 0) {
            free(df->columns[i].name);
            tablr_series_free(df->columns[i].series);
            
            for (size_t j = i; j < df->ncols - 1; j++) {
                df->columns[j] = df->columns[j + 1];
            }
            
            df->ncols--;
            return true;
        }
    }
    
    return false;
}

/**
 * @brief Get number of rows
 * 
 * Returns the number of rows in the dataframe.
 * 
 * @param df DataFrame to query
 * @return Number of rows, or 0 if df is NULL
 */
size_t tablr_dataframe_nrows(const TablrDataFrame* df) {
    return df ? df->nrows : 0;
}

/**
 * @brief Get number of columns
 * 
 * Returns the number of columns in the dataframe.
 * 
 * @param df DataFrame to query
 * @return Number of columns, or 0 if df is NULL
 */
size_t tablr_dataframe_ncols(const TablrDataFrame* df) {
    return df ? df->ncols : 0;
}

/**
 * @brief Get column names
 * 
 * Returns an array of column names. Caller must free each name and the array.
 * 
 * @param df DataFrame to query
 * @param count Output parameter for number of names
 * @return Array of column names, or NULL on failure
 */
char** tablr_dataframe_columns(const TablrDataFrame* df, size_t* count) {
    if (!df || !count) return NULL;
    
    *count = df->ncols;
    char** names = (char**)malloc(df->ncols * sizeof(char*));
    if (!names) return NULL;
    
    for (size_t i = 0; i < df->ncols; i++) {
        names[i] = _strdup(df->columns[i].name);
    }
    
    return names;
}

/**
 * @brief Print dataframe to console
 * 
 * Prints dataframe dimensions, column names, types, and up to 5 rows.
 * 
 * @param df DataFrame to print
 */
void tablr_dataframe_print(const TablrDataFrame* df) {
    if (!df) return;
    
    printf("DataFrame(%zu rows x %zu columns)\n", df->nrows, df->ncols);
    
    for (size_t i = 0; i < df->ncols; i++) {
        printf("%-15s", df->columns[i].name);
    }
    printf("\n");
    
    for (size_t i = 0; i < df->ncols; i++) {
        printf("%-15s", tablr_dtype_name(tablr_series_dtype(df->columns[i].series)));
    }
    printf("\n");
    
    size_t print_rows = df->nrows < 5 ? df->nrows : 5;
    for (size_t row = 0; row < print_rows; row++) {
        for (size_t col = 0; col < df->ncols; col++) {
            TablrSeries* s = df->columns[col].series;
            void* data = tablr_series_data(s);
            TablrDType dtype = tablr_series_dtype(s);
            
            if (dtype == TABLR_INT32) {
                printf("%-15d", ((int*)data)[row]);
            } else if (dtype == TABLR_FLOAT32) {
                printf("%-15.2f", ((float*)data)[row]);
            } else if (dtype == TABLR_FLOAT64) {
                printf("%-15.2f", ((double*)data)[row]);
            }
        }
        printf("\n");
    }
    
    if (df->nrows > 5) printf("... (%zu more rows)\n", df->nrows - 5);
}

/**
 * @brief Get first n rows
 * 
 * Creates a new dataframe containing the first n rows.
 * 
 * @param df Source dataframe
 * @param n Number of rows to select
 * @return New dataframe with first n rows, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_head(const TablrDataFrame* df, size_t n) {
    if (!df) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_create();
    if (!result) return NULL;
    
    size_t rows = n < df->nrows ? n : df->nrows;
    
    for (size_t i = 0; i < df->ncols; i++) {
        TablrSeries* s = df->columns[i].series;
        void* data = tablr_series_data(s);
        TablrDType dtype = tablr_series_dtype(s);
        TablrDevice device = tablr_series_device(s);
        
        TablrSeries* new_series = tablr_series_create(data, rows, dtype, device);
        tablr_dataframe_add_column(result, df->columns[i].name, new_series);
    }
    
    return result;
}

/**
 * @brief Get last n rows
 * 
 * Creates a new dataframe containing the last n rows.
 * 
 * @param df Source dataframe
 * @param n Number of rows to select
 * @return New dataframe with last n rows, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_tail(const TablrDataFrame* df, size_t n) {
    if (!df) return NULL;
    
    TablrDataFrame* result = tablr_dataframe_create();
    if (!result) return NULL;
    
    size_t rows = n < df->nrows ? n : df->nrows;
    size_t start = df->nrows - rows;
    
    for (size_t i = 0; i < df->ncols; i++) {
        TablrSeries* s = df->columns[i].series;
        void* data = tablr_series_data(s);
        TablrDType dtype = tablr_series_dtype(s);
        TablrDevice device = tablr_series_device(s);
        size_t elem_size = tablr_dtype_size(dtype);
        
        TablrSeries* new_series = tablr_series_create(
            (char*)data + start * elem_size, rows, dtype, device);
        tablr_dataframe_add_column(result, df->columns[i].name, new_series);
    }
    
    return result;
}

/**
 * @brief Copy dataframe
 * 
 * Creates a deep copy of the dataframe with all columns and data.
 * 
 * @param df DataFrame to copy
 * @return New dataframe copy, or NULL on failure
 */
TablrDataFrame* tablr_dataframe_copy(const TablrDataFrame* df) {
    if (!df) return NULL;
    
    TablrDataFrame* copy = tablr_dataframe_create();
    if (!copy) return NULL;
    
    for (size_t i = 0; i < df->ncols; i++) {
        TablrSeries* s = df->columns[i].series;
        void* data = tablr_series_data(s);
        TablrDType dtype = tablr_series_dtype(s);
        TablrDevice device = tablr_series_device(s);
        
        TablrSeries* new_series = tablr_series_create(data, tablr_series_size(s), dtype, device);
        tablr_dataframe_add_column(copy, df->columns[i].name, new_series);
    }
    
    return copy;
}
