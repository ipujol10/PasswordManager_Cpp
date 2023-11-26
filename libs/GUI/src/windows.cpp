#include "windows.hpp"
#include <FL/Fl_Secret_Input.H>

namespace window {
Fl_Window* password(int W, int H, const char* title) {
    Fl_Window* window = new Fl_Window(W, H, title);
    int w = 300, h = 25;
    int x = (W - w) / 2;
    int y = (H - h) / 2;
    Fl_Secret_Input* password = new Fl_Secret_Input(x, y, w, h, "Password");
    window->end();
    return window;
}
}
