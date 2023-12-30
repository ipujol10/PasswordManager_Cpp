#include <FL/Fl.H>
#include <GUI/windows.hpp>

int main(int argc, char *argv[]) {
  const int WIDTH = 1000, HEIGHT = 700, MENU_HEIGHT = 20;
  const char *title = "Password Manager";
  auto window = window::MainWindow(WIDTH, HEIGHT, title);
  window.show(argc, argv);
  return Fl::run();
}
