#include <editor/editor.hpp>

#include <utility>

namespace editor {

Editor::Editor() : buf_{}, frame_{&buf_} {
    buf_.AppendLine("; scratch buffer ");
}

void Editor::Open(const char* path) {
    Buffer b{path};
    std::swap(buf_, b);
}

void Editor::Run() {
    while (1) {
        frame_.Refresh();
        frame_.ProcessInput();
    }
}

}  // namespace editor
