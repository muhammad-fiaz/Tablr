/**
 * @file csv.h
 * @brief CSV file I/O operations
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_IO_CSV_H
#define TABLR_IO_CSV_H

#include "tablr/core/dataframe.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read CSV file into dataframe
 * @param filename Path to CSV file
 * @param delimiter Column delimiter character
 * @param has_header Whether file has header row
 * @return Pointer to dataframe or NULL on failure
 */
TablrDataFrame* tablr_read_csv(const char* filename, char delimiter, bool has_header);

/**
 * @brief Write dataframe to CSV file
 * @param df DataFrame to write
 * @param filename Output file path
 * @param delimiter Column delimiter character
 * @param write_header Whether to write header row
 * @return true on success, false on failure
 */
bool tablr_to_csv(const TablrDataFrame* df, const char* filename, char delimiter, bool write_header);

/**
 * @brief Read CSV with default settings (comma delimiter, with header)
 * @param filename Path to CSV file
 * @return Pointer to dataframe or NULL on failure
 */
TablrDataFrame* tablr_read_csv_default(const char* filename);

/**
 * @brief Write CSV with default settings (comma delimiter, with header)
 * @param df DataFrame to write
 * @param filename Output file path
 * @return true on success, false on failure
 */
bool tablr_to_csv_default(const TablrDataFrame* df, const char* filename);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_IO_CSV_H */
