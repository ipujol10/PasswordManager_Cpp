#pragma once

#include "storage.hpp"

namespace storage {
class GoogleDriveApi : public Storage {
 public:
  /**
   * Upload a file to Google Drive
   * @param file_path the path to the file to be uploaded
   * @return if the upload has been performed succesfully
   */
  bool Upload(const std::string& file_path) override;

  /**
   * Download a file into the current machine from Google Drive
   * @param cloud_file_path the path of the file that needs to be downloaded
   * @param file_path path where to download the file
   * @return if the download has been perfomed succesfully
   */
  bool Download(const std::string& cloud_file_path,
                const std::string& file_path) override;

  /**
   * Set the configuration for Google Drive
   * @param file_path the file from where it will get the configuration from
   * @return if the configuration has been performed succesfully
   */
  bool SetConfiguration(const std::string& file_path) override;
};
}  // namespace storage
