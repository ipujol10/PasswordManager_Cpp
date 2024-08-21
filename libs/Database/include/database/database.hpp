#pragma once

#include <string>
#include <vector>

namespace db {
class Database {
 protected:
  std::string error_;

 public:
  Database() noexcept;

  /**
   * @brief Connect to a database
   */
  virtual bool Connect() noexcept = 0;

  /**
   * @brief Disconnect from the database
   */
  virtual bool Disconnect() noexcept = 0;

  /**
   * @brief Obtain the data from the database
   * @param columns the columns from where to take the data - use * to get data from all
   * columns
   * @param table name of the table to get the data from
   * @return a list of rows where each row has the elements of the query
   */
  virtual std::vector<std::vector<std::string>> Select(
      const std::vector<std::string>& columns, const std::string& table) noexcept = 0;

  /**
   * @brief Get the last error message
   */
  virtual std::string GetError() const noexcept = 0;
};
}  // namespace db
