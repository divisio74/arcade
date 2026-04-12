#include "../../include/Vm/Vm.hpp"
#include "../../include/Vm/CustomError.hpp"
#include <dirent.h>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>

int Vm::handle_lib()
{
    const char *path = "./lib";
    DIR* dir = opendir(path);
    struct dirent* libs;

    if (!dir)
        return 1;
    libs = readdir(dir);
    while (libs != nullptr) {
        std::string name = libs->d_name;
        std::size_t len = name.size();

        if (len > 3 && name.substr(len - 3) == ".so") {
            std::string full_path = std::string(path) + "/" + name;
            Libdl lib(full_path);
            std::string symDisplay = "CreateDisplay";
            std::string symGame = "CreateGame";
            if (lib.IsSymbol(symDisplay))
                _displays.push_back(full_path);
            else if (lib.IsSymbol(symGame))
                _games.push_back(full_path);
        }
        libs = readdir(dir);
    }
    closedir(dir);
    return 0;
}

IDisplay *Vm::load_display(std::string &path, Libdl *&lib)
{
    typedef IDisplay* (*dispfunc)();
    lib = new Libdl(path);
    std::string sym = "CreateDisplay";
    return lib->DlSymbol<dispfunc>(sym)();
}

IGame *Vm::load_menu(Libdl *&lib)
{
    typedef IGame* (*menufunc)();
    typedef void (*setlistsfunc)(IGame*, std::vector<std::string>, std::vector<std::string>);

    std::string menue_path = "./lib/arcade_menue.so";
    lib = new Libdl(menue_path);
    std::string symCreate = "CreateGame";
    IGame *menu = lib->DlSymbol<menufunc>(symCreate)();
    std::string symSet = "SetLists";
    setlistsfunc sfunc = lib->DlSymbol<setlistsfunc>(symSet);
    if (sfunc)
        sfunc(menu, _games, _displays);
    return menu;
}

bool Vm::run_menu(IGame *menu, IDisplay *display)
{
    menu->reset();
    display->open_window();
    while (!menu->get_end()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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

bool Vm::run_game(IGame *game, IDisplay *&display, Libdl *&display_lib)
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
            delete display_lib;
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

std::map<std::string, int> Vm::load_scores()
{
    std::map<std::string, int> scores;
    std::ifstream file("scores.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::size_t sep = line.find(':');
        if (sep != std::string::npos)
            scores[line.substr(0, sep)] = std::stoi(line.substr(sep + 1));
    }
    return scores;
}

void Vm::save_score(const std::string &game_name, int score)
{
    std::map<std::string, int> scores = load_scores();

    if (scores.find(game_name) == scores.end() || score > scores[game_name])
        scores[game_name] = score;

    std::ofstream file("scores.txt");
    for (auto &pair : scores)
        file << pair.first << ":" << pair.second << std::endl;
}

void Vm::main_boucle(std::string &default_display_path)
{
    Libdl *DefaultLib;
    Libdl *MenueLib;
    _current_display_path = default_display_path;
    IDisplay *Default = load_display(default_display_path, DefaultLib);
    IGame *menu;
    typedef std::string (*getterfunc)(IGame*);

    handle_lib();
    menu = load_menu(MenueLib);
    std::string symGetGame = "GetChosenGame";
    std::string symGetDisp = "GetChosenDisplay";
    std::string symSetScores = "SetScores";
    getterfunc gGame = MenueLib->DlSymbol<getterfunc>(symGetGame);
    getterfunc gDisp = MenueLib->DlSymbol<getterfunc>(symGetDisp);
    typedef void (*setscoresfunc)(IGame*, std::map<std::string, int>);
    setscoresfunc sScores = MenueLib->DlSymbol<setscoresfunc>(symSetScores);

    while (true) {
        if (sScores)
            sScores(menu, load_scores());
        if (!run_menu(menu, Default))
            break;

        std::string chosen_game = gGame(menu);
        std::string chosen_display = gDisp(menu);
        _current_display_path = chosen_display;

        Libdl *GameLib;
        Libdl *DisplayLib;
        typedef IGame* (*gamefunc)();
        GameLib = new Libdl(chosen_game);
        std::string symCreate = "CreateGame";
        IGame *game = GameLib->DlSymbol<gamefunc>(symCreate)();
        IDisplay *display = load_display(chosen_display, DisplayLib);

        run_game(game, display, DisplayLib);
        save_score(chosen_game, game->get_score());
        delete game;
        delete display;
        delete GameLib;
        delete DisplayLib;
    }
    delete Default;
    delete menu;
    delete DefaultLib;
    delete MenueLib;
}
