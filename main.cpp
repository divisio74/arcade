#include <dlfcn.h>
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <filesystem>
#include <dirent.h>


//vm part

int handle_lib() //remonte une erreur si ne trouve pas un jeu et une lib graphique ?
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

        if (name == "." || name == "..")
            continue;
        if (name.size() > 3 && name.substr(name.size() - 3) == ".so")
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

//le menue du programme est vue comme unIGAME  


int main(int argc, char *argv[]) {

    void *DefaultLib;
    IDisplay *Default;
    typedef IDisplay* (*displayfunc)();
    int is_working = 0;

    if (argc == 0 || argc > 1)
        return 0;

    // handle_lib ici
    DefaultLib = dlopen(argv[1], RTLD_LAZY);
    displayfunc dfunc = (displayfunc)dlsym(DefaultLib, "CreateDisplay");
    Default = dfunc();

    //vm->handle_lib()

    //menue IGame a affcicher ici avec la lib donner en argument par default


    //boucle appelant toute les focntion display meme celles vide peut import la lib
    while (is_working < 20)
    {

    }
    dlclose(displaylib);
    dlclose(gamelib);
}