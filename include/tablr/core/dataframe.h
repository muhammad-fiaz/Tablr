/**
 * @file dataframe.h
 * @brief DataFrame data structure and operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_CORE_DATAFRAME_H
#define TABLR_CORE_DATAFRAME_H

#include "tablr/core/types.h"
#include "tablr/core/series.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create empty dataframe
 * @return Pointer to new dataframe or NULL on failure
 */
TablrDataFrame* tablr_dataframe_create(void);

/**
 * @brief Free dataframe memory
 * @param df DataFrame to free
 */
void tablr_dataframe_free(TablrDataFrame* df);

/**
 * @brief Add column to dataframe
 * @param df DataFrame pointer
 * @param name Column name
 * @param series Series data
 * @return true on success, false on failure
 */
bool tablr_dataframe_add_column(TablrDataFrame* df, const char* name, TablrSeries* series);

/**
 * @brief Get column from dataframe
 * @param df DataFrame pointer
 * @param name Column name
 * @return Series pointer or NULL if not found
 */
TablrSeries* tablr_dataframe_get_column(const TablrDataFrame* df, const char* name);

/**
 * @brief Remove column from dataframe
 * @param df DataFrame pointer
 * @param name Column name
 * @return true on success, false on failure
 */
bool tablr_dataframe_remove_column(TablrDataFrame* df, const char* name);

/**
 * @brief Get number of rows
 * @param df DataFrame pointer
 * @return Number of rows
 */
size_t tablr_dataframe_nrows(const TablrDataFrame* df);

/**
 * @brief Get number of columns
 * @param df DataFrame pointer
 * @return Number of columns
 */
size_t tablr_dataframe_ncols(const TablrDataFrame* df);

/**
 * @brief Get column names
 * @param df DataFrame pointer
 * @param count Output parameter for number of names
 * @return Array of column names (caller must free)
 */
char** tablr_dataframe_columns(const TablrDataFrame* df, size_t* count);

/**
 * @brief Print dataframe to stdout
 * @param df DataFrame to print
 */
void tablr_dataframe_print(const TablrDataFrame* df);

/**
 * @brief Get dataframe head (first n rows)
 * @param df DataFrame pointer
 * @param n Number of rows
 * @return New dataframe with first n rows
 */
TablrDataFrame* tablr_dataframe_head(const TablrDataFrame* df, size_t n);

/**
 * @brief Get dataframe tail (last n rows)
 * @param df DataFrame pointer
 * @param n Number of rows
 * @return New dataframe with last n rows
 */
TablrDataFrame* tablr_dataframe_tail(const TablrDataFrame* df, size_t n);

/**
 * @brief Copy dataframe
 * @param df DataFrame to copy
 * @return New dataframe copy
 */
TablrDataFrame* tablr_dataframe_copy(const TablrDataFrame* df);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_CORE_DATAFRAME_H */
