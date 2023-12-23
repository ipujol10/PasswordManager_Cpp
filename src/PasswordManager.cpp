#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <GUI/menus.hpp>
#include <GUI/windows.hpp>

int main(int argc, char *argv[]) {
  const int WIDTH = 1000, HEIGHT = 700, MENU_HEIGHT = 20;
  const char *title = "Password Manager";
  Fl_Window *window = new Fl_Window(WIDTH, HEIGHT, title);
  auto password = window::password(WIDTH, HEIGHT, title);
  auto password2 = window::password2(WIDTH, HEIGHT, "Change");
  Fl_Group *groups[2] = {password, password2};
  password->show();
  password2->hide();
  window::getWidget(password, "button")->callback(window::go2window2, groups);
  window::getWidget(password2, "button")->callback(window::go2window1, groups);
  auto menu = menu::menu(WIDTH, MENU_HEIGHT);
  window->show();
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
