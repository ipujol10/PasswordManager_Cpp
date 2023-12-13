#pragma once

#include "FL/Fl_Widget.H"
#include <FL/Fl_Group.H>
#include <optional>

namespace window {
Fl_Group *password(int W, int H, const char *title);
Fl_Group *password2(int W, int H, const char *title);
std::optional<Fl_Widget*> getWidget(Fl_Group *group, const char *user_data);
void go2window1(Fl_Widget *w, void *v);
void go2window2(Fl_Widget *w, void *v);
} // namespace window
