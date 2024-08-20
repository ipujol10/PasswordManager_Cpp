#pragma once

#include <sqlite3.h>

#include "database.hpp"

namespace db {
class SQLite3API : public Database {
  sqlite3 *db_;

 public:
  /**
   * @brief Connect to a SQLite3 database
   */
  bool Connect() noexcept override;

  /**
   * @brief Disconnect from the SQLite3 database
   */
  bool Disconnect() noexcept override;
};
}  // namespace db
