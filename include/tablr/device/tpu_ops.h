/**
 * @file tpu_ops.h
 * @brief TPU operations header
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_TPU_OPS_H
#define TABLR_TPU_OPS_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

bool tablr_tpu_available(void);
int tablr_tpu_device_count(void);
bool tablr_tpu_synchronize(void);
void tablr_tpu_device_properties(int device_id);
void* tablr_tpu_malloc(size_t size);
void tablr_tpu_free(void* ptr);
bool tablr_tpu_memcpy_h2d(void* dst, const void* src, size_t size);
bool tablr_tpu_memcpy_d2h(void* dst, const void* src, size_t size);
bool tablr_tpu_add_float32(float* result, const float* a, const float* b, size_t size);
bool tablr_tpu_mul_float32(float* result, const float* a, const float* b, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_TPU_OPS_H */
