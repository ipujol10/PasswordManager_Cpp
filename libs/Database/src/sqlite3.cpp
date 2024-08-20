#include "database/sqlite3.hpp"

namespace db {
SQLite3API::SQLite3API(const std::string& file_path) noexcept
    : db_(nullptr), connected_(false), file_path_(std::move(file_path)) {}

bool SQLite3API::Connect() noexcept {
  int return_code = sqlite3_open(file_path_.c_str(), &db_);
  connected_ = return_code == SQLITE_OK;
  return connected_;
}

bool SQLite3API::Disconnect() noexcept {
  int return_code = sqlite3_close(db_);
  if (return_code == SQLITE_OK) {
    connected_ = false;
    db_ = nullptr;
    return true;
  }
  return false;
}

std::vector<std::vector<std::string>> SQLite3API::Select(
    const std::vector<std::string>& columns, const std::string& table) const noexcept {}

std::string SQLite3API::GenerateQuery(const std::vector<std::string>& columns,
                                      const std::string& table) const noexcept {
  if (table.length() == 0) return {};
  if (columns.size() == 0) return "SELECT * FROM " + table + ";";
  if (columns.back() == "*" && columns.size() != 1) return {};
  std::string out = "SELECT ";
  for (int i = 0; i < columns.size() - 1; ++i) {
    if (columns[i] == "*") return {};
    out += columns[i] + ", ";
  }
  return out + columns.back() + " FROM " + table + ";";
}
}  // namespace db
