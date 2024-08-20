#pragma once

#include <string>

namespace db {
class Database {
 public:
  /**
   * @brief Connect to a database
   */
  virtual bool Connect() noexcept;

  /**
   * @brief Disconnect from the database
   */
  virtual bool Disconnect() noexcept;
};
}  // namespace db
