#include "database/sqlite3.hpp"

namespace db {
SQLite3API::SQLite3API(const std::string& file_path) noexcept
    : db_(nullptr), file_path_(std::move(file_path)) {}

bool SQLite3API::Connect() noexcept {
  int return_code = sqlite3_open(file_path_.c_str(), &db_);
  if (!(connected_ = return_code == SQLITE_OK)) error_ = "Could not connect";
  error_ = "";
  return connected_;
}

bool SQLite3API::Disconnect() noexcept {
  int return_code = sqlite3_close(db_);
  if (return_code == SQLITE_OK) {
    connected_ = false;
    db_ = nullptr;
    error_ = "";
    return true;
  }
  error_ = "Could not disconnect";
  return false;
}

std::vector<std::vector<std::string>> SQLite3API::Select(
    const std::vector<std::string>& columns, const std::string& table) noexcept {
  if (!connected_) {
    error_ = "Not connected";
    return {};
  }
  const auto query = GenerateQuery(columns, table);
  if (query.empty()) return {};

  const char* error = nullptr;
  sqlite3_stmt* statement = nullptr;
  int return_code = sqlite3_prepare(db_, query.c_str(), -1, &statement, &error);
  if (return_code != SQLITE_OK) {
    error_ = "Invalid column name";
    return {};
  }

  std::vector<std::vector<std::string>> out;
  while ((return_code = sqlite3_step(statement)) == SQLITE_ROW) {
    std::vector<std::string> row;
    for (int i = 0; i < columns.size(); ++i) {
      auto val = sqlite3_column_type(statement, i);
      row.push_back(std::to_string(val));
    }
    out.push_back(row);
  }

  switch (return_code) {
    case SQLITE_BUSY:
      error_ = "Still busy";
      return {};
    case SQLITE_ERROR:
      error_ = "Run-time error";
      return {};
    case SQLITE_MISUSE:
      error_ = "Query misused";
      return {};
    default:
      break;
  }

  error_ = "";
  return out;
}

std::string SQLite3API::GenerateQuery(const std::vector<std::string>& columns,
                                      const std::string& table) noexcept {
  if (table.length() == 0) {
    error_ = "No table name";
    return {};
  }
  if (columns.size() == 0) {
    error_ = "";
    return "SELECT * FROM " + table + ";";
  }
  if (columns.back() == "*" && columns.size() != 1) {
    error_ = "* column with other names";
    return {};
  }
  std::string out = "SELECT ";
  for (int i = 0; i < columns.size() - 1; ++i) {
    if (columns[i] == "*") {
      error_ = "* column with other names";
      return {};
    }
    out += columns[i] + ", ";
  }
  error_ = "";
  return out + columns.back() + " FROM " + table + ";";
}
}  // namespace db
