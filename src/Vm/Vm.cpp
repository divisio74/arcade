#include "../../include/Vm/Vm.hpp"

int Vm::handle_lib()
{
    const char *path = "./Lib";
    DIR* dir = opendir(path);
    struct dirent* libs;
    void *lib;

    if (!dir)
        return 1;
    libs = readdir(dir);
    while (libs != nullptr) {
        std::string name = libs->d_name;
        std::size_t len = name.size();

        if (name.substr(len - 3) == ".so" && len > 3)
        {
            lib = dlopen(name.c_str(), RTLD_LAZY);
            if(dlsym(lib, "CreateDisplay")) {
                _displays.push_back(name);
            } else if (dlsym(lib, "CreateGame")) {
                _games.push_back(name);
            }
        }
    }
}