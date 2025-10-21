/**
 * @file example_csv.c
 * @brief CSV I/O operations example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.h>
#include <stdio.h>

/**
 * @brief Main function demonstrating CSV operations
 * @return Exit code (0 for success)
 */
int main(void) {
    printf("Tablr CSV I/O Example\n\n");
    
    /* Create dataframe */
    TablrDataFrame* df = tablr_dataframe_create();
    
    /* Create sample data */
    int ids[] = {1, 2, 3, 4, 5};
    int ages[] = {25, 30, 35, 40, 45};
    float salaries[] = {50000.0f, 60000.0f, 70000.0f, 80000.0f, 90000.0f};
    
    TablrSeries* id_series = tablr_series_create(ids, 5, TABLR_INT32, TABLR_CPU);
    TablrSeries* age_series = tablr_series_create(ages, 5, TABLR_INT32, TABLR_CPU);
    TablrSeries* salary_series = tablr_series_create(salaries, 5, TABLR_FLOAT32, TABLR_CPU);
    
    tablr_dataframe_add_column(df, "ID", id_series);
    tablr_dataframe_add_column(df, "Age", age_series);
    tablr_dataframe_add_column(df, "Salary", salary_series);
    
    printf("Original DataFrame:\n");
    tablr_dataframe_print(df);
    
    /* Write to CSV */
    printf("\nWriting to output.csv...\n");
    if (tablr_to_csv_default(df, "output.csv")) {
        printf("Successfully wrote to output.csv\n");
    } else {
        printf("Failed to write CSV\n");
    }
    
    /* Write with custom delimiter */
    printf("\nWriting to output.tsv (tab-separated)...\n");
    if (tablr_to_csv(df, "output.tsv", '\t', true)) {
        printf("Successfully wrote to output.tsv\n");
    }
    
    /* Read from CSV */
    printf("\nReading from output.csv...\n");
    TablrDataFrame* loaded = tablr_read_csv_default("output.csv");
    if (loaded) {
        printf("Loaded DataFrame:\n");
        tablr_dataframe_print(loaded);
        tablr_dataframe_free(loaded);
    } else {
        printf("Failed to read CSV\n");
    }
    
    /* Cleanup */
    tablr_dataframe_free(df);
    
    return 0;
}
