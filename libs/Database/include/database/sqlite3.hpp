#pragma once

#include <gtest/gtest.h>
#include <sqlite3.h>

#include "database.hpp"

namespace db {
class SQLite3API : public Database {
  sqlite3 *db_;
  const std::string file_path_;

  /**
   * @brief Generate the query to SELECT data
   * @param columns the columns from where to take the data - use * to get data from all
   * columns
   * @param table name of the table to get the data from
   * @return the string to select the data
   */
  std::string GenerateQuery(const std::vector<std::string> &columns,
                            const std::string &table) noexcept;

 public:
  /**
   * @brief provide the path to the database file
   * @param file_path the path to the file
   */
  SQLite3API(const std::string &file_path) noexcept;

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
