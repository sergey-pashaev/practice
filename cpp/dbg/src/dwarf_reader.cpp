#include <dbg/dwarf_reader.h>

#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // open, close

#include <fmt/printf.h>

DwarfReader::DwarfReader(std::string filepath)
    : filepath_{std::move(filepath)} {
    fd_ = open(filepath_.c_str(), O_RDONLY);
    if (fd_ < 0) {
        throw 1; // TODO:
    }

    int res = dwarf_init(fd_, DW_DLC_READ, d_error_handler_, d_error_arg_,
                         &d_dbg_, &d_error_);
    if (res != DW_DLV_OK) {
        throw 2;// TODO:
    }
}

DwarfReader::~DwarfReader() {
    int res = dwarf_finish(d_dbg_, &d_error_);
    if (res != DW_DLV_OK) {
        fmt::printf("dwarf_finish failed\n");
    }

    if (fd_ >= 0) {
        close(fd_);
    }
}
