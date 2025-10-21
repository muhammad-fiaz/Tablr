/**
 * @file tablr.hpp
 * @brief C++ API for data manipulation
 * @author Muhammad Fiaz
 * @license Apache-2.0
 * 
 * This header provides modern C++ wrapper classes for the Tablr library,
 * offering RAII-style memory management and STL-compatible interfaces.
 * 
 * @example
 * @code
 * #include <tablr/tablr.hpp>
 * 
 * int main() {
 *     auto df = tablr::DataFrame::read_csv("data.csv");
 *     df.print();
 *     return 0;
 * }
 * @endcode
 */

#ifndef TABLR_HPP
#define TABLR_HPP

#include "tablr.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace tablr {

/**
 * @brief Series class for one-dimensional data
 * 
 * Provides a C++ wrapper around TablrSeries with automatic memory management.
 */
class Series {
    TablrSeries* series_;  /**< Internal series pointer */
public:
    /**
     * @brief Create series from vector
     * @tparam T Element type
     * @param data Vector of data
     */
    template<typename T>
    explicit Series(const std::vector<T>& data);
    
    /**
     * @brief Destructor - automatically frees series
     */
    ~Series();
    
    /**
     * @brief Get series size
     * @return Number of elements
     */
    size_t size() const;
    
    /**
     * @brief Get value at index
     * @tparam T Element type
     * @param idx Index position
     * @return Value at index
     */
    template<typename T>
    T at(size_t idx) const;
};

/**
 * @brief DataFrame class for two-dimensional tabular data
 * 
 * Provides a C++ wrapper around TablrDataFrame with automatic memory management
 * and modern C++ interfaces including lambda support for filtering.
 */
class DataFrame {
    TablrDataFrame* df_;  /**< Internal dataframe pointer */
public:
    /**
     * @brief Create empty dataframe
     */
    DataFrame();
    
    /**
     * @brief Destructor - automatically frees dataframe
     */
    ~DataFrame();
    
    /**
     * @brief Add column to dataframe
     * @param name Column name
     * @param series Series data
     */
    void add_column(const std::string& name, const Series& series);
    
    /**
     * @brief Get column by name
     * @param name Column name
     * @return Series containing column data
     */
    Series get_column(const std::string& name) const;
    
    /**
     * @brief Get number of rows
     * @return Row count
     */
    size_t nrows() const;
    
    /**
     * @brief Get number of columns
     * @return Column count
     */
    size_t ncols() const;
    
    /**
     * @brief Read CSV file into dataframe
     * @param filename Path to CSV file
     * @return DataFrame containing CSV data
     */
    static DataFrame read_csv(const std::string& filename);
    
    /**
     * @brief Write dataframe to CSV file
     * @param filename Output file path
     */
    void to_csv(const std::string& filename) const;
    
    /**
     * @brief Print dataframe to console
     */
    void print() const;
    
    /**
     * @brief Filter rows using predicate function
     * @param predicate Function returning true for rows to keep
     * @return Filtered dataframe
     */
    DataFrame filter(std::function<bool(size_t)> predicate) const;
    
    /**
     * @brief Group dataframe by column
     * @param column Column name to group by
     * @return Grouped dataframe
     */
    DataFrame groupby(const std::string& column) const;
    
    /**
     * @brief Sort dataframe by column
     * @param column Column name to sort by
     * @param ascending Sort order (true for ascending)
     * @return Sorted dataframe
     */
    DataFrame sort(const std::string& column, bool ascending = true) const;
    
    /**
     * @brief Merge with another dataframe
     * @param other DataFrame to merge with
     * @param on Column name to join on
     * @return Merged dataframe
     */
    DataFrame merge(const DataFrame& other, const std::string& on) const;
    
    /**
     * @brief Get descriptive statistics
     * @return DataFrame containing statistics
     */
    DataFrame describe() const;
};

} // namespace tablr

#endif /* TABLR_HPP */
