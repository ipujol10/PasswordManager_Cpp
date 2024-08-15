#include "menus.hpp"

namespace menu {
Fl_Menu_Bar *menu(int w, int h, const window::MainWindow *window) {
  Fl_Menu_Item menuItems[] = {
      {"&Help", FL_ALT + 'h', (Fl_Callback *)help_cb, (void *)window},
      {      0             }
  };
  Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, w, h);
  m->copy(menuItems);
  return m;
}

void help_cb(Fl_Widget *w, void *v) {
  auto *window = static_cast<window::MainWindow *>(v);
  window->help->show();
}
}  // namespace menu
