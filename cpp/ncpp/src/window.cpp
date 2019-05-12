#include <ncpp/window.hpp>

#include <cassert>

#include <ncurses.h>

#include <ncpp/exception.hpp>
#include <ncpp/ncurses.hpp>

namespace ncpp {

Window::Window() : Window{ncurses().NewWindow(LINES, COLS, 0, 0)} {}

Window::Window(int rows, int cols, int y0, int x0)
    : Window{ncurses().NewWindow(rows, cols, y0, x0)} {}

Window::Window(WINDOW* w) : win_{w} {
    if (!win_) {
        throw Exception("newwin/initscr failed");
    }

    SetKeyPad(true);
}

int Window::Getch() { return wgetch(win_.get()); }

int Window::Getch(int y, int x) { return mvwgetch(win_.get(), y, x); }

void Window::Refresh() { wrefresh(win_.get()); }

void Window::Clear() { wclear(win_.get()); }

std::size_t Window::GetHeight() const {
    int h, w;
    getmaxyx(win_.get(), h, w);
    assert(h > 0);
    return h;
}

std::size_t Window::GetWidth() const {
    int h, w;
    getmaxyx(win_.get(), h, w);
    assert(w > 0);
    return w;
}

void Window::Print(Point p, const std::string& s) {
    mvwprintw(win_.get(), p.y, p.x, s.c_str());
}

void Window::Print(Point p, const char* s) {
    mvwprintw(win_.get(), p.y, p.x, s);
}

int Window::SetKeyPad(bool on) { return keypad(win_.get(), on); }

int Window::MoveCursor(int y, int x) { return wmove(win_.get(), y, x); }

}  // namespace ncpp
