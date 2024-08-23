#include "database/sqlite3.hpp"

namespace db {
SQLite3API::SQLite3API(
    const std::string& file_path,
    const std::vector<
        std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>&
        tables) noexcept
    : db_(nullptr),
      file_path_(std::move(file_path)),
      tables_(GenerateTables(tables)),
      columns_(GenerateColumns(tables)) {}

std::map<std::string, std::vector<ColumnType>> db::SQLite3API::GenerateColumns(
    const std::vector<
        std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>& tables)
    const noexcept {
  std::map<std::string, std::vector<ColumnType>> out;
  for (const auto& [table, columns_type] : tables) {
    std::vector<ColumnType> list;
    for (const auto& [column, type] : columns_type) { list.push_back(type); }
    out[table] = list;
  }
  return out;
}

std::map<std::string, std::map<std::string, ColumnType>> db::SQLite3API::GenerateTables(
    const std::vector<
        std::pair<std::string, std::vector<std::pair<std::string, ColumnType>>>>& tables)
    const noexcept {
  std::map<std::string, std::map<std::string, ColumnType>> out;
  for (const auto& [table, columns_type] : tables) {
    std::map<std::string, ColumnType> map;
    for (const auto& [column, type] : columns_type) { map[column] = type; }
    out[table] = map;
  }
  return out;
}

bool SQLite3API::Connect() noexcept {
  int return_code = sqlite3_open(file_path_.c_str(), &db_);
  if (!(connected_ = return_code == SQLITE_OK)) error_ = ErrorStatus::CouldNotConnect;
  error_ = ErrorStatus::Ok;
  return connected_;
}

bool SQLite3API::Disconnect() noexcept {
  int return_code = sqlite3_close(db_);
  if (return_code == SQLITE_OK) {
    connected_ = false;
    db_ = nullptr;
    error_ = ErrorStatus::Ok;
    return true;
  }
  error_ = ErrorStatus::CouldNotDisconnect;
  return false;
}

std::vector<std::vector<ColumnData>> SQLite3API::Select(
    const std::vector<std::string>& columns, const std::string& table) noexcept {
  if (!connected_) {
    error_ = ErrorStatus::NotConnected;
    return {};
  }

  if (!IsValidQuery(columns, table)) return {};

  const auto query = GenerateQuery(columns, table);
  if (query.empty()) return {};

  const char* error = nullptr;
  sqlite3_stmt* statement = nullptr;
  int return_code = sqlite3_prepare(db_, query.c_str(), -1, &statement, &error);
  if (return_code != SQLITE_OK) {
    error_ = ErrorStatus::CouldNotPrepare;
    return {};
  }

  const auto current_table = tables_.at(table);
  std::vector<std::vector<ColumnData>> out;
  while ((return_code = sqlite3_step(statement)) == SQLITE_ROW) {
    std::vector<ColumnData> row;
    if (columns.size() == 0 || columns.front() == "*") {
      for (int i = 0; i < columns_.at(table).size(); ++i) {
        row.push_back(GetColumnDataIdx(statement, i, columns_.at(table)[i]));
      }
    } else {
      for (int i = 0; i < columns.size(); ++i) {
        row.push_back(GetColumnDataIdx(statement, i, current_table.at(columns[i])));
      }
    }
    out.push_back(row);
  }
  sqlite3_finalize(statement);

  switch (return_code) {
    case SQLITE_BUSY:
      error_ = ErrorStatus::QueryBusy;
      return {};
    case SQLITE_ERROR:
      error_ = ErrorStatus::QueryRuntimeError;
      return {};
    case SQLITE_MISUSE:
      error_ = ErrorStatus::QueryMisused;
      return {};
    default:
      break;
  }

  error_ = ErrorStatus::Ok;
  return out;
}

std::string SQLite3API::GenerateQuery(const std::vector<std::string>& columns,
                                      const std::string& table) noexcept {
  if (table.empty()) {
    error_ = ErrorStatus::InvalidTableName;
    return {};
  }
  if (columns.size() == 0) {
    error_ = ErrorStatus::Ok;
    return "SELECT * FROM " + table + ";";
  }
  if (columns.back() == "*" && columns.size() != 1) {
    error_ = ErrorStatus::NoWildcardAlone;
    return {};
  }
  std::string out = "SELECT ";
  for (int i = 0; i < columns.size() - 1; ++i) {
    if (columns[i] == "*") {
      error_ = ErrorStatus::NoWildcardAlone;
      return {};
    }
    out += columns[i] + ", ";
  }
  error_ = ErrorStatus::Ok;
  return out + columns.back() + " FROM " + table + ";";
}

bool db::SQLite3API::IsValidQuery(const std::vector<std::string>& columns,
                                  const std::string& table) noexcept {
  if (!tables_.contains(table)) {
    error_ = ErrorStatus::InvalidTableName;
    return false;
  }

  if (columns.size() == 0 || (columns.size() == 1 && columns.front() == "*")) {
    error_ = ErrorStatus::Ok;
    return true;
  }

  const auto current = tables_.at(table);
  for (const auto& column : columns) {
    if (column == "*") {
      error_ = ErrorStatus::NoWildcardAlone;
      return false;
    }
    if (!current.contains(column)) {
      error_ = ErrorStatus::InvalidColumnName;
      return false;
    }
  }
  error_ = ErrorStatus::Ok;
  return true;
}

ColumnData db::SQLite3API::GetColumnDataIdx(sqlite3_stmt* statement, int idx,
                                            const ColumnType& type) const noexcept {
  switch (type) {
    case ColumnType::Integer:
      return ColumnData{sqlite3_column_int(statement, idx)};
    case ColumnType::Double:
      return ColumnData{sqlite3_column_double(statement, idx)};
    case ColumnType::Text:
      return ColumnData{sqlite3_column_text(statement, idx)};
    default:
      return {};
  }
}
}  // namespace db
