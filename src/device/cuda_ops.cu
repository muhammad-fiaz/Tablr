/**
 * @file cuda_ops.cu
 * @brief CUDA device operations implementation
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This file provides CUDA-specific operations for GPU acceleration
 * including memory management, device queries, and kernel operations.
 */

#include "tablr/core/types.h"
#include <cuda_runtime.h>
#include <stdio.h>

/**
 * @brief Get number of CUDA devices
 * @return Number of available CUDA devices
 */
int tablr_cuda_device_count(void) {
    int count = 0;
    cudaError_t err = cudaGetDeviceCount(&count);
    if (err != cudaSuccess) {
        return 0;
    }
    return count;
}

/**
 * @brief Check if CUDA is available
 * @return true if CUDA is available, false otherwise
 */
bool tablr_cuda_available(void) {
    return tablr_cuda_device_count() > 0;
}

/**
 * @brief Synchronize CUDA device
 * @return true on success, false on failure
 */
bool tablr_cuda_synchronize(void) {
    cudaError_t err = cudaDeviceSynchronize();
    return err == cudaSuccess;
}

/**
 * @brief Get CUDA device properties
 * @param device_id Device ID to query
 */
void tablr_cuda_device_properties(int device_id) {
    cudaDeviceProp prop;
    cudaError_t err = cudaGetDeviceProperties(&prop, device_id);
    
    if (err != cudaSuccess) {
        printf("Failed to get device properties\n");
        return;
    }
    
    printf("CUDA Device %d: %s\n", device_id, prop.name);
    printf("  Compute Capability: %d.%d\n", prop.major, prop.minor);
    printf("  Total Memory: %.2f GB\n", prop.totalGlobalMem / (1024.0 * 1024.0 * 1024.0));
    printf("  Multiprocessors: %d\n", prop.multiProcessorCount);
    printf("  Max Threads per Block: %d\n", prop.maxThreadsPerBlock);
    printf("  Warp Size: %d\n", prop.warpSize);
}

/**
 * @brief Allocate CUDA device memory
 * @param size Size in bytes
 * @return Pointer to device memory or NULL on failure
 */
void* tablr_cuda_malloc(size_t size) {
    void* ptr = NULL;
    cudaError_t err = cudaMalloc(&ptr, size);
    if (err != cudaSuccess) {
        return NULL;
    }
    return ptr;
}

/**
 * @brief Free CUDA device memory
 * @param ptr Pointer to device memory
 */
void tablr_cuda_free(void* ptr) {
    if (ptr != NULL) {
        cudaFree(ptr);
    }
}

/**
 * @brief Copy memory from host to device
 * @param dst Destination device pointer
 * @param src Source host pointer
 * @param size Size in bytes
 * @return true on success, false on failure
 */
bool tablr_cuda_memcpy_h2d(void* dst, const void* src, size_t size) {
    cudaError_t err = cudaMemcpy(dst, src, size, cudaMemcpyHostToDevice);
    return err == cudaSuccess;
}

/**
 * @brief Copy memory from device to host
 * @param dst Destination host pointer
 * @param src Source device pointer
 * @param size Size in bytes
 * @return true on success, false on failure
 */
bool tablr_cuda_memcpy_d2h(void* dst, const void* src, size_t size) {
    cudaError_t err = cudaMemcpy(dst, src, size, cudaMemcpyDeviceToHost);
    return err == cudaSuccess;
}

/**
 * @brief Copy memory from device to device
 * @param dst Destination device pointer
 * @param src Source device pointer
 * @param size Size in bytes
 * @return true on success, false on failure
 */
bool tablr_cuda_memcpy_d2d(void* dst, const void* src, size_t size) {
    cudaError_t err = cudaMemcpy(dst, src, size, cudaMemcpyDeviceToDevice);
    return err == cudaSuccess;
}

/**
 * @brief CUDA kernel for element-wise addition (float32)
 */
__global__ void cuda_add_float32_kernel(float* result, const float* a, const float* b, size_t size) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        result[idx] = a[idx] + b[idx];
    }
}

/**
 * @brief CUDA kernel for element-wise multiplication (float32)
 */
__global__ void cuda_mul_float32_kernel(float* result, const float* a, const float* b, size_t size) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        result[idx] = a[idx] * b[idx];
    }
}

/**
 * @brief CUDA kernel for scalar multiplication (float32)
 */
__global__ void cuda_scale_float32_kernel(float* result, const float* a, float scalar, size_t size) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        result[idx] = a[idx] * scalar;
    }
}

/**
 * @brief Launch CUDA addition kernel
 * @param result Result device pointer
 * @param a First operand device pointer
 * @param b Second operand device pointer
 * @param size Number of elements
 * @return true on success, false on failure
 */
bool tablr_cuda_add_float32(float* result, const float* a, const float* b, size_t size) {
    int threads = 256;
    int blocks = (size + threads - 1) / threads;
    
    cuda_add_float32_kernel<<<blocks, threads>>>(result, a, b, size);
    
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        return false;
    }
    
    return tablr_cuda_synchronize();
}

/**
 * @brief Launch CUDA multiplication kernel
 * @param result Result device pointer
 * @param a First operand device pointer
 * @param b Second operand device pointer
 * @param size Number of elements
 * @return true on success, false on failure
 */
bool tablr_cuda_mul_float32(float* result, const float* a, const float* b, size_t size) {
    int threads = 256;
    int blocks = (size + threads - 1) / threads;
    
    cuda_mul_float32_kernel<<<blocks, threads>>>(result, a, b, size);
    
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        return false;
    }
    
    return tablr_cuda_synchronize();
}

/**
 * @brief Launch CUDA scalar multiplication kernel
 * @param result Result device pointer
 * @param a Input device pointer
 * @param scalar Scalar value
 * @param size Number of elements
 * @return true on success, false on failure
 */
bool tablr_cuda_scale_float32(float* result, const float* a, float scalar, size_t size) {
    int threads = 256;
    int blocks = (size + threads - 1) / threads;
    
    cuda_scale_float32_kernel<<<blocks, threads>>>(result, a, scalar, size);
    
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        return false;
    }
    
    return tablr_cuda_synchronize();
}
