#include <editor/buffer.hpp>

#include <cassert>
#include <fstream>

namespace editor {

Buffer::Buffer() : is_modified_{false} {}

Buffer::Buffer(const char* path) : name_{path}, is_modified_{false} {
    std::ifstream input(path, std::ios::in);
    for (String line; std::getline(input, line);) {
        lines_.push_back(line);
    }
}

void Buffer::SetName(const String& name) { name_ = name; }

const Buffer::String& Buffer::GetName() const { return name_; }

bool Buffer::IsModified() const { return is_modified_; }

void Buffer::AppendLine(const String& line) { lines_.push_back(line); }

void Buffer::AppendChar(Char c) { lines_.back().push_back(c); }

const Buffer::String& Buffer::GetLine(std::size_t row) const {
    return lines_.at(row);
}

Buffer::String& Buffer::GetLine(std::size_t row) { return lines_.at(row); }

void Buffer::InsertChar(Char c) {
    String& line = GetCurrentLine();
    auto cur_pos = line.begin() + point_.col;
    if (c == '\r' || c == '\n') {
        String new_line(cur_pos, line.end());
        line.erase(cur_pos, line.end());
        lines_.insert(lines_.begin() + point_.row + 1, new_line);
        point_.row++;
        point_.col = 0;
    } else {
        line.insert(cur_pos, c);
        point_.col++;
    }
}

void Buffer::DeleteChar() {
    String& line = GetCurrentLine();
    if (point_.col > 0) {
        line.erase(point_.col - 1, 1);
        point_.col--;
    } else {
        if (point_.row > 0) {
            String& prev_line = GetLine(point_.row - 1);
            point_.col = prev_line.size();
            prev_line.append(line);
            lines_.erase(lines_.begin() + point_.row);
            point_.row--;
        }
    }
}

std::size_t Buffer::GetLinesCount() const { return lines_.size(); }

Buffer::String& Buffer::GetCurrentLine() {
    assert(point_.row < GetLinesCount() && "out of range buffer access");
    return GetLine(point_.row);
}

const Buffer::String& Buffer::GetCurrentLine() const {
    assert(point_.row < GetLinesCount() && "out of range buffer access");
    return GetLine(point_.row);
}

std::size_t Buffer::GetCurrentLineLastCol() const {
    auto& line = GetCurrentLine();
    return line.size();
}

void Buffer::MovePointForward() {
    const std::size_t last_col = GetCurrentLineLastCol();
    if (point_.col < last_col) {
        // move format in current line
        point_.col++;
    } else {
        // go to beginning of next line if it exists
        std::size_t last_line = GetLinesCount() - 1;
        if (point_.row < last_line) {
            point_.row++;
            MovePointBeginOfLine();
        }
    }
}

void Buffer::MovePointBackward() {
    if (point_.col > 0) {
        // move back in current line
        point_.col--;
    } else {
        // go to end of previous line if it exists
        if (point_.row > 0) {
            point_.row--;
            MovePointEndOfLine();
        }
    }
}

void Buffer::MovePointBeginOfLine() { point_.col = 0; }

void Buffer::MovePointEndOfLine() { point_.col = GetCurrentLineLastCol(); }

Point Buffer::GetPoint() const { return point_; }

void Buffer::MoveLineForward() {
    std::size_t last_line = GetLinesCount() - 1;
    if (point_.row < last_line) {
        point_.row++;
        const std::size_t last_col = GetCurrentLineLastCol();
        if (point_.col > last_col) {
            point_.col = last_col;
        }
    }
}

void Buffer::MoveLineBackward() {
    if (point_.row > 0) {
        point_.row--;
        const std::size_t last_col = GetCurrentLineLastCol();
        if (point_.col > last_col) {
            point_.col = last_col;
        }
    }
}

}  // namespace editor
