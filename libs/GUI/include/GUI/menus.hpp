#pragma once

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Widget.H>

#include "windows.hpp"

namespace menu {
Fl_Menu_Bar *menu(int w, int h, const window::MainWindow *window);
void helpCb(Fl_Widget *w, void *v);
}  // namespace menu
