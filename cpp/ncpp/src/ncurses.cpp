#include <ncpp/ncurses.hpp>

namespace ncpp {

Ncurses::Ncurses() : Window{initscr()} {}

Ncurses::~Ncurses() { endwin(); }

WINDOW* Ncurses::NewWindow(int rows, int cols, int y0, int x0) {
    return newwin(rows, cols, y0, x0);
}

int Ncurses::SetCbreak(bool on) { return on ? cbreak() : nocbreak(); }

int Ncurses::SetEcho(bool on) { return on ? echo() : noecho(); }

int Ncurses::SetRaw(bool on) { return on ? raw() : noraw(); }

int Ncurses::SetKeyPad(bool on) { return keypad(stdscr, on); }

int Ncurses::Ungetch(int c) { return ungetch(c); }

int Ncurses::Getch() { return getch(); }

Ncurses& ncurses() {
    static Ncurses nc;
    return nc;
}

}  // namespace ncpp
