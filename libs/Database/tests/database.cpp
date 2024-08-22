#include <gtest/gtest.h>

#include <database/database.hpp>

TEST(DatabaseTest, ColumnData_Int) {
  db::ColumnData data(2);

  EXPECT_EQ(data.ToInt(), 2);
  EXPECT_EQ(data.GetString(), "2");
}

TEST(DatabaseTest, ColumnData_Bool) {
  db::ColumnData data0(0), data1(1), data2(2), data3(-1);

  EXPECT_FALSE(data0.ToBool());
  EXPECT_EQ(data0.GetString(), "0");

  EXPECT_TRUE(data1.ToBool());
  EXPECT_EQ(data1.GetString(), "1");

  EXPECT_TRUE(data2.ToBool());
  EXPECT_EQ(data2.GetString(), "2");

  EXPECT_TRUE(data3.ToBool());
  EXPECT_EQ(data3.GetString(), "-1");
}

TEST(DatabaseTest, ColumnData_Float) {
  db::ColumnData data(3.1415f);

  EXPECT_NEAR(data.ToFloat(), 3.1415, 0.0001);
  EXPECT_EQ(data.GetString(), "3.141500");
}

TEST(DatabaseTest, ColumnData_String) {
  db::ColumnData data("Test");

  EXPECT_EQ(data.ToStr(), "Test");
  EXPECT_EQ(data.GetString(), "Test");
}
