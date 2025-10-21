/**
 * @file example_filtering.c
 * @brief Filtering and selection example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

/**
 * @brief Filter predicate to keep rows where age >= 30
 * @param row Row index
 * @param ctx Context pointer (DataFrame)
 * @return true to keep row, false to exclude
 */
bool age_filter(size_t row, void* ctx) {
    TablrDataFrame* df = (TablrDataFrame*)ctx;
    TablrSeries* age_col = tablr_dataframe_get_column(df, "Age");
    int* ages = (int*)tablr_series_data(age_col);
    return ages[row] >= 30;
}

/**
 * @brief Main function demonstrating filtering operations
 * @return Exit code (0 for success)
 */
int main(void) {
    printf("Tablr Filtering Example\n\n");
    
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create data */
    int ages[] = {25, 30, 35, 40, 45};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f, 90000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 5, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 5, TABLR_FLOAT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    printf("Original DataFrame:\n");
    tablr_dataframe_print(df);
    
    /* Filter rows where age >= 30 */
    printf("\nFiltered (Age >= 30):\n");
    TablrDataFrame* filtered = tablr_dataframe_filter(df, age_filter, df);
    tablr_dataframe_print(filtered);
    
    /* Select specific rows */
    printf("\nSelected rows [0, 2, 4]:\n");
    size_t indices[] = {0, 2, 4};
    TablrDataFrame* selected = tablr_dataframe_select_rows(df, indices, 3);
    tablr_dataframe_print(selected);
    
    /* Select specific columns */
    printf("\nSelected column 'Age':\n");
    const char* cols[] = {"Age"};
    TablrDataFrame* col_selected = tablr_dataframe_select_columns(df, cols, 1);
    tablr_dataframe_print(col_selected);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    tablr_dataframe_free(filtered);
    tablr_dataframe_free(selected);
    tablr_dataframe_free(col_selected);
    
    return 0;
}
