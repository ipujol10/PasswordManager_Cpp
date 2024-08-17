#include <curl/curl.h>
#include <gtest/gtest.h>

#include <cloud_storage/google_drive.hpp>

TEST(GoogleDrive, UploadCorrect) {
  storage::GoogleDriveApi s;
  const std::string path = "";

  EXPECT_TRUE(s.Upload(path));
}
