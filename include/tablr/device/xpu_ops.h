/**
 * @file xpu_ops.h
 * @brief Intel XPU operations header
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_XPU_OPS_H
#define TABLR_XPU_OPS_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

bool tablr_xpu_available(void);
int tablr_xpu_device_count(void);
bool tablr_xpu_synchronize(void);
void tablr_xpu_device_properties(int device_id);
void* tablr_xpu_malloc(size_t size);
void tablr_xpu_free(void* ptr);
bool tablr_xpu_memcpy_h2d(void* dst, const void* src, size_t size);
bool tablr_xpu_memcpy_d2h(void* dst, const void* src, size_t size);
bool tablr_xpu_add_float32(float* result, const float* a, const float* b, size_t size);
bool tablr_xpu_mul_float32(float* result, const float* a, const float* b, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_XPU_OPS_H */
