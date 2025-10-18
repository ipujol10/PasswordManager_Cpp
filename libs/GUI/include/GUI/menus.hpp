#pragma once

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Widget.H>

#include "windows.hpp"

namespace menu {
Fl_Menu_Bar *Menu(int w, int h, const window::MainWindow *window);
void HelpCb(Fl_Widget *w, void *v);
}  // namespace menu
