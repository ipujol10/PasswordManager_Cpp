#include "database/database.hpp"

namespace db {
Database::Database() noexcept : connected_(false), error_(ErrorStatus::Ok) {}

ErrorStatus Database::GetError() const noexcept { return error_; }

bool Database::IsConnected() const noexcept { return connected_; }

ColumnData::ColumnData(int value) noexcept : type(ColumnType::Integer) {
  val.int_val = value;
}

ColumnData::ColumnData(float value) noexcept : type(ColumnType::Float) {
  val.float_val = value;
}

ColumnData::ColumnData(const std::string& value) noexcept : type(ColumnType::Text) {
  val.str_val = value.c_str();
}

int ColumnData::ToInt() const noexcept { return val.int_val; }

bool ColumnData::ToBool() const noexcept { return static_cast<bool>(val.int_val); }

float ColumnData::ToFloat() const noexcept { return val.float_val; }

std::string ColumnData::ToStr() const noexcept { return {val.str_val}; }

std::string ColumnData::GetString() const noexcept {
  switch (type) {
    case ColumnType::Integer:
      return std::to_string(val.int_val);
    case ColumnType::Float:
      return std::to_string(val.float_val);
    case ColumnType::Text:
      return {val.str_val};
    default:
      return "Unkown";
  }
}
}  // namespace db
