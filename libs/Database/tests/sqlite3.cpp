#include <gtest/gtest.h>

#include <database/sqlite3.hpp>
#include <filesystem>

// Friend tests
namespace db {
TEST(SQLite3Test, CreateDatabase) {
  std::string file_path = "test.db";
  auto *db = new SQLite3API(file_path);

  EXPECT_EQ(db->db_, nullptr);
  EXPECT_EQ(db->file_path_, file_path);
  EXPECT_FALSE(db->connected_);

  delete db;
}
}  // namespace db

TEST(SQLite3Test, ConnectExistingDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_existing.db";
  auto *db = new db::SQLite3API(file_path);

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db->Connect());

  delete db;
}

TEST(SQLite3Test, ConnectNonExistingDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_not_existing.db";
  auto *db = new db::SQLite3API(file_path);

  EXPECT_FALSE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db->Connect());
  EXPECT_TRUE(std::filesystem::exists(file_path));
  std::filesystem::remove(file_path);
  EXPECT_FALSE(std::filesystem::exists(file_path));

  delete db;
}

TEST(SQLite3Test, DisconnectDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_existing.db";
  auto *db = new db::SQLite3API(file_path);

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db->Connect());
  EXPECT_TRUE(db->Disconnect());

  delete db;
}
