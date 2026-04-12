
#ifndef IDISPLAY_HPP
    #define IDISPLAY_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "Compo.hpp"

class IDisplay
{
    public:
        virtual ~IDisplay() = default;
        virtual void display(std::vector<arc::compo>) = 0;
        virtual arc::TouchSignal signal() = 0;
        virtual void open_window() = 0;
        virtual void close_window() = 0;
        virtual void clear_window() = 0;

};

#endif
