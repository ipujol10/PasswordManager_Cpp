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
}  // namespace db
