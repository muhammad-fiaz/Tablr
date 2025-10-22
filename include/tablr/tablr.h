/**
 * @file tablr.h
 * @brief Main header for Tablr data manipulation library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This is the main include file for the Tablr library. Include this single
 * header to access all Tablr functionality including core data structures,
 * I/O operations, and data manipulation functions.
 * 
 * @example
 * @code
 * #include <tablr/tablr.h>
 * 
 * int main(void) {
 *     TablrDataFrame* df = tablr_dataframe_create();
 *     // ... use dataframe
 *     tablr_dataframe_free(df);
 *     return 0;
 * }
 * @endcode
 */

#ifndef TABLR_H
#define TABLR_H

#include "tablr/core/types.h"
#include "tablr/core/series.h"
#include "tablr/core/dataframe.h"
#include "tablr/io/csv.h"
#include "tablr/ops/filter.h"
#include "tablr/ops/sort.h"
#include "tablr/ops/groupby.h"
#include "tablr/ops/merge.h"
#include "tablr/device/device.h"

#ifdef TABLR_CUDA_ENABLED
#include "tablr/device/cuda_ops.h"
#endif

#ifdef TABLR_XPU_ENABLED
#include "tablr/device/xpu_ops.h"
#endif

#ifdef TABLR_NPU_ENABLED
#include "tablr/device/npu_ops.h"
#endif

#ifdef TABLR_TPU_ENABLED
#include "tablr/device/tpu_ops.h"
#endif

#endif /* TABLR_H */
