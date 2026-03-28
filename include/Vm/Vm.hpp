
#ifndef INCLUDED_VM_HPP
    #define INCLUDED_VM_HPP

#include <iostream>
#include <vector>

class Vm
{
    public:
        Vm();
        Vm(/* args */);
        Vm(const Vm& other);
        Vm& operator=(const Vm& other);
        ~Vm() = default;
    
    private :
        std::vector<std::string> _games;
        std::vector<std::string> _displays;

};


#endif
