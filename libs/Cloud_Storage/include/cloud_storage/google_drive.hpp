#pragma once

#include "storage.hpp"

namespace storage {
class GoogleDriveApi : public Storage {
 public:
  bool Upload(const std::string& file_path) override;

  bool Download(const std::string& cloud_file_path,
                const std::string& file_path) override;
};
}  // namespace storage
