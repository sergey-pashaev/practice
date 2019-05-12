#ifndef NCPP_NCURSES_HPP
#define NCPP_NCURSES_HPP

#include <ncurses.h>

#include <ncpp/window.hpp>

namespace ncpp {

class Ncurses : public Window {
   private:
    friend Ncurses& ncurses();
    Ncurses();

   public:
    ~Ncurses();

    WINDOW* NewWindow(int rows, int cols, int y0, int x0);

    int SetCbreak(bool on);
    int SetEcho(bool on);
    int SetRaw(bool on);
    int SetKeyPad(bool on);

    int Ungetch(int c);
    int Getch();
};

Ncurses& ncurses();

}  // namespace ncpp

#endif /* NCPP_NCURSES_HPP */
