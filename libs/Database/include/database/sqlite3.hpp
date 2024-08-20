#pragma once

#include <gtest/gtest.h>
#include <sqlite3.h>

#include "database.hpp"

namespace db {
class SQLite3API : public Database {
  sqlite3 *db_;
  bool connected_;
  const std::string file_path_;

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

  FRIEND_TEST(SQLite3Test, CreateDatabase);
};
}  // namespace db
