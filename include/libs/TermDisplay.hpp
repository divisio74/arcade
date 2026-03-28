
#ifndef TERMDISPLAY_HPP
    #define TERMDISPLAY_HPP

#include <iostream>
#include "IDisplay.hpp"

class TermDisplay : public IDisplay
{
    public:
        TermDisplay();
        ~TermDisplay() = default;

        void display(std::string);
    private:
};

#endif
