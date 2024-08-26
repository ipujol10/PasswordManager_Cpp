#include "cloud_storage/google_drive.hpp"

#include <curl/curl.h>

#include <database/sqlite3.hpp>
#include <filesystem>
#include <fstream>

#include "google_drive.hpp"

namespace storage {
GoogleDriveApi::GoogleDriveApi() noexcept : configured_(false) {}

bool GoogleDriveApi::Upload(const std::string& file_path) const {
  throw "Not implemented";
}

bool GoogleDriveApi::Download(const std::string& cloud_file_path,
                              const std::string& file_path) const {
  CURL* curl;
  CURLcode res;
  const std::string file_url = GetFileUrlDownload(cloud_file_path, token_);

  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, file_url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

    std::string file_contents;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file_contents);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      curl_easy_cleanup(curl);
      curl_global_cleanup();
      return false;
    }
    std::ofstream output_file(file_path);
    output_file << file_contents;
    output_file.close();
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return curl;
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

std::string storage::GoogleDriveApi::GetFileUrlDownload(
    const std::string& file_id, const std::string& access_token) const noexcept {
  return "https://www.googleapis.com/drive/v3/files/" + file_id +
         "?alt=media&access_token=" + access_token;
}

size_t storage::GoogleDriveApi::WriteMemoryCallback(void* contents, size_t size,
                                                    size_t nmemb,
                                                    std::string* data) noexcept {
  data->append(static_cast<char*>(contents), size * nmemb);
  return size * nmemb;
}
}  // namespace storage
