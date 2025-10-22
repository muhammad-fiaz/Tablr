/**
 * @file cuda_ops.h
 * @brief CUDA operations header
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_CUDA_OPS_H
#define TABLR_CUDA_OPS_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Device management */
int tablr_cuda_device_count(void);
bool tablr_cuda_available(void);
bool tablr_cuda_synchronize(void);
void tablr_cuda_device_properties(int device_id);

/* Memory management */
void* tablr_cuda_malloc(size_t size);
void tablr_cuda_free(void* ptr);
bool tablr_cuda_memcpy_h2d(void* dst, const void* src, size_t size);
bool tablr_cuda_memcpy_d2h(void* dst, const void* src, size_t size);
bool tablr_cuda_memcpy_d2d(void* dst, const void* src, size_t size);

/* Compute operations */
bool tablr_cuda_add_float32(float* result, const float* a, const float* b, size_t size);
bool tablr_cuda_mul_float32(float* result, const float* a, const float* b, size_t size);
bool tablr_cuda_scale_float32(float* result, const float* a, float scalar, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_CUDA_OPS_H */
