/**
 * @file types.c
 * @brief Implementation of core type utilities
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file implements utility functions for working with Tablr data types
 * including size calculations and string representations.
 */

#include "tablr/core/types.h"

/**
 * @brief Get size of data type in bytes
 * 
 * Returns the memory size required for a single element of the given data type.
 * 
 * @param dtype Data type to query
 * @return Size in bytes, or 0 for unknown types
 */
size_t tablr_dtype_size(TablrDType dtype) {
    switch (dtype) {
        case TABLR_INT32:
        case TABLR_FLOAT32:
            return 4;
        case TABLR_INT64:
        case TABLR_FLOAT64:
            return 8;
        case TABLR_BOOL:
            return 1;
        case TABLR_STRING:
            return sizeof(char*);
        default:
            return 0;
    }
}

/**
 * @brief Get string name of data type
 * 
 * Returns a human-readable string representation of the data type.
 * 
 * @param dtype Data type to query
 * @return String name (e.g., "int32", "float64")
 */
const char* tablr_dtype_name(TablrDType dtype) {
    switch (dtype) {
        case TABLR_INT32:    return "int32";
        case TABLR_INT64:    return "int64";
        case TABLR_FLOAT32:  return "float32";
        case TABLR_FLOAT64:  return "float64";
        case TABLR_STRING:   return "string";
        case TABLR_BOOL:     return "bool";
        default:             return "unknown";
    }
}
