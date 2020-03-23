#ifndef DWARF_READER_H
#define DWARF_READER_H

#include <string>

#include <dwarf.h>
#include <libdwarf.h>

class DwarfReader {
   public:
    DwarfReader(std::string filepath);
    ~DwarfReader();
   private:

   private:
    int fd_ = -1;
    std::string filepath_;

    Dwarf_Debug d_dbg_ = 0;
    Dwarf_Error d_error_;
    Dwarf_Handler d_error_handler_ = 0;
    Dwarf_Ptr d_error_arg_ = 0;
};

#endif /* DWARF_READER_H */
