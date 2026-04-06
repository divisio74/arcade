#ifndef CUSTOMERROR_HPP
    #define CUSTOMERROR_HPP


#include <exception>
#include "Vm.hpp"


class CustomError : public std::exception {
    public:
        CustomError(const std::string &msg);
        const char *what() const noexcept override;
    private:
        std::string _msg;
};

#endif
