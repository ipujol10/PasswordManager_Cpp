#pragma once

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

namespace menu {
Fl_Menu_Bar *menu(int w, int h);
void help_cb(Fl_Widget *w, void *v);
} // namespace menu
