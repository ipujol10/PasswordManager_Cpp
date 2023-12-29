#include "menus.hpp"
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

namespace menu {
Fl_Menu_Bar *menu(int w, int h) {
  Fl_Menu_Item menuItems[] = {
    {"&Help", FL_ALT + 'h', (Fl_Callback *)help_cb},
    {0}
  };
  Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, w, h);
  m->copy(menuItems);
  return m;
}

void help_cb(Fl_Widget *w, void *v) {
  const int HEIGHT = 100, WIDTH = 300;
  Fl_Window *help = new Fl_Window(WIDTH, HEIGHT, "Help");
  Fl_Box *text = new Fl_Box(0, 0, WIDTH, HEIGHT, "This is help");
  help->end();
  help->show();
}
} // namespace menu
