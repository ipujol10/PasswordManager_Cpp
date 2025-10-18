#include <FL/Fl.H>

#include <GUI/windows.hpp>

int main(int argc, char *argv[]) {
  const int width = 1000, height = 700, menu_height = 20;
  const char *title = "Password Manager";
  auto window = new window::MainWindow(width, height, title);
  window->show(argc, argv);
  return Fl::run();
}
