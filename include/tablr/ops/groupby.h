/**
 * @file groupby.h
 * @brief DataFrame grouping and aggregation operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_OPS_GROUPBY_H
#define TABLR_OPS_GROUPBY_H

#include "tablr/core/dataframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Aggregation function type
 */
typedef enum {
    TABLR_AGG_SUM,    /**< Sum aggregation */
    TABLR_AGG_MEAN,   /**< Mean aggregation */
    TABLR_AGG_MIN,    /**< Minimum aggregation */
    TABLR_AGG_MAX,    /**< Maximum aggregation */
    TABLR_AGG_COUNT,  /**< Count aggregation */
    TABLR_AGG_STD,    /**< Standard deviation */
    TABLR_AGG_VAR     /**< Variance */
} TablrAggFunc;

/**
 * @brief Group dataframe by column
 * @param df Source dataframe
 * @param column Column name to group by
 * @return New grouped dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_groupby(const TablrDataFrame* df, const char* column);

/**
 * @brief Aggregate grouped dataframe
 * @param df Grouped dataframe
 * @param agg_column Column to aggregate
 * @param func Aggregation function
 * @return New aggregated dataframe
 */
TablrDataFrame* tablr_dataframe_aggregate(const TablrDataFrame* df, const char* agg_column, TablrAggFunc func);

/**
 * @brief Get descriptive statistics
 * @param df Source dataframe
 * @return New dataframe with statistics
 */
TablrDataFrame* tablr_dataframe_describe(const TablrDataFrame* df);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_OPS_GROUPBY_H */
