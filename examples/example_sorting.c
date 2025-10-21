/**
 * @file example_sorting.c
 * @brief Sorting operations example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

/**
 * @brief Main function demonstrating sorting operations
 * @return Exit code (0 for success)
 */
int main(void) {
    printf("Tablr Sorting Example\n\n");
    
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create unsorted data */
    int ages[] = {35, 25, 45, 30, 40};
    float salaries[] = {70000.0f, 50000.0f, 90000.0f, 60000.0f, 80000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 5, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 5, TABLR_FLOAT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    printf("Original DataFrame:\n");
    tablr_dataframe_print(df);
    
    /* Sort by age ascending */
    printf("\nSorted by Age (ascending):\n");
    TablrDataFrame* sorted_asc = tablr_dataframe_sort(df, "Age", true);
    tablr_dataframe_print(sorted_asc);
    
    /* Sort by salary descending */
    printf("\nSorted by Salary (descending):\n");
    TablrDataFrame* sorted_desc = tablr_dataframe_sort(df, "Salary", false);
    tablr_dataframe_print(sorted_desc);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    tablr_dataframe_free(sorted_asc);
    tablr_dataframe_free(sorted_desc);
    
    return 0;
}
