#include "widgets.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>

#include <cstring>
#include <string>

namespace widgets {
PasswordEntry::PasswordEntry(const std::string& name, const std::string& username, int w,
                             int h, const char* label)
    : Fl_Pack(0, 0, w, h, label),
      name_s_(CopyString(name)),
      username_s_(CopyString(username)) {
  type(Fl_Pack::HORIZONTAL);
  name_ = new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, 0, 0, w / 2, h, name_s_);
  username_ = new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, 0, 0, w / 2, h, username_s_);
  end();
}

PasswordEntry::~PasswordEntry() {
  delete name_;
  delete[] name_s_;
  delete username_;
  delete[] username_s_;
}

const char* PasswordEntry::CopyString(const std::string& str) const noexcept {
  char* name = new char[str.length() + 1];
  strcpy(name, str.c_str());
  return name;
}
}  // namespace widgets
