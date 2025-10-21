/**
 * @file filter.h
 * @brief DataFrame filtering operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_OPS_FILTER_H
#define TABLR_OPS_FILTER_H

#include "tablr/core/dataframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Filter callback function type
 * @param row Row index
 * @param ctx User context pointer
 * @return true to include row, false to exclude
 */
typedef bool (*TablrFilterFunc)(size_t row, void* ctx);

/**
 * @brief Filter dataframe rows by predicate
 * @param df Source dataframe
 * @param predicate Filter function
 * @param ctx User context
 * @return New filtered dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_filter(const TablrDataFrame* df, TablrFilterFunc predicate, void* ctx);

/**
 * @brief Select rows by index array
 * @param df Source dataframe
 * @param indices Array of row indices
 * @param count Number of indices
 * @return New dataframe with selected rows
 */
TablrDataFrame* tablr_dataframe_select_rows(const TablrDataFrame* df, const size_t* indices, size_t count);

/**
 * @brief Select columns by name array
 * @param df Source dataframe
 * @param columns Array of column names
 * @param count Number of columns
 * @return New dataframe with selected columns
 */
TablrDataFrame* tablr_dataframe_select_columns(const TablrDataFrame* df, const char** columns, size_t count);

/**
 * @brief Drop rows with missing values
 * @param df Source dataframe
 * @return New dataframe without missing values
 */
TablrDataFrame* tablr_dataframe_dropna(const TablrDataFrame* df);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_OPS_FILTER_H */
