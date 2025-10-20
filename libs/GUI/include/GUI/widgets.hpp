#pragma once

#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>

#include <string>

namespace widgets {
class PasswordEntry : public Fl_Pack {
  Fl_Box* name_;
  Fl_Box* username_;
  const char *name_s_, *username_s_;

  const char* CopyString(const std::string& str) const noexcept;

 public:
  PasswordEntry(const std::string& name, const std::string& sername, int w, int h,
                const char* label = nullptr);
  ~PasswordEntry() override;
};
}  // namespace widgets
