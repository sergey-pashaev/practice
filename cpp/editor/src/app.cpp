#include <iostream>

#include <editor/editor.hpp>
#include <ncpp/ncurses.hpp>

int usage(const char* bin) {
    std::cout << "Usage: " << bin << " <file>\n";
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return usage(argv[0]);
    }

    auto& nc = ncpp::ncurses();
    nc.SetRaw(true);
    nc.SetKeyPad(true);
    nc.SetEcho(false);

    editor::Editor e;
    e.Open(argv[1]);
    e.Run();
    return 0;
}
