#include <FL/Fl.H>
#include <FL/Fl_Window.H>

int main(int argc, char* argv[]) {
  int w = 1000, h = 700;
  const char* title = "Password Manager";
  Fl_Window* window = new Fl_Window(w, h, title);
  window->end();
  window->show(argc, argv);
  return Fl::run();
}
