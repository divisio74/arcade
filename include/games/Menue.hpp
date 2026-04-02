
#ifndef INCLUDED_MENUE_HPP
    #define INCLUDED_MENUE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Vm/AGame.hpp"

class Menue : public AGame
{
    public:
        Menue();
        ~Menue() override = default;
        void update(arc::TouchSignal) override;
        std::vector<arc::Compo> get_element() override;
        void reset() override;
        bool get_end() override;
        int get_score() override;
        std::string get_lib();
        std::string get_game();
        void set_games(std::vector<std::string> games);
        void set_displays(std::vector<std::string> displays);

    private:
        std::vector<std::string> _games;
        std::vector<std::string> _displays;
        std::size_t _cursor = 0;
        int _section = 0;
        int _selectedGame = -1;
        int _selectedDisplay = -1;
        bool _end = false;

};

#endif
