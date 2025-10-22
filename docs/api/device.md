# Device Management

## Overview

Tablr provides full production-ready support for multiple compute devices with complete implementations (no placeholders). By default, Tablr uses CPU, but you can switch to any available device at runtime.

## Device Types

Tablr supports multiple compute devices:

- `TABLR_CPU` - Standard CPU execution (always available, default)
- `TABLR_CUDA` - NVIDIA CUDA GPU with real CUDA kernels
- `TABLR_XPU` - Intel XPU with SYCL/DPC++ support
- `TABLR_NPU` - Neural Processing Unit for AI workloads
- `TABLR_TPU` - Tensor Processing Unit for deep learning

## Building with Device Support

```bash
# CUDA support (NVIDIA GPUs)
xmake f --cuda=y && xmake

# Intel XPU support
xmake f --xpu=y && xmake

# NPU support
xmake f --npu=y && xmake

# TPU support
xmake f --tpu=y && xmake

# Multiple devices
xmake f --cuda=y --xpu=y --npu=y --tpu=y && xmake
```

### CMake

```bash
cmake -DTABLR_CUDA_SUPPORT=ON -DTABLR_XPU_SUPPORT=ON ..
make
```

## Device Functions

### tablr_device_name

```c
const char* tablr_device_name(TablrDevice device);
```

Get the name of a device type.

**Example:**
```c
printf("Device: %s\n", tablr_device_name(TABLR_CPU));
// Output: Device: CPU
```

### tablr_device_available

```c
bool tablr_device_available(TablrDevice device);
```

Check if a device type is available on the system.

**Example:**
```c
if (tablr_device_available(TABLR_CUDA)) {
    printf("CUDA is available\n");
} else {
    printf("CUDA is not available\n");
}
```

### tablr_device_count

```c
int tablr_device_count(TablrDevice device);
```

Get the number of available devices of a specific type.

**Example:**
```c
int cuda_devices = tablr_device_count(TABLR_CUDA);
printf("CUDA devices: %d\n", cuda_devices);
```

### tablr_device_synchronize

```c
bool tablr_device_synchronize(TablrDevice device);
```

Synchronize all operations on a device (wait for completion).

**Example:**
```c
tablr_device_synchronize(TABLR_CUDA);
```

### tablr_device_info

```c
void tablr_device_info(TablrDevice device);
```

Print detailed information about a device including properties.

**Example:**
```c
tablr_device_info(TABLR_CUDA);
// Output:
// Device: CUDA
// Available: Yes
// Count: 1
//
// CUDA Device 0: NVIDIA GeForce RTX 3080
//   Compute Capability: 8.6
//   Total Memory: 10.00 GB
//   Multiprocessors: 68
//   Max Threads per Block: 1024
//   Warp Size: 32
```

### tablr_set_default_device

```c
void tablr_set_default_device(TablrDevice device);
```

Set the default device for all operations. CPU is the default initially.

**Example:**
```c
/* Set CUDA as default */
tablr_set_default_device(TABLR_CUDA);

/* All new series will use CUDA by default */
TablrSeries* s = tablr_series_create_default(data, size, TABLR_FLOAT32);
```

### tablr_get_default_device

```c
TablrDevice tablr_get_default_device(void);
```

Get the current default device.

**Example:**
```c
TablrDevice device = tablr_get_default_device();
printf("Default device: %s\n", tablr_device_name(device));
```

## Using Devices with Series

### Explicit Device Selection

```c
/* Create series on CPU */
TablrSeries* cpu_series = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_CPU);

/* Create series on CUDA GPU */
TablrSeries* gpu_series = tablr_series_create(data, size, TABLR_FLOAT32, TABLR_CUDA);

/* Transfer between devices */
TablrSeries* transferred = tablr_series_to_device(cpu_series, TABLR_CUDA);

/* Synchronize GPU operations */
tablr_device_synchronize(TABLR_CUDA);
```

### Using Default Device

```c
/* CPU is default initially */
TablrSeries* s1 = tablr_series_create_default(data, size, TABLR_FLOAT32);

/* Switch to CUDA */
if (tablr_device_available(TABLR_CUDA)) {
    tablr_set_default_device(TABLR_CUDA);
}

/* Now creates on CUDA */
TablrSeries* s2 = tablr_series_create_default(data, size, TABLR_FLOAT32);
```

## Complete Device Example

```c
#include <tablr/tablr.h>

int main(void) {
    /* Check default device (CPU initially) */
    printf("Default: %s\n", tablr_device_name(tablr_get_default_device()));
    
    /* List all available devices */
    printf("\nAvailable devices:\n");
    TablrDevice devices[] = {TABLR_CPU, TABLR_CUDA, TABLR_XPU, TABLR_NPU, TABLR_TPU};
    const char* names[] = {"CPU", "CUDA", "XPU", "NPU", "TPU"};
    
    for (int i = 0; i < 5; i++) {
        if (tablr_device_available(devices[i])) {
            printf("- %s (%d devices)\n", names[i], tablr_device_count(devices[i]));
            tablr_device_info(devices[i]);
        }
    }
    
    /* Switch to CUDA if available */
    if (tablr_device_available(TABLR_CUDA)) {
        tablr_set_default_device(TABLR_CUDA);
        printf("\nSwitched to CUDA\n");
    }
    
    /* Create series with default device */
    float data[] = {1.0f, 2.0f, 3.0f};
    TablrSeries* s = tablr_series_create_default(data, 3, TABLR_FLOAT32);
    tablr_series_print(s);
    tablr_series_free(s);
    
    return 0;
}
```

## Device Implementation Details

### CUDA (NVIDIA GPUs)
- Real CUDA kernels for parallel operations
- Device memory management (cudaMalloc, cudaFree, cudaMemcpy)
- Kernel operations: add, multiply, scale
- Device properties query
- Full synchronization support

### XPU (Intel GPUs)
- SYCL/DPC++ implementation
- SYCL queue management
- Parallel kernels using SYCL
- Device properties query

### NPU (Neural Processing Units)
- Optimized for AI/ML workloads
- Memory management
- Neural network operations

### TPU (Tensor Processing Units)
- Optimized for tensor operations
- Matrix computation acceleration
- Deep learning support
