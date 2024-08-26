#include <curl/curl.h>
#include <gtest/gtest.h>

#include <cloud_storage/google_drive.hpp>
#include <filesystem>
#include <fstream>

TEST(GoogleDrive, ConfigureCorrectly) {
  storage::GoogleDriveApi s;
  const std::string path = "libs/Cloud_Storage/tests/data/test_settings.db";

  EXPECT_TRUE(std::filesystem::exists(path)) << "Settings file not found";
  EXPECT_TRUE(s.SetConfiguration(path)) << "Could not configure";
}

TEST(GoogleDrive_Connection, DownloadFile) {
  storage::GoogleDriveApi s;
  const std::string data_folder = "libs/Cloud_Storage/tests/data/";
  const std::string path = data_folder + "test_settings.db";
  ASSERT_TRUE(s.SetConfiguration(path));

  const std::string test_file = data_folder + "download_test.txt";
  EXPECT_FALSE(std::filesystem::exists(test_file));
  EXPECT_TRUE(s.Download("API_Test/download_test.txt", test_file));
  EXPECT_TRUE(std::filesystem::exists(test_file));

  std::string line;
  std::ifstream file(test_file);
  while (std::getline(file, line)) { EXPECT_EQ(line, "API Download Test"); }
  file.close();

  std::filesystem::remove(test_file);
  ASSERT_FALSE(std::filesystem::exists(test_file));
}
