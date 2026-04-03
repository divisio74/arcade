
#include "../../include/libs/NCurse.hpp"
#include <ncurses.h>

NCurse::NCurse()
{

}

void NCurse::open_window()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
}

void NCurse::close_window()
{
    endwin();
}

void NCurse::clear_window()
{
    clear();
}

arc::TouchSignal NCurse::signal()
{

}

void NCurse::display(std::vector<arc::Compo>)
{

}

extern "C" IDisplay* CreateDisplay() {
    return new NCurse();
}


