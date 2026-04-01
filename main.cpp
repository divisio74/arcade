#include <dlfcn.h>
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "include/Vm/Vm.hpp"
#include "include/games/Menue.hpp"
#include <filesystem>
#include <dirent.h>


int main(int argc, char *argv[]) {

    void *DefaultLib;
    IDisplay *Default;
    typedef IDisplay* (*displayfunc)();
    int is_working = 0;
    Vm vm;

    void *MenueLib;
    typedef Menue* (*menufunc)(std::vector<std::string>, std::vector<std::string>);
    MenueLib = dlopen("./Menue.so", RTLD_LAZY);
    menufunc mfunc = (menufunc)dlsym(MenueLib, "CreateGame");


    if (argc == 0 || argc > 1)
        return 0;

    // gerer la lib par default donné en arg
    DefaultLib = dlopen(argv[1], RTLD_LAZY);
    displayfunc dfunc = (displayfunc)dlsym(DefaultLib, "CreateDisplay");
    Default = dfunc();

    vm.handle_lib()

    //menue IGame a affcicher ici avec la lib donner en argument par default


    //boucle appelant toute les focntion display meme celles vide peut import la lib
    while (is_working < 20)
    {
        
    }
    dlclose(displaylib);
    dlclose(gamelib);
}