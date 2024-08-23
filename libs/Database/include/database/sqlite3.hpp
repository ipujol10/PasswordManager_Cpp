#pragma once

#include <gtest/gtest.h>
#include <sqlite3.h>

#include <map>

#include "database.hpp"

namespace db {
class SQLite3API : public Database {
  sqlite3 *db_;
  const std::string file_path_;
  const std::map<std::string, std::map<std::string, ColumnType>> tables_;
  const std::map<std::string, std::vector<ColumnType>> columns_;

  /**
   * @brief generate the columns_ member
   * @param tables tables information
   * @return the generated columns_
   */
  std::map<std::string, std::vector<ColumnType>> GenerateColumns(
      const std::vector<
          std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>
          &tables) const noexcept;

  /**
   * @brief generate the tables_ member
   * @param tables tables information
   * @return the generated tables_
   */
  std::map<std::string, std::map<std::string, ColumnType>> GenerateTables(
      const std::vector<
          std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>
          &tables) const noexcept;

  /**
   * @brief Generate the query to SELECT data
   * @param columns the columns from where to take the data - use * to get data from all
   * columns
   * @param table name of the table to get the data from
   * @return the string to select the data
   */
  std::string GenerateQuery(const std::vector<std::string> &columns,
                            const std::string &table) noexcept;

  /**
   * @brief Check if the table and columns are valid
   * @param columns a list of the columns to Query
   * @param table the table from where to Query
   * @return if the columns and table are correct
   */
  bool IsValidQuery(const std::vector<std::string> &columns,
                    const std::string &table) noexcept;

  /**
   * @brief Get the ColumnData object from the current stament at the given index
   * @param statement the sqlite3 statment pointer
   * @param idx the index in the row
   * @param type the type of value to extract
   * @return The built object with the given data
   */
  ColumnData GetColumnDataIdx(sqlite3_stmt *statement, int idx,
                              const ColumnType &type) const noexcept;

 public:
  /**
   * @brief provide the path to the database file
   * @param file_path the path to the file
   */
  SQLite3API(const std::string &file_path,
             const std::vector<
                 std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>
                 &tables) noexcept;

  /**
   * @brief Connect to a SQLite3 database
   * @return if it has been able to connect succesfully
   */
  bool Connect() noexcept override;

  /**
   * @brief Disconnect from the SQLite3 database
   * @return if it has been able to disconnect succesfully
   */
  bool Disconnect() noexcept override;

  /**
   * @brief Obtain the data from the database
   * @param columns the columns from where to take the data - use * to get data from all
   * columns
   * @param table name of the table to get the data from
   * @return a list of rows where each row has the elements of the query
   */
  std::vector<std::vector<ColumnData>> Select(const std::vector<std::string> &columns,
                                              const std::string &table) noexcept override;

  FRIEND_TEST(SQLite3Test_Create, Normal);
  FRIEND_TEST(SQLite3Test_GenerateQuery, GetData);
};
}  // namespace db
