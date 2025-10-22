/**
 * @file series.h
 * @brief Series data structure and operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_CORE_SERIES_H
#define TABLR_CORE_SERIES_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create series from array data
 * @param data Pointer to source data
 * @param size Number of elements
 * @param dtype Data type
 * @param device Target device (use TABLR_CPU for default or call tablr_get_default_device())
 * @return Pointer to new series or NULL on failure
 */
TablrSeries* tablr_series_create(const void* data, size_t size, TablrDType dtype, TablrDevice device);

/**
 * @brief Create series from array data using default device
 * @param data Pointer to source data
 * @param size Number of elements
 * @param dtype Data type
 * @return Pointer to new series or NULL on failure
 */
TablrSeries* tablr_series_create_default(const void* data, size_t size, TablrDType dtype);

/**
 * @brief Create series filled with zeros
 * @param size Number of elements
 * @param dtype Data type
 * @param device Target device
 * @return Pointer to new series or NULL on failure
 */
TablrSeries* tablr_series_zeros(size_t size, TablrDType dtype, TablrDevice device);

/**
 * @brief Create series filled with ones
 * @param size Number of elements
 * @param dtype Data type
 * @param device Target device
 * @return Pointer to new series or NULL on failure
 */
TablrSeries* tablr_series_ones(size_t size, TablrDType dtype, TablrDevice device);

/**
 * @brief Create series with range of values
 * @param start Start value
 * @param stop Stop value (exclusive)
 * @param step Step size
 * @param device Target device
 * @return Pointer to new series or NULL on failure
 */
TablrSeries* tablr_series_arange(double start, double stop, double step, TablrDevice device);

/**
 * @brief Free series memory
 * @param series Series to free
 */
void tablr_series_free(TablrSeries* series);

/**
 * @brief Get series size
 * @param series Series pointer
 * @return Number of elements
 */
size_t tablr_series_size(const TablrSeries* series);

/**
 * @brief Get series data type
 * @param series Series pointer
 * @return Data type
 */
TablrDType tablr_series_dtype(const TablrSeries* series);

/**
 * @brief Get series device
 * @param series Series pointer
 * @return Device type
 */
TablrDevice tablr_series_device(const TablrSeries* series);

/**
 * @brief Get pointer to series data
 * @param series Series pointer
 * @return Pointer to data
 */
void* tablr_series_data(const TablrSeries* series);

/**
 * @brief Copy series to different device
 * @param series Source series
 * @param device Target device
 * @return New series on target device or NULL on failure
 */
TablrSeries* tablr_series_to_device(const TablrSeries* series, TablrDevice device);

/**
 * @brief Print series to stdout
 * @param series Series to print
 */
void tablr_series_print(const TablrSeries* series);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_CORE_SERIES_H */
