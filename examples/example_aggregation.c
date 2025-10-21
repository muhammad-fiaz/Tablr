/**
 * @file example_aggregation.c
 * @brief Grouping and aggregation example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

/**
 * @brief Main function demonstrating aggregation operations
 * @return Exit code (0 for success)
 */
int main(void) {
    printf("Tablr Aggregation Example\n\n");
    
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create sample data */
    int ages[] = {25, 30, 35, 40, 45, 50, 55, 60};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f, 
                        90000.0f, 100000.0f, 110000.0f, 120000.0f};
    
    TablrSeries* age_series = tablr_series_create(ages, 8, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 8, TABLR_FLOAT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    printf("Original DataFrame:\n");
    tablr_dataframe_print(df);
    
    /* Get descriptive statistics */
    printf("\nDescriptive Statistics:\n");
    TablrDataFrame* stats = tablr_dataframe_describe(df);
    tablr_dataframe_print(stats);
    
    /* Calculate mean salary */
    printf("\nMean Salary:\n");
    TablrDataFrame* mean_salary = tablr_dataframe_aggregate(df, "Salary", TABLR_AGG_MEAN);
    tablr_dataframe_print(mean_salary);
    
    /* Calculate sum of salaries */
    printf("\nTotal Salary:\n");
    TablrDataFrame* sum_salary = tablr_dataframe_aggregate(df, "Salary", TABLR_AGG_SUM);
    tablr_dataframe_print(sum_salary);
    
    /* Cleanup */
    tablr_dataframe_free(df);
    tablr_dataframe_free(stats);
    tablr_dataframe_free(mean_salary);
    tablr_dataframe_free(sum_salary);
    
    return 0;
}
