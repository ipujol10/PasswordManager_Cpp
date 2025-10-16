#include "windows.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

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

  _menuBar = menu::menu(width, MENU_HEIGHT, this);
  this->add(_menuBar);

  _password_group->show();
  _password_group2->hide();
}

MainWindow::~MainWindow() {
  delete _password_group;
  delete _password_group2;
  delete help;
}

void MainWindow::password(int width, int height, const char *title) {
  _password_group = new Fl_Group(0, 0, width, height, title);
  const int W = 300;
  const int H = 25;
  const int X = (width - W) / 2;
  const int Y = (height - H) / 2;
  auto *password = new Fl_Secret_Input(X, Y, W, H, "Password");
  auto *change = new Fl_Button(X, Y + 50, 100, 25, "Change");
  change->callback(go2pass2, this);
  _password_group->end();
  this->add(_password_group);
}

void MainWindow::password2(int width, int height, const char *title) {
  _password_group2 = new Fl_Group(0, 0, width, height, title);
  const int W = 100, H = 25;
  const int X = 0;
  const int Y = 20;
  auto *change = new Fl_Button(X, Y, W, H, "Change");
  change->callback(go2pass1, this);

  const int WIN_W = this->w(), WIN_H = this->h();
  const int S_X = 0, S_Y = H + Y, S_W = WIN_W, S_H = WIN_H - S_Y;
  auto *data_scroll = new Fl_Scroll(S_X, S_Y, S_W, S_H);
  data_scroll->type(Fl_Scroll::VERTICAL);
  data_scroll->end();
  _password_group2->end();
  this->add(_password_group2);
}

void MainWindow::go2pass1(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->_password_group->show();
  window->_password_group2->hide();
}

void MainWindow::go2pass2(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->_password_group->hide();
  window->_password_group2->show();
}

HelpWindow::HelpWindow(int width, int height, const char *title, const char *label)
    : Fl_Window(width, height, title) {
  _text = new Fl_Box(0, 0, width, height, label);
  _text->box(FL_EMBOSSED_BOX);
  _text->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  this->add(_text);
}

HelpWindow::~HelpWindow() { delete _text; }
}  // namespace window
