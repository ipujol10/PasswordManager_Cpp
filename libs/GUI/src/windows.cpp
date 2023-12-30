#include "windows.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Box.H>

namespace window {
MainWindow::MainWindow(int width, int height, const char *title)
    : Fl_Window(width, height, title) {
  password_group = password(width, height, title);
  password_group2 = password2(width, height, title);

  const int HEIGHT = 100, WIDTH = 300;
  help = new Fl_Window(WIDTH, HEIGHT, "Help");
  Fl_Box *text = new Fl_Box(0, 0, WIDTH, HEIGHT, "This is help");
  help->end();
  help->hide();

  password_group->show();
  password_group2->hide();
  this->end();
}

MainWindow::~MainWindow() {
  delete password_group;
  delete password_group2;
  delete help;
}

Fl_Group *MainWindow::password(int W, int H, const char *title) {
  Fl_Group *group = new Fl_Group(0, 0, W, H, title);
  int w = 300, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Secret_Input *password = new Fl_Secret_Input(x, y, w, h, "Password");
  Fl_Button *change = new Fl_Button(x, y + 50, 100, 25, "Change");
  change->callback(go2pass2, this);
  group->end();
  return group;
}

Fl_Group *MainWindow::password2(int W, int H, const char *title) {
  Fl_Group *group = new Fl_Group(0, 0, W, H, title);
  int w = 100, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Button *change = new Fl_Button(x, y, w, h, "Change");
  change->callback(go2pass1, this);
  group->end();
  return group;
}

void MainWindow::go2pass1(Fl_Widget *w, void *v) {
  MainWindow *window = (MainWindow *)v;
  window->password_group->show();
  window->password_group2->hide();
}

void MainWindow::go2pass2(Fl_Widget *w, void *v) {
  MainWindow *window = (MainWindow *)v;
  window->password_group->hide();
  window->password_group2->show();
}
} // namespace window
