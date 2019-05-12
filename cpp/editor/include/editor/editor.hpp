#ifndef EDITOR_EDITOR_HPP
#define EDITOR_EDITOR_HPP

#include <editor/buffer.hpp>
#include <editor/frame.hpp>

namespace editor {

class Editor {
   public:
    Editor();
    void Run();
    void Open(const char* path);

   private:
    Buffer buf_;
    Frame frame_;
};

}  // namespace editor

#endif /* EDITOR_EDITOR_HPP */
