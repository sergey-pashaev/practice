#ifndef NCPP_EXCEPTION_HPP
#define NCPP_EXCEPTION_HPP

#include <stdexcept>

namespace ncpp {

class Exception : public std::runtime_error {
   public:
    Exception(const char* msg) : std::runtime_error{msg} {}
};

}  // namespace ncpp

#endif /* NCPP_EXCEPTION_HPP */
