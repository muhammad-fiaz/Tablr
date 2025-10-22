/**
 * @file example_device_switching.c
 * @brief Device switching and default device example
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

int main(void) {
    printf("Tablr Device Switching Example\n\n");
    
    /* Check default device (CPU by default) */
    printf("Default device: %s\n\n", tablr_device_name(tablr_get_default_device()));
    
    /* Create data */
    float data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    
    /* Create series using default device (CPU) */
    printf("Creating series with default device:\n");
    TablrSeries* s1 = tablr_series_create_default(data, 5, TABLR_FLOAT32);
    tablr_series_print(s1);
    
    /* Create series explicitly on CPU */
    printf("\nCreating series explicitly on CPU:\n");
    TablrSeries* s2 = tablr_series_create(data, 5, TABLR_FLOAT32, TABLR_CPU);
    tablr_series_print(s2);
    
    /* Try to set CUDA as default if available */
    if (tablr_device_available(TABLR_CUDA)) {
        printf("\nCUDA is available! Setting as default device.\n");
        tablr_set_default_device(TABLR_CUDA);
        printf("New default device: %s\n\n", tablr_device_name(tablr_get_default_device()));
        
        /* Create series with new default (CUDA) */
        printf("Creating series with new default device:\n");
        TablrSeries* s3 = tablr_series_create_default(data, 5, TABLR_FLOAT32);
        tablr_series_print(s3);
        tablr_series_free(s3);
    } else {
        printf("\nCUDA not available. Build with: xmake f --cuda=y && xmake\n");
    }
    
    /* Transfer series between devices */
    printf("\nTransferring CPU series to CUDA:\n");
    TablrSeries* s_cuda = tablr_series_to_device(s1, TABLR_CUDA);
    tablr_series_print(s_cuda);
    
    /* Show all available devices */
    printf("\n=== Available Devices ===\n");
    TablrDevice devices[] = {TABLR_CPU, TABLR_CUDA, TABLR_XPU, TABLR_NPU, TABLR_TPU};
    const char* names[] = {"CPU", "CUDA", "XPU", "NPU", "TPU"};
    
    for (int i = 0; i < 5; i++) {
        printf("%s: %s (Count: %d)\n", 
               names[i],
               tablr_device_available(devices[i]) ? "Available" : "Not Available",
               tablr_device_count(devices[i]));
    }
    
    /* Detailed device info */
    printf("\n=== Detailed Device Information ===\n");
    for (int i = 0; i < 5; i++) {
        if (tablr_device_available(devices[i])) {
            tablr_device_info(devices[i]);
            printf("\n");
        }
    }
    
    /* Cleanup */
    tablr_series_free(s1);
    tablr_series_free(s2);
    tablr_series_free(s_cuda);
    
    printf("Build options:\n");
    printf("  CUDA: xmake f --cuda=y && xmake\n");
    printf("  XPU:  xmake f --xpu=y && xmake\n");
    printf("  NPU:  xmake f --npu=y && xmake\n");
    printf("  TPU:  xmake f --tpu=y && xmake\n");
    
    return 0;
}
