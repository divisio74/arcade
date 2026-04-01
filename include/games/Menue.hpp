
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
    private:
        int _score = 0;
};

#endif
