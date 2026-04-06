#include "../../include/Vm/Libdl.hpp"


Libdl::Libdl(std::string &path)
{
    void *temp = dlopen(path.c_str(), RTLD_LAZY);
    if (!temp)
        return;
    _opened_dl = temp;
}

Libdl::~Libdl()
{
    dlclose(_opened_dl);
}

bool Libdl::IsSymbol(std::string &name)
{
    if (dlsym(_opened_dl, name.c_str()))
        return true;
    return false;
}
