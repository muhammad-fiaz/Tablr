/**
 * @file test_tablr.c
 * @brief Unit tests for Tablr library
 */

#include "tablr/tablr.h"
#include <stdio.h>
#include <assert.h>

void test_series_create(void) {
    int data[] = {1, 2, 3, 4, 5};
    TablrSeries* s = tablr_series_create(data, 5, TABLR_INT32, TABLR_CPU);
    assert(s != NULL);
    assert(tablr_series_size(s) == 5);
    tablr_series_free(s);
    printf("✓ test_series_create passed\n");
}

void test_series_zeros(void) {
    TablrSeries* s = tablr_series_zeros(10, TABLR_FLOAT32, TABLR_CPU);
    assert(s != NULL);
    assert(tablr_series_size(s) == 10);
    tablr_series_free(s);
    printf("✓ test_series_zeros passed\n");
}

void test_dataframe_create(void) {
    TablrDataFrame* df = tablr_dataframe_create();
    assert(df != NULL);
    assert(tablr_dataframe_nrows(df) == 0);
    assert(tablr_dataframe_ncols(df) == 0);
    tablr_dataframe_free(df);
    printf("✓ test_dataframe_create passed\n");
}

void test_dataframe_add_column(void) {
    TablrDataFrame* df = tablr_dataframe_create();
    int data[] = {1, 2, 3};
    TablrSeries* s = tablr_series_create(data, 3, TABLR_INT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "col1", s);
    assert(tablr_dataframe_ncols(df) == 1);
    assert(tablr_dataframe_nrows(df) == 3);
    
    tablr_dataframe_free(df);
    printf("✓ test_dataframe_add_column passed\n");
}

void test_dataframe_get_column(void) {
    TablrDataFrame* df = tablr_dataframe_create();
    int data[] = {10, 20, 30};
    TablrSeries* s = tablr_series_create(data, 3, TABLR_INT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "numbers", s);
    TablrSeries* retrieved = tablr_dataframe_get_column(df, "numbers");
    
    assert(retrieved != NULL);
    assert(tablr_series_size(retrieved) == 3);
    (void)retrieved;
    
    tablr_dataframe_free(df);
    printf("✓ test_dataframe_get_column passed\n");
}

void test_dataframe_head_tail(void) {
    TablrDataFrame* df = tablr_dataframe_create();
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    TablrSeries* s = tablr_series_create(data, 10, TABLR_INT32, TABLR_CPU);
    tablr_dataframe_add_column(df, "numbers", s);
    
    TablrDataFrame* head = tablr_dataframe_head(df, 3);
    assert(tablr_dataframe_nrows(head) == 3);
    
    TablrDataFrame* tail = tablr_dataframe_tail(df, 3);
    assert(tablr_dataframe_nrows(tail) == 3);
    
    tablr_dataframe_free(df);
    tablr_dataframe_free(head);
    tablr_dataframe_free(tail);
    printf("✓ test_dataframe_head_tail passed\n");
}

int main(void) {
    printf("Running Tablr tests...\n\n");
    
    test_series_create();
    test_series_zeros();
    test_dataframe_create();
    test_dataframe_add_column();
    test_dataframe_get_column();
    test_dataframe_head_tail();
    
    printf("\n✓ All tests passed!\n");
    return 0;
}
