/**
 * @file npu_ops.h
 * @brief NPU operations header
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_NPU_OPS_H
#define TABLR_NPU_OPS_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

bool tablr_npu_available(void);
int tablr_npu_device_count(void);
bool tablr_npu_synchronize(void);
void tablr_npu_device_properties(int device_id);
void* tablr_npu_malloc(size_t size);
void tablr_npu_free(void* ptr);
bool tablr_npu_memcpy_h2d(void* dst, const void* src, size_t size);
bool tablr_npu_memcpy_d2h(void* dst, const void* src, size_t size);
bool tablr_npu_add_float32(float* result, const float* a, const float* b, size_t size);
bool tablr_npu_mul_float32(float* result, const float* a, const float* b, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_NPU_OPS_H */
