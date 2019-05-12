#include <iostream>

#include <editor/editor.hpp>
#include <ncpp/ncurses.hpp>

int main(int argc, char* argv[]) {
    auto& nc = ncpp::ncurses();
    nc.SetRaw(true);
    nc.SetKeyPad(true);
    nc.SetEcho(false);

    editor::Editor e;
    if (argc > 1) {
        e.Open(argv[1]);
    }
    e.Run();
    return 0;
}
