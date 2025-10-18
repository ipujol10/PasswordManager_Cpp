#pragma once

#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>

namespace window {
class MainWindow : public Fl_Window {
 private:
  Fl_Group *password_group_;
  Fl_Group *password_group2_;
  Fl_Menu_Bar *menuBar_;

  void Password(int width_p, int height_p, const char *title);
  void Password2(int width_p, int height_p, const char *title);
  static void Go2pass1(Fl_Widget *w, void *v);
  static void Go2pass2(Fl_Widget *w, void *v);

 public:
  MainWindow(int width_p, int height_p, const char *title);
  ~MainWindow() override;

  Fl_Window *help;
};

class HelpWindow : public Fl_Window {
 private:
  Fl_Box *text_;

 public:
  HelpWindow(int width_p, int height_p, const char *title, const char *label);
  ~HelpWindow() override;
};
}  // namespace window
