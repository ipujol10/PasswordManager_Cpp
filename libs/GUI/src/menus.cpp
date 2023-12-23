#include "menus.hpp"

namespace menu {
Fl_Menu_Bar *menu(int w, int h) {
  Fl_Menu_Item menuItems[] = {
    {"File", 0, 0, 0, FL_SUBMENU},
      {"TEST"},
      {"Test2"},
      {"Test3"},
      {0},
    {"File2", 0, 0, 0, FL_SUBMENU},
      {"TEST1.1"},
      {0},
    {0}
  };
  Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, w, h);
  m->copy(menuItems);
  return m;
}
} // namespace menu
