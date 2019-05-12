#include <editor/frame.hpp>

#include <cctype>
#include <cstdlib>
#include <sstream>

#include <ncurses.h>

namespace editor {

Frame::Frame(Buffer* buf) : buf_{buf}, offset_{0, 0} {}

void Frame::Attach(Buffer* buf) { buf_ = buf; }

void Frame::Detach() { buf_ = nullptr; }

void Frame::UpdateStatusLine() {
    auto point = buf_->GetPoint();
    std::ostringstream ss;
    ss << "=[offset " << offset_.row << ',' << offset_.col << " : point "
       << point.row << ',' << point.col;
    ss << " input=" << input_ << "]";
    status_line_ = ss.str();
}

void Frame::Scroll() {
    const Point point = buf_->GetPoint();

    if (point.row < offset_.row) {
        offset_.row = point.row;
    }

    const std::size_t max_screen_row = win_.GetHeight() - status_line_height;
    if (point.row >= offset_.row + max_screen_row) {
        offset_.row = point.row - (max_screen_row - 1);
    }

    if (point.col < offset_.col) {
        offset_.col = point.col;
    }

    const std::size_t win_width = win_.GetWidth();
    if (point.col >= offset_.col + win_width) {
        offset_.col = point.col - (win_width - 1);
    }
}

void Frame::Clear() { win_.Clear(); }

void Frame::DrawRows() {
    if (buf_) {
        const int win_width = win_.GetWidth();
        const std::size_t buf_max_row = buf_->GetLinesCount();
        const std::size_t max_screen_row =
            win_.GetHeight() - status_line_height;

        // for each row on screen/window
        for (std::size_t screen_row = 0; screen_row < max_screen_row;
             ++screen_row) {
            std::size_t buf_row = screen_row + offset_.row;
            ncpp::Point p{0, screen_row};
            if (buf_row < buf_max_row) {
                // draw buffer line
                auto& line = buf_->GetLine(buf_row);
                int len = line.size() - offset_.col;
                if (len < 0) {
                    len = 0;
                    win_.Print(p, "");
                } else {
                    // cut row if it doesn't fit in frame
                    if (len > win_width) {
                        len = win_width;
                    }
                    std::string rline(line.c_str() + offset_.col);
                    rline.resize(len);
                    win_.Print(p, rline);
                }
            } else {
                // draw empty line
                win_.Print(p, "~");
            }
        }
    }
}

void Frame::DrawStatusLine() {
    UpdateStatusLine();
    std::string separator(win_.GetWidth(), '=');
    auto win_height = win_.GetHeight();
    win_.Print({0, win_height - 1}, separator);
    win_.Print({0, win_height - 1}, status_line_);
}

void Frame::DrawCursor() {
    auto point = buf_->GetPoint();
    win_.MoveCursor(point.row - offset_.row, point.col - offset_.col);
}

void Frame::Refresh() {
    Scroll();

    Clear();
    DrawRows();
    DrawStatusLine();
    DrawCursor();

    win_.Refresh();
}

void Frame::ProcessInput() {
    input_ = win_.Getch();
    switch (input_) {
        case 27: {  // ESC or ALT
            std::exit(0);
            break;
        }
        case KEY_LEFT: {
            buf_->MovePointBackward();
            break;
        }
        case KEY_RIGHT: {
            buf_->MovePointForward();
            break;
        }
        case KEY_DOWN: {
            buf_->MoveLineForward();
            break;
        }
        case KEY_UP: {
            buf_->MoveLineBackward();
            break;
        }
        case KEY_BACKSPACE: {
            buf_->DeleteChar();
            break;
        }
        default: {
            if (std::isprint(input_) || input_ == '\r' || input_ == '\n') {
                buf_->InsertChar(input_);
            }
            break;
        }
    }
}
}  // namespace editor
