
#ifndef INCLUDED_AGAME_HPP
    #define INCLUDED_AGAME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Compo.hpp"
#include "IGame.hpp"

class AGame : public IGame
{
    public:
        ~AGame() override = default;
        void update(arc::TouchSignal) override = 0;
        std::vector<arc::Compo> get_element() override = 0;
        void reset() override = 0;
        bool get_end() override = 0;
        int get_score() override = 0;
        


};

#endif
