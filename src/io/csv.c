/**
 * @file csv.c
 * @brief Implementation of CSV I/O operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements CSV file reading and writing operations with support
 * for custom delimiters and header rows.
 */

#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#define strdup _strdup
#endif

#include "tablr/io/csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 65536  /**< Maximum CSV line length */
#define MAX_COLUMNS 1024        /**< Maximum number of columns */

/**
 * @brief Read CSV file into dataframe
 * 
 * Parses a CSV file and creates a dataframe with the data. Supports custom
 * delimiters and optional header rows.
 * 
 * @param filename Path to CSV file
 * @param delimiter Column delimiter character (e.g., ',' or '\t')
 * @param has_header Whether first row contains column names
 * @return New dataframe with CSV data, or NULL on failure
 */
TablrDataFrame* tablr_read_csv(const char* filename, char delimiter, bool has_header) {
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;
    
    TablrDataFrame* df = tablr_dataframe_create();
    if (!df) {
        fclose(f);
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    char* headers[MAX_COLUMNS] = {0};
    size_t ncols = 0;
    
    if (has_header && fgets(line, sizeof(line), f)) {
        char* token = strtok(line, &delimiter);
        while (token && ncols < MAX_COLUMNS) {
            size_t len = strlen(token);
            if (len > 0 && token[len-1] == '\n') token[len-1] = '\0';
            if (len > 1 && token[len-2] == '\r') token[len-2] = '\0';
            headers[ncols++] = strdup(token);
            token = strtok(NULL, &delimiter);
        }
    }
    
    double** col_data = (double**)calloc(ncols, sizeof(double*));
    size_t* col_sizes = (size_t*)calloc(ncols, sizeof(size_t));
    size_t* col_caps = (size_t*)calloc(ncols, sizeof(size_t));
    
    for (size_t i = 0; i < ncols; i++) {
        col_caps[i] = 1024;
        col_data[i] = (double*)malloc(col_caps[i] * sizeof(double));
    }
    
    while (fgets(line, sizeof(line), f)) {
        char* token = strtok(line, &delimiter);
        size_t col = 0;
        
        while (token && col < ncols) {
            if (col_sizes[col] >= col_caps[col]) {
                col_caps[col] *= 2;
                col_data[col] = (double*)realloc(col_data[col], col_caps[col] * sizeof(double));
            }
            col_data[col][col_sizes[col]++] = atof(token);
            token = strtok(NULL, &delimiter);
            col++;
        }
    }
    
    for (size_t i = 0; i < ncols; i++) {
        TablrSeries* s = tablr_series_create(col_data[i], col_sizes[i], TABLR_FLOAT64, TABLR_CPU);
        char col_name[32];
        if (headers[i]) {
            tablr_dataframe_add_column(df, headers[i], s);
            free(headers[i]);
        } else {
            snprintf(col_name, sizeof(col_name), "col%zu", i);
            tablr_dataframe_add_column(df, col_name, s);
        }
        free(col_data[i]);
    }
    
    free(col_data);
    free(col_sizes);
    free(col_caps);
    fclose(f);
    
    return df;
}

/**
 * @brief Write dataframe to CSV file
 * 
 * Writes dataframe contents to a CSV file with custom delimiter and optional header.
 * 
 * @param df DataFrame to write
 * @param filename Output file path
 * @param delimiter Column delimiter character
 * @param write_header Whether to write column names as first row
 * @return true on success, false on failure
 */
bool tablr_to_csv(const TablrDataFrame* df, const char* filename, char delimiter, bool write_header) {
    if (!df || !filename) return false;
    
    FILE* f = fopen(filename, "w");
    if (!f) return false;
    
    size_t ncols = tablr_dataframe_ncols(df);
    size_t nrows = tablr_dataframe_nrows(df);
    
    if (write_header) {
        size_t count;
        char** names = tablr_dataframe_columns(df, &count);
        for (size_t i = 0; i < count; i++) {
            fprintf(f, "%s%c", names[i], i < count - 1 ? delimiter : '\n');
            free(names[i]);
        }
        free(names);
    }
    
    for (size_t row = 0; row < nrows; row++) {
        for (size_t col = 0; col < ncols; col++) {
            size_t count;
            char** names = tablr_dataframe_columns(df, &count);
            TablrSeries* s = tablr_dataframe_get_column(df, names[col]);
            void* data = tablr_series_data(s);
            TablrDType dtype = tablr_series_dtype(s);
            
            if (dtype == TABLR_INT32) {
                fprintf(f, "%d", ((int*)data)[row]);
            } else if (dtype == TABLR_FLOAT32) {
                fprintf(f, "%.6f", ((float*)data)[row]);
            } else if (dtype == TABLR_FLOAT64) {
                fprintf(f, "%.6f", ((double*)data)[row]);
            }
            
            fprintf(f, "%c", col < ncols - 1 ? delimiter : '\n');
            
            for (size_t i = 0; i < count; i++) free(names[i]);
            free(names);
        }
    }
    
    fclose(f);
    return true;
}

/**
 * @brief Read CSV with default settings
 * 
 * Convenience function that reads CSV with comma delimiter and header row.
 * 
 * @param filename Path to CSV file
 * @return New dataframe with CSV data, or NULL on failure
 */
TablrDataFrame* tablr_read_csv_default(const char* filename) {
    return tablr_read_csv(filename, ',', true);
}

/**
 * @brief Write CSV with default settings
 * 
 * Convenience function that writes CSV with comma delimiter and header row.
 * 
 * @param df DataFrame to write
 * @param filename Output file path
 * @return true on success, false on failure
 */
bool tablr_to_csv_default(const TablrDataFrame* df, const char* filename) {
    return tablr_to_csv(df, filename, ',', true);
}
