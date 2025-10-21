/**
 * @file basic_usage.c
 * @brief Basic usage example of Tablr library
 */

#include <tablr/tablr.h>
#include <stdio.h>

int main(void) {
    printf("Tablr Basic Usage Example\n\n");
    
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create series */
    int ages[] = {25, 30, 35, 40};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 4, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 4, TABLR_FLOAT32, TABLR_CPU);
    
    /* Add columns */
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    /* Print dataframe */
    printf("DataFrame:\n");
    tablr_dataframe_print(df);
    
    printf("\nRows: %zu, Columns: %zu\n", 
           tablr_dataframe_nrows(df), 
           tablr_dataframe_ncols(df));
    
    /* Get head and tail */
    printf("\nFirst 2 rows:\n");
    TablrDataFrame* head = tablr_dataframe_head(df, 2);
    tablr_dataframe_print(head);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    tablr_dataframe_free(head);
    
    return 0;
}
