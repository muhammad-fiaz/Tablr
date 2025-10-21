/**
 * @file types.h
 * @brief Core type definitions for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_CORE_TYPES_H
#define TABLR_CORE_TYPES_H

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Data type enumeration
 */
typedef enum {
    TABLR_INT32,    /**< 32-bit signed integer */
    TABLR_INT64,    /**< 64-bit signed integer */
    TABLR_FLOAT32,  /**< 32-bit floating point */
    TABLR_FLOAT64,  /**< 64-bit floating point */
    TABLR_STRING,   /**< String type */
    TABLR_BOOL      /**< Boolean type */
} TablrDType;

/**
 * @brief Device type enumeration for compute acceleration
 */
typedef enum {
    TABLR_CPU,   /**< Standard CPU execution */
    TABLR_CUDA,  /**< NVIDIA CUDA GPU */
    TABLR_XPU,   /**< Intel XPU */
    TABLR_NPU,   /**< Neural Processing Unit */
    TABLR_TPU    /**< Tensor Processing Unit */
} TablrDevice;

/**
 * @brief Opaque series structure
 */
typedef struct TablrSeries TablrSeries;

/**
 * @brief Opaque dataframe structure
 */
typedef struct TablrDataFrame TablrDataFrame;

/**
 * @brief Get size of data type in bytes
 * @param dtype Data type
 * @return Size in bytes
 */
size_t tablr_dtype_size(TablrDType dtype);

/**
 * @brief Get string name of data type
 * @param dtype Data type
 * @return String representation
 */
const char* tablr_dtype_name(TablrDType dtype);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_CORE_TYPES_H */
