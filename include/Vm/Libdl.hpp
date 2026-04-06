
#ifndef LIBDL_HPP
    #define LIBDL_HPP

#include <dlfcn.h>
#include <string>

class Libdl {
    public:
        Libdl(std::string &path);
        ~Libdl();
        bool IsSymbol(std::string &name);

        template<typename T>
            T DlSymbol(std::string &name)
            {
                return (T)(dlsym(_opened_dl, name.c_str()));
            }
    private:
        void *_opened_dl;
};

#endif
