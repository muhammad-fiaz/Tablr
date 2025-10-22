/**
 * @file device.h
 * @brief Device management API
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#ifndef TABLR_DEVICE_DEVICE_H
#define TABLR_DEVICE_DEVICE_H

#include "tablr/core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get device name string
 * @param device Device type
 * @return Device name string
 */
const char* tablr_device_name(TablrDevice device);

/**
 * @brief Check if device is available
 * @param device Device type to check
 * @return true if device is available, false otherwise
 */
bool tablr_device_available(TablrDevice device);

/**
 * @brief Get number of available devices of type
 * @param device Device type
 * @return Number of available devices
 */
int tablr_device_count(TablrDevice device);

/**
 * @brief Synchronize device operations
 * @param device Device to synchronize
 * @return true on success, false on failure
 */
bool tablr_device_synchronize(TablrDevice device);

/**
 * @brief Print device information
 * @param device Device type
 */
void tablr_device_info(TablrDevice device);

/**
 * @brief Set default device for operations
 * @param device Device type to set as default
 */
void tablr_set_default_device(TablrDevice device);

/**
 * @brief Get current default device
 * @return Current default device type
 */
TablrDevice tablr_get_default_device(void);

#ifdef __cplusplus
}
#endif

#endif /* TABLR_DEVICE_DEVICE_H */
