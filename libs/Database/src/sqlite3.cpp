#include "database/sqlite3.hpp"

namespace db {
SQLite3API::SQLite3API(const std::string& file_path) noexcept
    : db_(nullptr), file_path_(std::move(file_path)) {}

bool SQLite3API::Connect() noexcept {
  int return_code = sqlite3_open(file_path_.c_str(), &db_);
  if (!(connected_ = return_code == SQLITE_OK)) error_ = ErrorStatus::CouldNotConnect;
  error_ = ErrorStatus::Ok;
  return connected_;
}

bool SQLite3API::Disconnect() noexcept {
  int return_code = sqlite3_close(db_);
  if (return_code == SQLITE_OK) {
    connected_ = false;
    db_ = nullptr;
    error_ = ErrorStatus::Ok;
    return true;
  }
  error_ = ErrorStatus::CouldNotDisconnect;
  return false;
}

std::vector<std::vector<ColumnData>> SQLite3API::Select(
    const std::vector<std::string>& columns, const std::string& table) noexcept {
  if (!connected_) {
    error_ = ErrorStatus::NotConnected;
    return {};
  }
  const auto query = GenerateQuery(columns, table);
  if (query.empty()) return {};

  const char* error = nullptr;
  sqlite3_stmt* statement = nullptr;
  int return_code = sqlite3_prepare(db_, query.c_str(), -1, &statement, &error);
  if (return_code != SQLITE_OK) {
    error_ = ErrorStatus::InvalidColumnTableName;
    return {};
  }

  std::vector<std::vector<ColumnData>> out;
  while ((return_code = sqlite3_step(statement)) == SQLITE_ROW) {
    std::vector<ColumnData> row;
    int num_columns = (columns.size() == 0 || columns.front() == "*")
                          ? sqlite3_column_count(statement)
                          : columns.size();
    for (int i = 0; i < num_columns; ++i) {
      int value_type = sqlite3_column_type(statement, i);
      switch (value_type) {
        case ColumnType::Integer:
          row.emplace_back(sqlite3_column_int(statement, i));
          break;
        case ColumnType::Double:
          row.emplace_back(sqlite3_column_double(statement, i));
          break;
        case ColumnType::Text:
          row.emplace_back(sqlite3_column_text(statement, i));
          break;
        default:
          row.emplace_back();
          break;
      }
    }
    out.push_back(row);
  }
  sqlite3_finalize(statement);

  switch (return_code) {
    case SQLITE_BUSY:
      error_ = ErrorStatus::QueryBusy;
      return {};
    case SQLITE_ERROR:
      error_ = ErrorStatus::QueryRuntimeError;
      return {};
    case SQLITE_MISUSE:
      error_ = ErrorStatus::QueryMisused;
      return {};
    default:
      break;
  }

  error_ = ErrorStatus::Ok;
  return out;
}

std::string SQLite3API::GenerateQuery(const std::vector<std::string>& columns,
                                      const std::string& table) noexcept {
  if (table.empty()) {
    error_ = ErrorStatus::NoTableName;
    return {};
  }
  if (columns.size() == 0) {
    error_ = ErrorStatus::Ok;
    return "SELECT * FROM " + table + ";";
  }
  if (columns.back() == "*" && columns.size() != 1) {
    error_ = ErrorStatus::NoWildcardAlone;
    return {};
  }
  std::string out = "SELECT ";
  for (int i = 0; i < columns.size() - 1; ++i) {
    if (columns[i] == "*") {
      error_ = ErrorStatus::NoWildcardAlone;
      return {};
    }
    out += columns[i] + ", ";
  }
  error_ = ErrorStatus::Ok;
  return out + columns.back() + " FROM " + table + ";";
}
}  // namespace db
