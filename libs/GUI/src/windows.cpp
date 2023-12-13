#include "windows.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Secret_Input.H>
#include <cstring>

namespace window {
Fl_Group *password(int W, int H, const char *title) {
  Fl_Group *group = new Fl_Group(0, 0, W, H, title);
  int w = 300, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Secret_Input *password = new Fl_Secret_Input(x, y, w, h, "Password");
  Fl_Button *change = new Fl_Button(x, y + 50, 100, 25, "Change");
  change->user_data((void *)"button");
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

std::optional<Fl_Widget*> getWidget(Fl_Group *group, const char *user_data) {
  for (int i = 0; i < group->children(); i++) {
    Fl_Widget *child = group->child(i);
    auto data = child->user_data();
    if (data == (void *)0x0) {
      continue;
    }
    if (strcmp((char *)data, user_data) == 0) {
      return child;
    }
  }
  return {};
}

void go2window1(Fl_Widget *w, void *v) {}

void go2window2(Fl_Widget *w, void *v) {}
} // namespace window
