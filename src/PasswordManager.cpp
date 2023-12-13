#include "FL/Fl_Window.H"
#include <FL/Fl.H>
#include <GUI/windows.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  int w = 1000, h = 700;
  const char *title = "Password Manager";
  Fl_Window *window = new Fl_Window(w, h, title);
  auto password = window::password(w, h, title);
  auto password2 = window::password2(w, h, "Change");
  password->show();
  password2->hide();
  if (window::getWidget(password, "button")) {
    std::cout << "Found\n";
  }
  window->show();
  window->show(argc, argv);
  return Fl::run();
}
