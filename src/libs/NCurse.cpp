
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
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
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
    arc::TouchSignal sig;
    sig.touch = arc::Touch::NONE;

    int ch = getch();

    switch (ch) {
        case KEY_UP: sig.touch = arc::Touch::UP;
            break;
        case KEY_DOWN: sig.touch = arc::Touch::DOWN;
            break;
        case KEY_LEFT: sig.touch = arc::Touch::LEFT;
            break;
        case KEY_RIGHT: sig.touch = arc::Touch::RIGHT;
            break;
        case 10: sig.touch = arc::Touch::ENTER;
            break;
        case 27: sig.touch = arc::Touch::ESCAPE;
            break;
        case '\t': sig.touch = arc::Touch::TAB;
            break;
        default:
            break;
    }
    return sig;
}

void NCurse::display(std::vector<arc::Compo> elems)
{
    clear();

    int gameW = 20;
    int gameH = 20;
    int offsetX = 2; 
    int offsetY = 1;

    attron(COLOR_PAIR(3));
    mvprintw(offsetY, offsetX * 2 - 2, "+-");
    mvprintw(offsetY, offsetX * 2 + gameW * 2, "-+");
    mvprintw(offsetY + gameH + 1, offsetX * 2 - 2, "+-");
    mvprintw(offsetY + gameH + 1, offsetX * 2 + gameW * 2, "-+");
    for (int x = 0; x < gameW; x++) {
        mvprintw(offsetY, offsetX * 2 + x * 2, "--");
        mvprintw(offsetY + gameH + 1, offsetX * 2 + x * 2, "--");
    }
    for (int y = 1; y <= gameH; y++) {
        mvprintw(offsetY + y, offsetX * 2 - 2, "| ");
        mvprintw(offsetY + y, offsetX * 2 + gameW * 2, " |");
    }
    attroff(COLOR_PAIR(3));

    for (size_t i = 0; i < elems.size(); i++) {
        arc::Compo c = elems[i];

        int color = 1;
        if (c.color == arc::Color::GREEN)
            color = 2;
        else if (c.color == arc::Color::RED)
            color = 3;
        else if (c.color == arc::Color::CYAN)
           color = 4;
        else if (c.color == arc::Color::YELLOW)
            color = 5;
        else if (c.color == arc::Color::BLUE)
            color = 6;
        else if (c.color == arc::Color::MAGENTA)
            color = 7;
        else
            color = 1;

        bool isSprite = (c.sprite.find(".jpg") != std::string::npos ||
                         c.sprite.find(".png") != std::string::npos);

        attron(COLOR_PAIR(color));
        if (c.sprite.empty() || isSprite) {
            mvprintw(c.y + offsetY + 1, c.x * 2 + offsetX * 2, "[]");
        } else {
            mvprintw(c.y, c.x * 2, "%s", c.sprite.c_str());
        }
        attroff(COLOR_PAIR(color));
    }

    refresh();
}

extern "C" IDisplay* CreateDisplay() {
    return new NCurse();
}
