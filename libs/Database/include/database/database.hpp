#pragma once

#include <string>
#include <vector>

namespace db {
enum ErrorStatus {
  Ok = 0,
  CouldNotConnect,
  CouldNotDisconnect,
  NotConnected,
  InvalidColumnName,
  InvalidTableName,
  QueryBusy,
  QueryRuntimeError,
  QueryMisused,
  NoTableName,
  NoWildcardAlone,
};

enum ColumnType {
  Integer = 1,
  Float,
  Text,
  Blob,
  Null
};

struct ColumnData {
  ColumnType type;
  union {
    int int_val;
    float float_val;
    const char* str_val;
  } val;

  ColumnData(int value) noexcept;

  ColumnData(float value) noexcept;

  ColumnData(const std::string& value) noexcept;

  int ToInt() const noexcept;

  bool ToBool() const noexcept;

  float ToFloat() const noexcept;

  std::string ToStr() const noexcept;

  std::string GetString() const noexcept;
};

class Database {
 protected:
  bool connected_;
  ErrorStatus error_;

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
  ErrorStatus GetError() const noexcept;

  /**
   * @brief Check if the dtatabase is connected
   */
  bool IsConnected() const noexcept;
};
}  // namespace db
