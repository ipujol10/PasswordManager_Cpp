#include "cloud_storage/google_drive.hpp"

#include <database/sqlite3.hpp>
#include <filesystem>

#include "google_drive.hpp"

namespace storage {
GoogleDriveApi::GoogleDriveApi() noexcept : configured_(false) {}

bool GoogleDriveApi::Upload(const std::string& file_path) const {
  throw "Not implemented";
}

bool GoogleDriveApi::Download(const std::string& cloud_file_path,
                              const std::string& file_path) const {
  throw "Not implemented";
}

bool GoogleDriveApi::SetConfiguration(const std::string& file_path) noexcept {
  if (!std::filesystem::exists(file_path)) return false;

  db::SQLite3API db(file_path, {
                                   {"data", {{"token", db::ColumnType::Text}}}
  });
  db.Connect();
  if (!db.IsConnected()) return false;
  const auto token = db.Select({"token"}, "data");
  if (token.size() != 1 || token.front().size() != 1) {
    db.Disconnect();
    return false;
  }

  token_ = token.front().front().ToStr();
  if (token_.empty()) {
    db.Disconnect();
    return false;
  }
  configured_ = true;
  db.Disconnect();
  return true;
}
}  // namespace storage
