#pragma once

#include <string>

namespace storage {
class Storage {
 public:
  // TODO: maybe change the file argument
  /**
   * Upload a file to the cloud storage service
   * @param file_path the path to the file to be uploaded
   * @return if the upload has been performed succesfully
   */
  virtual bool Upload(const std::string& file_path) const = 0;

  // TODO: maybe change the files argument
  /**
   * Download a file into the current machine from the cloud service
   * @param cloud_file_path the path of the file that needs to be downloaded
   * @param file_path path where to download the file
   * @return if the download has been perfomed succesfully
   */
  virtual bool Download(const std::string& cloud_file_path,
                        const std::string& file_path) const = 0;

  /**
   * Set the configuration of the cloud storage service
   * @param file_path the file from where it will get the configuration from
   * @return if the configuration has been performed succesfully
   */
  virtual bool SetConfiguration(const std::string& file_path) noexcept = 0;
};
}  // namespace storage
