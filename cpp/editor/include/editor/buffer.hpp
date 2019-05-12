#ifndef EDITOR_BUFFER_HPP
#define EDITOR_BUFFER_HPP

#include <string>
#include <vector>

namespace editor {

struct Point {
    std::size_t row = 0;
    std::size_t col = 0;
};

class Buffer {
   public:
    using String = std::string;
    using Char = char;

    Buffer();
    Buffer(const char* path);

    void SetName(const String& name);
    const String& GetName() const;

    bool IsModified() const;

    void AppendLine(const String& line);
    void AppendChar(Char c);

    std::size_t GetLinesCount() const;
    const String& GetLine(std::size_t row) const;

    // TODO: add count parameter
    void MovePointForward();
    void MovePointBackward();
    void MovePointBeginOfLine();
    void MovePointEndOfLine();
    void MoveLineForward();
    void MoveLineBackward();

    Point GetPoint() const;

   private:
    std::size_t ReadFile(const char* path);
    const String& GetCurrentLine() const;
    std::size_t GetCurrentLineLastCol() const;

   private:
    std::string name_;
    bool is_modified_;
    std::vector<String> lines_;
    Point point_;
};

}  // namespace editor

#endif /* EDITOR_BUFFER_HPP */
