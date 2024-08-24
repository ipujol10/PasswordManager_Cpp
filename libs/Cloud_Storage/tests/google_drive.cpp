#include <curl/curl.h>
#include <gtest/gtest.h>

#include <cloud_storage/google_drive.hpp>
#include <filesystem>

TEST(GoogleDrive, ConfigureCorrectly) {
  storage::GoogleDriveApi s;
  const std::string path = "libs/Cloud_Storage/tests/data/test_settings.db";

  EXPECT_TRUE(s.SetConfiguration(path));
}
