/**
 * @file example_device.c
 * @brief Multi-device support example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

/**
 * @brief Main function demonstrating multi-device operations
 * @return Exit code (0 for success)
 */
int main(void) {
    printf("Tablr Multi-Device Example\n\n");
    
    /* Create series on different devices */
    int data[] = {1, 2, 3, 4, 5};
    
    /* CPU execution */
    printf("Creating series on CPU...\n");
    TablrSeries* cpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_CPU);
    tablr_series_print(cpu_series);
    
    /* CUDA GPU (if available) */
    printf("\nCreating series on CUDA GPU...\n");
    TablrSeries* cuda_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_CUDA);
    tablr_series_print(cuda_series);
    
    /* Intel XPU (if available) */
    printf("\nCreating series on Intel XPU...\n");
    TablrSeries* xpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_XPU);
    tablr_series_print(xpu_series);
    
    /* Neural Processing Unit (if available) */
    printf("\nCreating series on NPU...\n");
    TablrSeries* npu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_NPU);
    tablr_series_print(npu_series);
    
    /* Tensor Processing Unit (if available) */
    printf("\nCreating series on TPU...\n");
    TablrSeries* tpu_series = tablr_series_create(data, 5, TABLR_INT32, TABLR_TPU);
    tablr_series_print(tpu_series);
    
    /* Transfer between devices */
    printf("\nTransferring CPU series to CUDA...\n");
    TablrSeries* transferred = tablr_series_to_device(cpu_series, TABLR_CUDA);
    tablr_series_print(transferred);
    
    /* Cleanup */
    tablr_series_free(cpu_series);
    tablr_series_free(cuda_series);
    tablr_series_free(xpu_series);
    tablr_series_free(npu_series);
    tablr_series_free(tpu_series);
    tablr_series_free(transferred);
    
    printf("\nNote: Device operations are placeholders.\n");
    printf("Actual GPU/XPU/NPU/TPU support requires hardware and drivers.\n");
    
    return 0;
}
