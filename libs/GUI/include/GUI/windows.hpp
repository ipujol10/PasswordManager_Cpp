#pragma once

#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Window.H>

namespace window {
class MainWindow : public Fl_Window {
private:
  Fl_Group *password_group;
  Fl_Group *password_group2;
  Fl_Menu_Bar *menuBar;

  void password(int W, int H, const char *title);
  void password2(int W, int H, const char *title);
  static void go2pass1(Fl_Widget *w, void *v);
  static void go2pass2(Fl_Widget *w, void *v);

public:
  MainWindow(int width, int height, const char *title);
  ~MainWindow();

  Fl_Window *help;
};

class HelpWindow : public Fl_Window {
private:
  Fl_Box *text;

public:
  HelpWindow(int width, int height, const char *title, const char *label);
  ~HelpWindow();
};
} // namespace window
