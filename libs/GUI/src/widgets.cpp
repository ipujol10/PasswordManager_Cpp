#include "widgets.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Pack.H>
#include <string.h>  //NOLINT

#include <string>

namespace widgets {
PasswordEntry::PasswordEntry(const std::string& name, const std::string& username, int w,
                             int h, const char* label)
    : Fl_Pack(0, 0, w, h, label),
      name_s_(strdup(name.c_str())),
      username_s_(strdup(username.c_str())) {
  type(Fl_Pack::HORIZONTAL);
  name_ = new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, 0, 0, w / 2, h, name_s_);
  username_ = new Fl_Box(Fl_Boxtype::FL_BORDER_BOX, 0, 0, w / 2, h, username_s_);
  end();
}

PasswordEntry::~PasswordEntry() {
  delete name_;
  delete username_;
}
}  // namespace widgets
