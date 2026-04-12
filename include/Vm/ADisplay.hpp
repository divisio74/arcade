
#ifndef ADISPLAY_HPP
    #define ADISPLAY_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "Compo.hpp"
#include "IDisplay.hpp"

class ADisplay : public IDisplay
{
    public:
        ~ADisplay() override = default;
        void display(std::vector<arc::compo>) override = 0;
        arc::TouchSignal signal() override = 0;
        void open_window() override = 0;
        void close_window() override = 0;
        void clear_window() override = 0;

};

#endif
