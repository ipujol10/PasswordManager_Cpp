#include "database/database.hpp"

namespace db {
Database::Database() noexcept : connected_(false), error_(ErrorStatus::Ok) {}

ErrorStatus Database::GetError() const noexcept { return error_; }

bool Database::IsConnected() const noexcept { return connected_; }
}  // namespace db
