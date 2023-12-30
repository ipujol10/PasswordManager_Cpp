#pragma once

#include "windows.hpp"

namespace menu {
Fl_Menu_Bar *menu(int w, int h, const window::MainWindow *window);
void help_cb(Fl_Widget *w, void *v);
} // namespace menu
