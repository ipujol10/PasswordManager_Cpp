#include <FL/Fl.H>
#include <GUI/windows.hpp>

int main (int argc, char *argv[]) {
    int w = 1000, h = 700;
    const char* title = "Password Manager";
    auto password = window::password(w, h, title);
    password->show(argc, argv);
    return Fl::run();
}
