/**
 * @file merge.h
 * @brief DataFrame merging and joining operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_OPS_MERGE_H
#define TABLR_OPS_MERGE_H

#include "tablr/core/dataframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Join type enumeration
 */
typedef enum {
    TABLR_JOIN_INNER,  /**< Inner join */
    TABLR_JOIN_LEFT,   /**< Left outer join */
    TABLR_JOIN_RIGHT,  /**< Right outer join */
    TABLR_JOIN_OUTER   /**< Full outer join */
} TablrJoinType;

/**
 * @brief Merge two dataframes on a column
 * @param left Left dataframe
 * @param right Right dataframe
 * @param on Column name to join on
 * @param join_type Type of join
 * @return New merged dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_merge(const TablrDataFrame* left, const TablrDataFrame* right, 
                                       const char* on, TablrJoinType join_type);

/**
 * @brief Concatenate dataframes vertically
 * @param dfs Array of dataframes
 * @param count Number of dataframes
 * @return New concatenated dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_concat(const TablrDataFrame** dfs, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_OPS_MERGE_H */
