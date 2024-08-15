#include "windows.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Secret_Input.H>

#include "menus.hpp"

namespace window {
MainWindow::MainWindow(int width, int height, const char *title)
    : Fl_Window(width, height, title) {
  password(width, height, title);
  password2(width, height, title);

  const int HEIGHT = 100;
  const int WIDTH = 300;
  const int MENU_HEIGHT = 20;
  help = new HelpWindow(WIDTH, HEIGHT, "Help", "This is help");
  help->hide();

  menuBar = menu::menu(width, MENU_HEIGHT, this);
  this->add(menuBar);

  password_group->show();
  password_group2->hide();
}

MainWindow::~MainWindow() {
  delete password_group;
  delete password_group2;
  delete help;
}

void MainWindow::password(int W, int H, const char *title) {
  password_group = new Fl_Group(0, 0, W, H, title);
  int w = 300;
  int h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Secret_Input *password = new Fl_Secret_Input(x, y, w, h, "Password");
  Fl_Button *change = new Fl_Button(x, y + 50, 100, 25, "Change");
  change->callback(go2pass2, this);
  password_group->end();
  this->add(password_group);
}

void MainWindow::password2(int W, int H, const char *title) {
  password_group2 = new Fl_Group(0, 0, W, H, title);
  int w = 100, h = 25;
  int x = (W - w) / 2;
  int y = (H - h) / 2;
  Fl_Button *change = new Fl_Button(x, y, w, h, "Change");
  change->callback(go2pass1, this);
  password_group2->end();
  this->add(password_group2);
}

void MainWindow::go2pass1(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->password_group->show();
  window->password_group2->hide();
}

void MainWindow::go2pass2(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->password_group->hide();
  window->password_group2->show();
}

HelpWindow::HelpWindow(int width, int height, const char *title, const char *label)
    : Fl_Window(width, height, title) {
  text = new Fl_Box(0, 0, width, height, label);
  text->box(FL_EMBOSSED_BOX);
  text->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  this->add(text);
}

HelpWindow::~HelpWindow() { delete text; }
}  // namespace window
