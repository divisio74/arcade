
#ifndef INCLUDED_VM_HPP
    #define INCLUDED_VM_HPP

#include <iostream>
#include <vector>

class Vm
{
    public:
        ~Vm() = default;
        int handle_lib();

    private :
        std::vector<std::string> _games;
        std::vector<std::string> _displays;

};


#endif
