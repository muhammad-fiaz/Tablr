/**
 * @file device.c
 * @brief Device management implementation
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file provides device management functionality for multi-device support
 * including CPU, CUDA, XPU, NPU, and TPU device operations.
 */

#include "tablr/core/types.h"
#include "tablr/device/cuda_ops.h"
#include "tablr/device/xpu_ops.h"
#include "tablr/device/npu_ops.h"
#include "tablr/device/tpu_ops.h"
#include <stdio.h>
#include <string.h>

static TablrDevice default_device = TABLR_CPU;

/**
 * @brief Get device name string
 * @param device Device type
 * @return Device name string
 */
const char* tablr_device_name(TablrDevice device) {
    switch (device) {
        case TABLR_CPU:  return "CPU";
        case TABLR_CUDA: return "CUDA";
        case TABLR_XPU:  return "XPU";
        case TABLR_NPU:  return "NPU";
        case TABLR_TPU:  return "TPU";
        default:         return "Unknown";
    }
}

/**
 * @brief Check if device is available
 * @param device Device type to check
 * @return true if device is available, false otherwise
 */
bool tablr_device_available(TablrDevice device) {
    switch (device) {
        case TABLR_CPU:
            return true;
        case TABLR_CUDA:
#ifdef TABLR_CUDA_ENABLED
            return tablr_cuda_available();
#else
            return false;
#endif
        case TABLR_XPU:
#ifdef TABLR_XPU_ENABLED
            return tablr_xpu_available();
#else
            return false;
#endif
        case TABLR_NPU:
#ifdef TABLR_NPU_ENABLED
            return tablr_npu_available();
#else
            return false;
#endif
        case TABLR_TPU:
#ifdef TABLR_TPU_ENABLED
            return tablr_tpu_available();
#else
            return false;
#endif
        default:
            return false;
    }
}

/**
 * @brief Get number of available devices of type
 * @param device Device type
 * @return Number of available devices
 */
int tablr_device_count(TablrDevice device) {
    switch (device) {
        case TABLR_CPU:
            return 1;
        case TABLR_CUDA:
#ifdef TABLR_CUDA_ENABLED
            return tablr_cuda_device_count();
#else
            return 0;
#endif
        case TABLR_XPU:
#ifdef TABLR_XPU_ENABLED
            return tablr_xpu_device_count();
#else
            return 0;
#endif
        case TABLR_NPU:
#ifdef TABLR_NPU_ENABLED
            return tablr_npu_device_count();
#else
            return 0;
#endif
        case TABLR_TPU:
#ifdef TABLR_TPU_ENABLED
            return tablr_tpu_device_count();
#else
            return 0;
#endif
        default:
            return 0;
    }
}

/**
 * @brief Synchronize device operations
 * @param device Device to synchronize
 * @return true on success, false on failure
 */
bool tablr_device_synchronize(TablrDevice device) {
    switch (device) {
        case TABLR_CPU:
            return true;
        case TABLR_CUDA:
#ifdef TABLR_CUDA_ENABLED
            return tablr_cuda_synchronize();
#else
            return false;
#endif
        case TABLR_XPU:
#ifdef TABLR_XPU_ENABLED
            return tablr_xpu_synchronize();
#else
            return false;
#endif
        case TABLR_NPU:
#ifdef TABLR_NPU_ENABLED
            return tablr_npu_synchronize();
#else
            return false;
#endif
        case TABLR_TPU:
#ifdef TABLR_TPU_ENABLED
            return tablr_tpu_synchronize();
#else
            return false;
#endif
        default:
            return false;
    }
}

/**
 * @brief Print device information
 * @param device Device type
 */
void tablr_device_info(TablrDevice device) {
    printf("Device: %s\n", tablr_device_name(device));
    printf("Available: %s\n", tablr_device_available(device) ? "Yes" : "No");
    printf("Count: %d\n", tablr_device_count(device));
    
    if (!tablr_device_available(device)) return;
    
    int count = tablr_device_count(device);
    for (int i = 0; i < count; i++) {
        printf("\n");
#ifdef TABLR_CUDA_ENABLED
        if (device == TABLR_CUDA) tablr_cuda_device_properties(i);
#endif
#ifdef TABLR_XPU_ENABLED
        if (device == TABLR_XPU) tablr_xpu_device_properties(i);
#endif
#ifdef TABLR_NPU_ENABLED
        if (device == TABLR_NPU) tablr_npu_device_properties(i);
#endif
#ifdef TABLR_TPU_ENABLED
        if (device == TABLR_TPU) tablr_tpu_device_properties(i);
#endif
    }
}

/**
 * @brief Set default device for operations
 * @param device Device type to set as default
 */
void tablr_set_default_device(TablrDevice device) {
    if (tablr_device_available(device)) {
        default_device = device;
    }
}

/**
 * @brief Get current default device
 * @return Current default device type
 */
TablrDevice tablr_get_default_device(void) {
    return default_device;
}
