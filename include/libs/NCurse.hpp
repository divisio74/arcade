

#ifndef NCURSE_HPP
    #define NCURSE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "Compo.hpp"
#include "../Vm/ADisplay.hpp"

class NCurse : public ADisplay
{
    public:
        NCurse();
        ~NCurse() override = default;
        void display(std::vector<arc::Compo>) override;
        arc::TouchSignal signal() override;
        void open_window() override;
        void close_window() override;
        void clear_window() override;

};

#endif
