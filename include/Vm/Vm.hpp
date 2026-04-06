
#ifndef INCLUDED_VM_HPP
    #define INCLUDED_VM_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Libdl.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"

class Vm
{
    public:
        ~Vm() = default;
        int handle_lib();
        void main_boucle(std::string &default_display_path);

    private:
        IDisplay *load_display(std::string &path, Libdl *&lib);
        IGame *load_menu(Libdl *&lib);
        bool run_menu(IGame *menu, IDisplay *display);
        bool run_game(IGame *game, IDisplay *&display, Libdl *&lib);

        std::vector<std::string> _games;
        std::vector<std::string> _displays;
        std::string              _current_display_path;
};

#endif
