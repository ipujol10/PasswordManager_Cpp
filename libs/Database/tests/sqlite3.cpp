#include <gtest/gtest.h>

#include <database/sqlite3.hpp>
#include <filesystem>

// Friend tests
namespace db {
TEST(SQLite3Test_Create, Normal) {
  const std::string file_path = "libs/Database/tests/data/connect_existing.db";
  const std::vector<
      std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>
      tables = {
          {"table1",
           {{"ID", ColumnType::Integer},
           {"str", ColumnType::Text},
           {"num", ColumnType::Double}}             },
          {"table2", {{"test", ColumnType::Integer}}}
  };
  SQLite3API db(file_path, tables);

  EXPECT_EQ(db.db_, nullptr);
  EXPECT_EQ(db.file_path_, file_path);
  EXPECT_EQ(db.error_, ErrorStatus::Ok);
  EXPECT_FALSE(db.connected_);

  const std::vector<ColumnType> table1_types = {ColumnType::Integer, ColumnType::Text,
                                                ColumnType::Double};
  for (int i = 0; i < table1_types.size(); ++i) {
    EXPECT_EQ(db.columns_.at("table1")[i], table1_types[i]);
  }
  EXPECT_EQ(db.columns_.at("table2").front(), ColumnType::Integer);

  const std::map<std::string, ColumnType> table1_map_types = {
      { "ID", ColumnType::Integer},
      {"str",    ColumnType::Text},
      {"num",  ColumnType::Double}
  };
  for (const auto& [table, value] : db.tables_) {
    EXPECT_TRUE(table == "table1" || table == "table2");
    for (const auto& [key, value] : db.tables_.at(table)) {
      if (table == "table1") {
        EXPECT_TRUE(table1_map_types.contains(key));
        EXPECT_EQ(value, table1_map_types.at(key));
      } else {
        EXPECT_EQ(key, "test");
        EXPECT_EQ(value, ColumnType::Integer);
      }
    }
  }
}

TEST(SQLite3Test_GenerateQuery, GetData) {
  SQLite3API db("test.db", {});
  EXPECT_EQ(db.GenerateQuery({"test1", "test2"}, "table_test"),
            "SELECT test1, test2 FROM table_test;")
      << "Failed on correct test 1";

  EXPECT_EQ(db.GenerateQuery({"*"}, "table_test"), "SELECT * FROM table_test;")
      << "Failed on correct test 2";

  EXPECT_EQ(db.GenerateQuery({}, "table_test"), "SELECT * FROM table_test;")
      << "Failed on correct test 3";

  EXPECT_EQ(db.GenerateQuery({"*", "test1"}, "table_test"), "")
      << "Failed on incorrect test 4";
  EXPECT_EQ(db.GetError(), ErrorStatus::NoWildcardAlone);

  EXPECT_EQ(db.GenerateQuery({"test1", "*"}, "table_test"), "")
      << "Failed on incorrect test 5";
  EXPECT_EQ(db.GetError(), ErrorStatus::NoWildcardAlone);

  EXPECT_EQ(db.GenerateQuery({"test1", "test2"}, ""), "") << "Failed on incorrect test 6";
  EXPECT_EQ(db.GetError(), ErrorStatus::InvalidTableName);
}
}  // namespace db

TEST(SQLite3Test_Connect, ExistingDatabase) {
  const std::string file_path = "libs/Database/tests/data/connect_existing.db";
  db::SQLite3API db(file_path, {});

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_FALSE(db.IsConnected());
  EXPECT_TRUE(db.Connect());
  EXPECT_TRUE(db.IsConnected());
}

TEST(SQLite3Test_Connect, NonExistingDatabase) {
  const std::string file_path = "libs/Database/tests/data/connect_not_existing.db";
  db::SQLite3API db(file_path, {});

  EXPECT_FALSE(std::filesystem::exists(file_path));
  EXPECT_FALSE(db.IsConnected());
  EXPECT_TRUE(db.Connect());
  EXPECT_TRUE(db.IsConnected());
  EXPECT_TRUE(std::filesystem::exists(file_path));
  std::filesystem::remove(file_path);
  EXPECT_FALSE(std::filesystem::exists(file_path));
}

TEST(SQLite3Test_Connect, Disconnect) {
  const std::string file_path = "libs/Database/tests/data/connect_existing.db";
  db::SQLite3API db(file_path, {});

  EXPECT_TRUE(std::filesystem::exists(file_path));
  EXPECT_FALSE(db.IsConnected());
  EXPECT_TRUE(db.Connect());
  EXPECT_TRUE(db.IsConnected());
  EXPECT_TRUE(db.Disconnect());
  EXPECT_FALSE(db.IsConnected());
}

TEST(SQLite3Test_Select, Table1_all) {
  const std::string file_path = "libs/Database/tests/data/test.db";
  const std::vector<
      std::pair<std::string, std::vector<std::pair<std::string, db::ColumnType>>>>
      tables = {
          {"table1",
           {{"ID", db::ColumnType::Integer},
           {"str", db::ColumnType::Text},
           {"num", db::ColumnType::Double}}             },
          {"table2", {{"test", db::ColumnType::Integer}}}
  };
  db::SQLite3API db(file_path, tables);
  EXPECT_TRUE(db.Connect());

  std::vector<std::vector<db::ColumnData>> compare_table_1 = {
      {db::ColumnData(1), db::ColumnData("Test1"), db::ColumnData(3.1415)},
      {db::ColumnData(2), db::ColumnData("false"),    db::ColumnData(0.0)}
  };
  auto result_table_1 = db.Select({"ID", "str", "num"}, "table1");
  auto result_table_1_2 = db.Select({}, "table1");
  ASSERT_NE(result_table_1.size(), 0) << "Result empty";
  ASSERT_NE(result_table_1.front().size(), 0) << "Row empty";
  ASSERT_NE(result_table_1_2.size(), 0) << "Result empty";
  ASSERT_NE(result_table_1_2.front().size(), 0) << "Row empty";
  for (int i = 0; i < result_table_1.size(); ++i) {
    for (int j = 0; j < result_table_1[i].size(); ++j) {
      EXPECT_EQ(result_table_1[i][j], compare_table_1[i][j])
          << "Failed on row " << i << " element " << j;
      EXPECT_EQ(result_table_1_2[i][j], compare_table_1[i][j])
          << "Failed on row " << i << " element " << j;
    }
  }

  EXPECT_TRUE(db.Disconnect());
}

TEST(SQLite3Test_Select, Table1_num) {
  const std::string file_path = "libs/Database/tests/data/test.db";
  const std::vector<
      std::pair<std::string, std::vector<std::pair<std::string, db::ColumnType>>>>
      tables = {
          {"table1",
           {{"ID", db::ColumnType::Integer},
           {"str", db::ColumnType::Text},
           {"num", db::ColumnType::Double}}             },
          {"table2", {{"test", db::ColumnType::Integer}}}
  };
  db::SQLite3API db(file_path, tables);
  EXPECT_TRUE(db.Connect());

  std::vector<std::vector<db::ColumnData>> compare_table_1 = {{db::ColumnData(3.1415)},
                                                              {db::ColumnData(0.0)}};
  auto result_table_1 = db.Select({"num"}, "table1");
  ASSERT_NE(result_table_1.size(), 0) << "Result empty";
  ASSERT_NE(result_table_1.front().size(), 0) << "Row empty";
  for (int i = 0; i < result_table_1.size(); ++i) {
    for (int j = 0; j < result_table_1[i].size(); ++j) {
      EXPECT_EQ(result_table_1[i][j], compare_table_1[i][j])
          << "Failed on row " << i << " element " << j;
    }
  }

  EXPECT_TRUE(db.Disconnect());
}

TEST(SQLite3Test_Select, Table2_all) {
  const std::string file_path = "libs/Database/tests/data/test.db";
  const std::vector<
      std::pair<std::string, std::vector<std::pair<std::string, db::ColumnType>>>>
      tables = {
          {"table1",
           {{"ID", db::ColumnType::Integer},
           {"str", db::ColumnType::Text},
           {"num", db::ColumnType::Double}}             },
          {"table2", {{"test", db::ColumnType::Integer}}}
  };
  db::SQLite3API db(file_path, tables);
  EXPECT_TRUE(db.Connect());

  std::vector<std::vector<db::ColumnData>> compare_table_2 = {{db::ColumnData(1)}};
  auto result_table_2 = db.Select({"test"}, "table2");
  ASSERT_NE(result_table_2.size(), 0) << "Result empty";
  ASSERT_NE(result_table_2.front().size(), 0) << "Row empty";
  for (int i = 0; i < result_table_2.size(); ++i) {
    for (int j = 0; j < result_table_2[i].size(); ++j) {
      EXPECT_EQ(result_table_2[i][j], compare_table_2[i][j])
          << "Failed on row " << i << " element " << j;
    }
  }
  EXPECT_TRUE(db.Disconnect());
}

TEST(SQLite3Test_Select, Bad) {
  const std::string file_path = "libs/Database/tests/data/test.db";
  const std::vector<
      std::pair<std::string, std::vector<std::pair<std::string, db::ColumnType>>>>
      tables = {
          {"table1",
           {{"ID", db::ColumnType::Integer},
           {"str", db::ColumnType::Text},
           {"num", db::ColumnType::Double}}             },
          {"table2", {{"test", db::ColumnType::Integer}}}
  };
  db::SQLite3API db(file_path, tables);

  EXPECT_EQ(db.Select({}, "").size(), 0) << "Database not connected";
  EXPECT_EQ(db.GetError(), db::ErrorStatus::NotConnected);

  EXPECT_TRUE(db.Connect());

  EXPECT_EQ(db.Select({"id"}, "table1").size(), 0) << "With a bad column name";
  EXPECT_EQ(db.GetError(), db::ErrorStatus::InvalidColumnName);

  EXPECT_EQ(db.Select({"id", "str", "num"}, "table1").size(), 0)
      << "With a bad column name";
  EXPECT_EQ(db.GetError(), db::ErrorStatus::InvalidColumnName);

  EXPECT_EQ(db.Select({"ID"}, "tablet1").size(), 0) << "With bad table name";
  EXPECT_EQ(db.GetError(), db::ErrorStatus::InvalidTableName);

  EXPECT_EQ(db.Select({}, "").size(), 0) << "With bad table name";
  EXPECT_EQ(db.GetError(), db::ErrorStatus::InvalidTableName);

  EXPECT_TRUE(db.Disconnect());
}
