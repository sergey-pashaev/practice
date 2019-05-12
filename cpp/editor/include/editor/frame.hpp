#ifndef EDITOR_FRAME_HPP
#define EDITOR_FRAME_HPP

#include <chrono>
#include <string>

#include <ncpp/window.hpp>

#include <editor/buffer.hpp>

namespace editor {

class Frame {
   public:
    Frame(Buffer* buf);

    void Attach(Buffer* buf);
    void Detach();
    void Refresh();
    void ProcessInput();

   private:
    void UpdateStatusLine();
    void Scroll();
    void Clear();
    void DrawRows();
    void DrawStatusLine();
    void DrawCursor();

   private:
    std::size_t status_line_height = 1;

   private:
    Buffer* buf_;
    ncpp::Window win_;
    Point offset_;
    std::string status_line_;
    int input_ = 0;
};

}  // namespace editor

#endif /* EDITOR_FRAME_HPP */
