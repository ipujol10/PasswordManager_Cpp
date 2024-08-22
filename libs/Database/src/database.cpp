#include "database/database.hpp"

namespace db {
Database::Database() noexcept : connected_(false), error_(ErrorStatus::Ok) {}

ErrorStatus Database::GetError() const noexcept { return error_; }

bool Database::IsConnected() const noexcept { return connected_; }

ColumnData::ColumnData() noexcept : type(ColumnType::Null) {}

ColumnData::ColumnData(int value) noexcept : type(ColumnType::Integer) {
  val.int_val = value;
}

ColumnData::ColumnData(double value) noexcept : type(ColumnType::Double) {
  val.double_val = value;
}

ColumnData::ColumnData(const std::string& value) noexcept : type(ColumnType::Text) {
  val.str_val = value.c_str();
}

ColumnData::ColumnData(const unsigned char* value) noexcept : type(ColumnType::Text) {
  val.str_val = reinterpret_cast<const char*>(value);
}

int ColumnData::ToInt() const noexcept { return val.int_val; }

bool ColumnData::ToBool() const noexcept { return static_cast<bool>(val.int_val); }

double ColumnData::ToDouble() const noexcept { return val.double_val; }

std::string ColumnData::ToStr() const noexcept { return {val.str_val}; }

std::string ColumnData::GetString() const noexcept {
  switch (type) {
    case ColumnType::Integer:
      return std::to_string(val.int_val);
    case ColumnType::Double:
      return std::to_string(val.double_val);
    case ColumnType::Text:
      return {val.str_val};
    default:
      return "Unkown";
  }
}

bool ColumnData::operator==(const ColumnData& other) const noexcept {
  if (type != other.type) return false;
  switch (type) {
    case ColumnType::Integer:
      return val.int_val == other.val.int_val;
    case ColumnType::Double:
      return abs(val.double_val - other.val.double_val) < 1e-6;
    case ColumnType::Text:
      return val.str_val == other.val.str_val;
    default:
      return true;
  }
  return false;
}
}  // namespace db
