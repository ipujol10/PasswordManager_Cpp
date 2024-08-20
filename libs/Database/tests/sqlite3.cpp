#include <gtest/gtest.h>

#include <database/sqlite3.hpp>
#include <filesystem>

// Friend tests
namespace db {
TEST(SQLite3Test, CreateDatabase) {
  std::string file_path = "test.db";
  SQLite3API db(file_path);

  EXPECT_EQ(db.db_, nullptr);
  EXPECT_EQ(db.file_path_, file_path);
  EXPECT_FALSE(db.connected_);
}

TEST(SQLite3Test, GenerateQuery_GetData) {
  SQLite3API db("test.db");
  EXPECT_EQ(db.GenerateQuery({"test1", "test2"}, "table_test"),
            "SELECT test1, test2 FROM table_test;");
  EXPECT_EQ(db.GenerateQuery({"*"}, "table_test"), "SELECT * FROM table_test;");
  EXPECT_EQ(db.GenerateQuery({}, "table_test"), "SELECT * FROM table_test;");
  EXPECT_EQ(db.GenerateQuery({"*", "test1"}, "table_test"), "");
  EXPECT_EQ(db.GenerateQuery({"test1", "*"}, "table_test"), "");
  EXPECT_EQ(db.GenerateQuery({"test1", "test2"}, ""), "");
}
}  // namespace db

TEST(SQLite3Test, ConnectExistingDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_existing.db";
  db::SQLite3API db(file_path);

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db.Connect());
}

TEST(SQLite3Test, ConnectNonExistingDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_not_existing.db";
  db::SQLite3API db(file_path);

  EXPECT_FALSE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db.Connect());
  EXPECT_TRUE(std::filesystem::exists(file_path));
  std::filesystem::remove(file_path);
  EXPECT_FALSE(std::filesystem::exists(file_path));
}

TEST(SQLite3Test, DisconnectDatabase) {
  std::string file_path = "libs/Database/tests/data/connect_existing.db";
  db::SQLite3API db(file_path);

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_TRUE(db.Connect());
  EXPECT_TRUE(db.Disconnect());
}
