
#ifndef INCLUDED_IGAME_HPP
    #define INCLUDED_IGAME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Compo.hpp"

class IGame
{
    public:
        virtual ~IGame() = default;
        virtual void update(arc::TouchSignal) = 0;
        virtual std::vector<arc::Compo> get_element() = 0;
        virtual void reset() = 0;
        virtual bool get_end() = 0;
        virtual int get_score() = 0;

};

#endif
