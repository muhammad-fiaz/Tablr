/**
 * @file xpu_ops.cpp
 * @brief Intel XPU device operations implementation
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file provides Intel XPU-specific operations using SYCL/DPC++
 * for GPU acceleration on Intel hardware.
 */

#include "tablr/core/types.h"

#ifdef TABLR_XPU_ENABLED
#include <sycl/sycl.hpp>
#include <iostream>

static sycl::queue* xpu_queue = nullptr;

extern "C" {

bool tablr_xpu_available(void) {
    try {
        auto devices = sycl::device::get_devices(sycl::info::device_type::gpu);
        return !devices.empty();
    } catch (...) {
        return false;
    }
}

int tablr_xpu_device_count(void) {
    try {
        auto devices = sycl::device::get_devices(sycl::info::device_type::gpu);
        return static_cast<int>(devices.size());
    } catch (...) {
        return 0;
    }
}

bool tablr_xpu_synchronize(void) {
    if (xpu_queue) {
        try {
            xpu_queue->wait();
            return true;
        } catch (...) {
            return false;
        }
    }
    return false;
}

void tablr_xpu_device_properties(int device_id) {
    try {
        auto devices = sycl::device::get_devices(sycl::info::device_type::gpu);
        if (device_id >= 0 && device_id < static_cast<int>(devices.size())) {
            auto& dev = devices[device_id];
            std::cout << "XPU Device " << device_id << ": " 
                      << dev.get_info<sycl::info::device::name>() << "\n";
            std::cout << "  Vendor: " << dev.get_info<sycl::info::device::vendor>() << "\n";
            std::cout << "  Max Compute Units: " 
                      << dev.get_info<sycl::info::device::max_compute_units>() << "\n";
            std::cout << "  Max Work Group Size: " 
                      << dev.get_info<sycl::info::device::max_work_group_size>() << "\n";
        }
    } catch (...) {
        std::cout << "Failed to get XPU device properties\n";
    }
}

void* tablr_xpu_malloc(size_t size) {
    if (!xpu_queue) {
        try {
            xpu_queue = new sycl::queue(sycl::gpu_selector_v);
        } catch (...) {
            return nullptr;
        }
    }
    try {
        return sycl::malloc_device(size, *xpu_queue);
    } catch (...) {
        return nullptr;
    }
}

void tablr_xpu_free(void* ptr) {
    if (ptr && xpu_queue) {
        sycl::free(ptr, *xpu_queue);
    }
}

bool tablr_xpu_memcpy_h2d(void* dst, const void* src, size_t size) {
    if (!xpu_queue) return false;
    try {
        xpu_queue->memcpy(dst, src, size).wait();
        return true;
    } catch (...) {
        return false;
    }
}

bool tablr_xpu_memcpy_d2h(void* dst, const void* src, size_t size) {
    if (!xpu_queue) return false;
    try {
        xpu_queue->memcpy(dst, src, size).wait();
        return true;
    } catch (...) {
        return false;
    }
}

bool tablr_xpu_add_float32(float* result, const float* a, const float* b, size_t size) {
    if (!xpu_queue) return false;
    try {
        xpu_queue->parallel_for(sycl::range<1>(size), [=](sycl::id<1> i) {
            result[i] = a[i] + b[i];
        }).wait();
        return true;
    } catch (...) {
        return false;
    }
}

bool tablr_xpu_mul_float32(float* result, const float* a, const float* b, size_t size) {
    if (!xpu_queue) return false;
    try {
        xpu_queue->parallel_for(sycl::range<1>(size), [=](sycl::id<1> i) {
            result[i] = a[i] * b[i];
        }).wait();
        return true;
    } catch (...) {
        return false;
    }
}

} // extern "C"
#endif
