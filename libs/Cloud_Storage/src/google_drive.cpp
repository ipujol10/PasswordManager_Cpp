#include "cloud_storage/google_drive.hpp"

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
  return true;
}
}  // namespace storage
