#include "../../include/Vm/Vm.hpp"
#include <dirent.h>
#include <thread>
#include <chrono>

int Vm::handle_lib()
{
    const char *path = "./lib";
    DIR* dir = opendir(path);
    struct dirent* libs;
    void *lib;

    if (!dir)
        return 1;
    libs = readdir(dir);
    while (libs != nullptr) {
        std::string name = libs->d_name;
        std::size_t len = name.size();

        if (len > 3 && name.substr(len - 3) == ".so") {
            std::string full_path = std::string(path) + "/" + name;
            lib = dlopen(full_path.c_str(), RTLD_LAZY);
            if (dlsym(lib, "CreateDisplay"))
                _displays.push_back(full_path);
            else if (dlsym(lib, "CreateGame"))
                _games.push_back(full_path);
            dlclose(lib);
        }
        libs = readdir(dir);
    }
    closedir(dir);
    return 0;
}

IDisplay *Vm::load_display(const std::string &path, void *&lib)
{
    typedef IDisplay* (*dispfunc)();
    lib = dlopen(path.c_str(), RTLD_LAZY);
    return ((dispfunc)dlsym(lib, "CreateDisplay"))();
}

IGame *Vm::load_menu(void *&lib)
{
    typedef IGame* (*menufunc)();
    typedef void (*setlistsfunc)(IGame*, std::vector<std::string>, std::vector<std::string>);

    lib = dlopen("./lib/arcade_menue.so", RTLD_LAZY);
    IGame *menu = ((menufunc)dlsym(lib, "CreateGame"))();
    setlistsfunc sfunc = (setlistsfunc)dlsym(lib, "SetLists");
    if (sfunc)
        sfunc(menu, _games, _displays);
    return menu;
}

bool Vm::run_menu(IGame *menu, IDisplay *display)
{
    menu->reset();
    display->open_window();
    while (!menu->get_end()) {
        display->clear_window();
        display->display(menu->get_element());
        arc::TouchSignal sig = display->signal();
        if (sig.touch == arc::Touch::ESCAPE) {
            display->close_window();
            return false;
        }
        menu->update(sig);
    }
    display->close_window();
    return true;
}

bool Vm::run_game(IGame *game, IDisplay *&display, void *&display_lib)
{
    int disp_index = 0;
    for (int i = 0; i < (int)_displays.size(); i++) {
        if (_displays[i] == _current_display_path)
            disp_index = i;
    }

    display->open_window();
    while (!game->get_end()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        arc::TouchSignal sig = display->signal();

        if (sig.touch == arc::Touch::ESCAPE) {
            display->close_window();
            return true;
        }

        if (sig.touch == arc::Touch::TAB) {
            display->close_window();
            dlclose(display_lib);
            disp_index = (disp_index + 1) % (int)_displays.size();
            _current_display_path = _displays[disp_index];
            display = load_display(_current_display_path, display_lib);
            display->open_window();
            continue;
        }
        display->clear_window();
        display->display(game->get_element());
        game->update(sig);
    }
    display->close_window();
    return true;
}

void Vm::main_boucle(const std::string &default_display_path)
{
    void *DefaultLib;
    void *MenueLib;
    _current_display_path = default_display_path;
    IDisplay *Default = load_display(default_display_path, DefaultLib);
    IGame *menu;
    typedef std::string (*getterfunc)(IGame*);

    handle_lib();
    menu = load_menu(MenueLib);
    getterfunc gGame = (getterfunc)dlsym(MenueLib, "GetChosenGame");
    getterfunc gDisp = (getterfunc)dlsym(MenueLib, "GetChosenDisplay");

    while (true) {
        if (!run_menu(menu, Default))
            break;

        std::string chosen_game = gGame(menu);
        std::string chosen_display = gDisp(menu);
        _current_display_path = chosen_display;

        void *GameLib;
        void *DisplayLib;
        typedef IGame*(*gamefunc)();
        GameLib = dlopen(chosen_game.c_str(), RTLD_LAZY);
        IGame *game = ((gamefunc)dlsym(GameLib, "CreateGame"))();
        IDisplay *display = load_display(chosen_display, DisplayLib);

        run_game(game, display, DisplayLib);
        dlclose(GameLib);
        dlclose(DisplayLib);
    }
    dlclose(DefaultLib);
    dlclose(MenueLib);
}
