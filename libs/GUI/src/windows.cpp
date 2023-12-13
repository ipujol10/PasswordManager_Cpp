#include "windows.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Secret_Input.H>

namespace window {
Fl_Group *password(int W, int H, const char *title) {
  Fl_Group *group = new Fl_Group(0, 0, W, H, title);
  int w = 300, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Secret_Input *password = new Fl_Secret_Input(x, y, w, h, "Password");
  Fl_Button *change = new Fl_Button(x, y + 50, 100, 25, "Change");
  change->user_data((void *)"button");
  password->user_data((void *)"");
  group->end();
  return group;
}

Fl_Group *password2(int W, int H, const char *title) {
  Fl_Group *group = new Fl_Group(0, 0, W, H, title);
  int w = 100, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Button *change = new Fl_Button(x, y, w, h, "Change");
  group->user_data((void *)"button");
  group->end();
  return group;
}
} // namespace window
