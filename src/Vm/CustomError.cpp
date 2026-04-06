#include "../../include/Vm/CustomError.hpp"

CustomError::CustomError(const std::string &msg)
{
    _msg = msg;
}

const char *CustomError::what() const noexcept
{
    return _msg.c_str();
}
