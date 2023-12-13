#include "FL/Fl_Window.H"
#include <FL/Fl.H>
#include <GUI/windows.hpp>
#include <cstring>
#include <iostream>

int main(int argc, char *argv[]) {
  int w = 1000, h = 700;
  const char *title = "Password Manager";
  Fl_Window *window = new Fl_Window(w, h, title);
  auto password = window::password(w, h, title);
  auto password2 = window::password2(w, h, "Change");
  password->show();
  password2->hide();
  for (int i = 0; i < password->children(); i++) {
    Fl_Widget *child = password->child(i);
    if (strcmp((char *)child->user_data(), "Button") == 0) {
      std::cout << "Found\n";
    }
  }
  window->show();
  window->show(argc, argv);
  return Fl::run();
}
