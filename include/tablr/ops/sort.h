/**
 * @file sort.h
 * @brief DataFrame sorting operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_OPS_SORT_H
#define TABLR_OPS_SORT_H

#include "tablr/core/dataframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sort dataframe by column
 * @param df Source dataframe
 * @param column Column name to sort by
 * @param ascending Sort order (true for ascending)
 * @return New sorted dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_sort(const TablrDataFrame* df, const char* column, bool ascending);

/**
 * @brief Sort dataframe by multiple columns
 * @param df Source dataframe
 * @param columns Array of column names
 * @param ascending Array of sort orders
 * @param count Number of columns
 * @return New sorted dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_sort_multi(const TablrDataFrame* df, const char** columns, 
                                            const bool* ascending, size_t count);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_OPS_SORT_H */
