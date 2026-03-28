
#include "TermDisplay.hpp"

TermDisplay::TermDisplay()
{

}

void TermDisplay::display(std::string str)
{
    std::cout << str;
}

extern "C" IDisplay* CreateDisplay() {
    return new TermDisplay();
}


