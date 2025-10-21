/**
 * @file example_cpp.cpp
 * @brief C++ API usage example for Tablr library
 * @author Muhammad Fiaz
 * @license Apache-2.0
 */

#include <tablr/tablr.hpp>
#include <iostream>

/**
 * @brief Main function demonstrating C++ API usage
 * @return Exit code (0 for success)
 */
int main() {
    std::cout << "Tablr C++ API Example\n\n";
    
    /* Create dataframe using C++ wrapper */
    tablr::DataFrame df;
    
    /* Create series data */
    std::vector<int> ages = {25, 30, 35, 40, 45};
    std::vector<float> salaries = {50000.0f, 60000.0f, 70000.0f, 80000.0f, 90000.0f};
    
    /* Add columns */
    tablr::Series age_series(ages);
    tablr::Series salary_series(salaries);
    
    df.add_column("Age", age_series);
    df.add_column("Salary", salary_series);
    
    /* Print dataframe */
    std::cout << "DataFrame:\n";
    df.print();
    
    /* Get dimensions */
    std::cout << "\nRows: " << df.nrows() << ", Columns: " << df.ncols() << "\n";
    
    /* Read from CSV */
    try {
        auto csv_df = tablr::DataFrame::read_csv("data.csv");
        std::cout << "\nLoaded from CSV:\n";
        csv_df.print();
    } catch (...) {
        std::cout << "\nNo CSV file found (expected)\n";
    }
    
    return 0;
}
