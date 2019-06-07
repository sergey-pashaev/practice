#ifndef NCPP_WINDOW_HPP
#define NCPP_WINDOW_HPP

#include <memory>
#include <utility>

#include <ncurses.h>

namespace ncpp {

struct Point {
    std::size_t x;
    std::size_t y;
};

class Window {
   public:
    Window();
    Window(int rows, int cols, int y0, int x0);
    explicit Window(WINDOW* win);

    int SetKeyPad(bool on);

    int Getch();
    int Getch(int y, int x);

    void Refresh();
    void Clear();

    std::size_t GetHeight() const;
    std::size_t GetWidth() const;

    void Print(Point p, const std::string& s);
    void Print(Point p, const char* s);

    int MoveCursor(int y, int x);

   private:
    struct WindowDeleter {
        void operator()(WINDOW* win) const { delwin(win); }
    };

    using WindowPtr = std::unique_ptr<WINDOW, WindowDeleter>;
    static_assert(sizeof(WindowPtr) == sizeof(WINDOW*),
                  "unique_ptr space overhead detected");

    WindowPtr win_;
};

}  // namespace ncpp

#endif /* NCPP_WINDOW_HPP */
