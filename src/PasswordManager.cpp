#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <GUI/windows.hpp>

int main(int argc, char *argv[]) {
  int w = 1000, h = 700;
  const char *title = "Password Manager";
  Fl_Window *window = new Fl_Window(w, h, title);
  auto password = window::password(w, h, title);
  auto password2 = window::password2(w, h, "Change");
  Fl_Group *groups[2] = {password, password2};
  password->show();
  password2->hide();
  window::getWidget(password, "button")
      .value()
      ->callback(window::go2window2, groups);
  window::getWidget(password2, "button")
      .value()
      ->callback(window::go2window1, groups);
  window->show();
  window->show(argc, argv);
  return Fl::run();
}
