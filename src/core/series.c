/**
 * @file series.c
 * @brief Implementation of series operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements all series-related operations including creation,
 * manipulation, and device transfer for the Tablr library.
 */

#include "tablr/core/series.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Internal series structure
 * 
 * Contains the actual data, size, data type, and target device
 * for a one-dimensional array of values.
 */
struct TablrSeries {
    void* data;          /**< Pointer to series data */
    size_t size;         /**< Number of elements */
    TablrDType dtype;    /**< Data type of elements */
    TablrDevice device;  /**< Target compute device */
};

/**
 * @brief Create series from array data
 * 
 * Allocates and initializes a new series by copying data from the provided array.
 * 
 * @param data Pointer to source data array
 * @param size Number of elements in array
 * @param dtype Data type of elements
 * @param device Target compute device
 * @return Pointer to new series, or NULL on failure
 */
TablrSeries* tablr_series_create(const void* data, size_t size, TablrDType dtype, TablrDevice device) {
    if (!data || size == 0) return NULL;
    
    TablrSeries* s = (TablrSeries*)malloc(sizeof(TablrSeries));
    if (!s) return NULL;
    
    size_t elem_size = tablr_dtype_size(dtype);
    s->data = malloc(size * elem_size);
    if (!s->data) {
        free(s);
        return NULL;
    }
    
    memcpy(s->data, data, size * elem_size);
    s->size = size;
    s->dtype = dtype;
    s->device = device;
    
    return s;
}

/**
 * @brief Create series filled with zeros
 * 
 * Allocates a new series and initializes all elements to zero.
 * 
 * @param size Number of elements
 * @param dtype Data type of elements
 * @param device Target compute device
 * @return Pointer to new series, or NULL on failure
 */
TablrSeries* tablr_series_zeros(size_t size, TablrDType dtype, TablrDevice device) {
    if (size == 0) return NULL;
    
    TablrSeries* s = (TablrSeries*)malloc(sizeof(TablrSeries));
    if (!s) return NULL;
    
    size_t elem_size = tablr_dtype_size(dtype);
    s->data = calloc(size, elem_size);
    if (!s->data) {
        free(s);
        return NULL;
    }
    
    s->size = size;
    s->dtype = dtype;
    s->device = device;
    
    return s;
}

/**
 * @brief Create series filled with ones
 * 
 * Allocates a new series and initializes all elements to one.
 * 
 * @param size Number of elements
 * @param dtype Data type of elements
 * @param device Target compute device
 * @return Pointer to new series, or NULL on failure
 */
TablrSeries* tablr_series_ones(size_t size, TablrDType dtype, TablrDevice device) {
    TablrSeries* s = tablr_series_zeros(size, dtype, device);
    if (!s) return NULL;
    
    if (dtype == TABLR_INT32) {
        int* data = (int*)s->data;
        for (size_t i = 0; i < size; i++) data[i] = 1;
    } else if (dtype == TABLR_FLOAT32) {
        float* data = (float*)s->data;
        for (size_t i = 0; i < size; i++) data[i] = 1.0f;
    } else if (dtype == TABLR_FLOAT64) {
        double* data = (double*)s->data;
        for (size_t i = 0; i < size; i++) data[i] = 1.0;
    }
    
    return s;
}

/**
 * @brief Create series with range of values
 * 
 * Creates a series with evenly spaced values from start to stop (exclusive).
 * 
 * @param start Starting value
 * @param stop Ending value (exclusive)
 * @param step Step size between values
 * @param device Target compute device
 * @return Pointer to new series, or NULL on failure
 */
TablrSeries* tablr_series_arange(double start, double stop, double step, TablrDevice device) {
    if (step == 0.0 || (stop - start) / step < 0) return NULL;
    
    size_t size = (size_t)((stop - start) / step);
    TablrSeries* s = tablr_series_zeros(size, TABLR_FLOAT64, device);
    if (!s) return NULL;
    
    double* data = (double*)s->data;
    for (size_t i = 0; i < size; i++) {
        data[i] = start + i * step;
    }
    
    return s;
}

/**
 * @brief Free series memory
 * 
 * Deallocates all memory associated with the series including data and structure.
 * 
 * @param series Series to free (can be NULL)
 */
void tablr_series_free(TablrSeries* series) {
    if (series) {
        free(series->data);
        free(series);
    }
}

/**
 * @brief Get series size
 * 
 * Returns the number of elements in the series.
 * 
 * @param series Series to query
 * @return Number of elements, or 0 if series is NULL
 */
size_t tablr_series_size(const TablrSeries* series) {
    return series ? series->size : 0;
}

/**
 * @brief Get series data type
 * 
 * Returns the data type of elements in the series.
 * 
 * @param series Series to query
 * @return Data type, or TABLR_INT32 if series is NULL
 */
TablrDType tablr_series_dtype(const TablrSeries* series) {
    return series ? series->dtype : TABLR_INT32;
}

/**
 * @brief Get series device
 * 
 * Returns the compute device where the series data resides.
 * 
 * @param series Series to query
 * @return Device type, or TABLR_CPU if series is NULL
 */
TablrDevice tablr_series_device(const TablrSeries* series) {
    return series ? series->device : TABLR_CPU;
}

/**
 * @brief Get pointer to series data
 * 
 * Returns a pointer to the underlying data array. Use with caution.
 * 
 * @param series Series to query
 * @return Pointer to data, or NULL if series is NULL
 */
void* tablr_series_data(const TablrSeries* series) {
    return series ? series->data : NULL;
}

/**
 * @brief Transfer series to different device
 * 
 * Creates a copy of the series on the specified device.
 * 
 * @param series Source series
 * @param device Target device
 * @return New series on target device, or NULL on failure
 */
TablrSeries* tablr_series_to_device(const TablrSeries* series, TablrDevice device) {
    if (!series) return NULL;
    return tablr_series_create(series->data, series->size, series->dtype, device);
}

/**
 * @brief Print series to console
 * 
 * Prints series metadata and up to 10 elements to stdout.
 * 
 * @param series Series to print
 */
void tablr_series_print(const TablrSeries* series) {
    if (!series) return;
    
    printf("Series(size=%zu, dtype=%s, device=%d)\n[", 
           series->size, tablr_dtype_name(series->dtype), series->device);
    
    size_t print_max = series->size < 10 ? series->size : 10;
    
    for (size_t i = 0; i < print_max; i++) {
        if (series->dtype == TABLR_INT32) {
            printf("%d", ((int*)series->data)[i]);
        } else if (series->dtype == TABLR_FLOAT32) {
            printf("%.2f", ((float*)series->data)[i]);
        } else if (series->dtype == TABLR_FLOAT64) {
            printf("%.2f", ((double*)series->data)[i]);
        }
        if (i < print_max - 1) printf(", ");
    }
    
    if (series->size > 10) printf(", ...");
    printf("]\n");
}
