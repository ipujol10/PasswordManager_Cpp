#include "menus.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Widget.H>

#include "windows.hpp"

namespace menu {
Fl_Menu_Bar *Menu(int w, int h, const window::MainWindow *window) {
  Fl_Menu_Item menu_items[] = {
      {"&Help", FL_ALT + 'h', (Fl_Callback *)HelpCb, (void *)window},
      {nullptr}
  };
  auto *m = new Fl_Menu_Bar(0, 0, w, h);
  m->copy(menu_items);
  return m;
}

void HelpCb(Fl_Widget *w, void *v) {
  auto *window = static_cast<window::MainWindow *>(v);
  window->help->show();
}
}  // namespace menu
