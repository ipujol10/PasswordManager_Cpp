#include "windows.hpp"

#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

#include <string>

#include "menus.hpp"
#include "widgets.hpp"

namespace window {
MainWindow::MainWindow(int width_p, int height_p, const char *title)
    : Fl_Window(width_p, height_p, title) {
  Password(width_p, height_p, title);
  Password2(width_p, height_p, title);

  const int height = 100;
  const int width = 300;
  const int menu_height = 20;
  help = new HelpWindow(width, height, "Help", "This is help");
  help->hide();

  menuBar_ = menu::Menu(width_p, menu_height, this);
  this->add(menuBar_);

  password_group_->show();
  password_group2_->hide();
}

MainWindow::~MainWindow() {
  delete password_group_;
  delete password_group2_;
  delete help;
  for (auto *ptr : entries_) { delete ptr; }
  entries_.clear();
}

void MainWindow::Password(int width_p, int height_p, const char *title) {
  password_group_ = new Fl_Group(0, 0, width_p, height_p, title);
  const int w = 300;
  const int h = 25;
  const int x = (width_p - w) / 2;
  const int y = (height_p - h) / 2;
  auto *password = new Fl_Secret_Input(x, y, w, h, "Password");
  auto *change = new Fl_Button(x, y + 50, 100, 25, "Change");
  change->callback(Go2pass2, this);
  password_group_->end();
  this->add(password_group_);
}

void MainWindow::Password2(int width_p, int height_p, const char *title) {
  password_group2_ = new Fl_Group(0, 0, width_p, height_p, title);
  const int w = 100, h = 25;
  const int x = 0;
  const int y = 20;
  auto *change = new Fl_Button(x, y, w, h, "Change");
  change->callback(Go2pass1, this);

  const int win_w = this->w(), win_h = this->h();
  const int s_x = 0, s_y = h + y, s_w = win_w, s_h = win_h - s_y;
  auto *data_scroll = new Fl_Scroll(s_x, s_y, s_w, s_h);
  data_scroll->type(Fl_Scroll::VERTICAL);
  data_scroll->box(Fl_Boxtype::FL_DOWN_BOX);
  auto *pack = new Fl_Pack(s_x, s_y, s_w, s_h);
  pack->resizable(pack);
  pack->type(Fl_Pack::VERTICAL);
  const int entry_height = 30;
  for (int i = 0; i < 100; ++i) {
    std::string name = "Name";
    name += std::to_string(i);

    std::string username = "User Name";
    username += std::to_string(i);

    auto *widget = new widgets::PasswordEntry(name, username, s_w, entry_height);
    entries_.push_back(widget);
  }
  pack->end();
  data_scroll->resizable(data_scroll);
  data_scroll->end();
  password_group2_->end();
  this->add(password_group2_);
}

void MainWindow::Go2pass1(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->password_group_->show();
  window->password_group2_->hide();
}

void MainWindow::Go2pass2(Fl_Widget *w, void *v) {
  auto *window = static_cast<MainWindow *>(v);
  window->password_group_->hide();
  window->password_group2_->show();
}

HelpWindow::HelpWindow(int width, int height, const char *title, const char *label)
    : Fl_Window(width, height, title) {
  text_ = new Fl_Box(0, 0, width, height, label);
  text_->box(FL_EMBOSSED_BOX);
  text_->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
  this->add(text_);
}

HelpWindow::~HelpWindow() { delete text_; }
}  // namespace window
