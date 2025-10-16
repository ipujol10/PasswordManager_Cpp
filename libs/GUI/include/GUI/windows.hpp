#pragma once

#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

namespace window {
class MainWindow : public Fl_Window {
 private:
  Fl_Group *_password_group;
  Fl_Group *_password_group2;
  Fl_Menu_Bar *_menuBar;

  void password(int width, int height, const char *title);
  void password2(int width, int height, const char *title);
  static void go2pass1(Fl_Widget *w, void *v);
  static void go2pass2(Fl_Widget *w, void *v);

 public:
  MainWindow(int width, int height, const char *title);
  ~MainWindow() override;

  Fl_Window *help;
};

class HelpWindow : public Fl_Window {
 private:
  Fl_Box *_text;

 public:
  HelpWindow(int width, int height, const char *title, const char *label);
  ~HelpWindow() override;
};
}  // namespace window
