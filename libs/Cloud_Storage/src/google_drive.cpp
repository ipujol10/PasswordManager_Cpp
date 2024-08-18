#include "cloud_storage/google_drive.hpp"

namespace storage {
bool GoogleDriveApi::Upload(const std::string& file_path) { throw "Not implemented"; }

bool GoogleDriveApi::Download(const std::string& cloud_file_path,
                              const std::string& file_path) {
  throw "Not implemented";
}

bool GoogleDriveApi::SetConfiguration(const std::string& file_path) {
  throw "Not implemented";
}
}  // namespace storage
