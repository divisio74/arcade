#include "../../include/games/Menue.hpp"

Menue::Menue(std::vector<std::string> games, std::vector<std::string> displays)
{
    _games = games;
    _displays = displays;
}


void Menue::update(arc::TouchSignal signal)
{
    std::size_t lib_len = _displays.size();
    std::size_t game_len = _games.size();

    if (signal.touch == arc::Touch::ENTER) {
        if (_section == 0)
            _selectedGame = _cursor;
        if (_section == 1)
            _selectedDisplay = _cursor;
        if (_selectedGame != -1 && _selectedDisplay != -1)
            _end = true;
    }

    if (signal.touch == arc::Touch::UP) {
        if (_cursor > 0)
            _cursor--;
    }

    if (signal.touch == arc::Touch::DOWN) {
        if (_section == 1) {
            if (_cursor < lib_len - 1)
                _cursor++;
        }
        if (_section == 0) {
            if (_cursor < game_len - 1)
                _cursor++;
        }
    }

    if (signal.touch == arc::Touch::LEFT) {
        if (_section == 1) {
            _section = 0;
            _cursor = 0;
        }
    }

    if (signal.touch == arc::Touch::RIGHT) {
        if (_section == 0) {
            _section = 1;
            _cursor = 0;
        }
    }
}

std::vector<arc::Compo> Menue::get_element()
{
    std::vector<arc::Compo> total;
    std::vector<arc::Compo> games;
    std::size_t lib_len = _displays.size();
    std::size_t game_len = _games.size();

    for (int i = 0; i < game_len; i++) {
        arc::Compo game;
        game.x = 2;
        game.y = 2 + i;
        game.sprite = _games[i];
        if (_section == 0 && i == _cursor)
            game.color = arc::Color::CYAN;
        else if (i == _selectedGame)
            game.color = arc::Color::YELLOW;
        else
            game.color = arc::Color::WHITE;
        total.push_back(game);
    }

    arc::Compo game_title;
    game_title.x = 2;
    game_title.y = 1;
    game_title.sprite = "Games :";
    game_title.color = arc::Color::WHITE;
    total.push_back(game_title);

    arc::Compo displays_title;
    displays_title.x = 2;
    displays_title.y = game_len + 2;
    displays_title.sprite = "Displays :";
    displays_title.color = arc::Color::WHITE;
    total.push_back(displays_title);


    for (int i = 0; i < lib_len; i++) {
        arc::Compo lib;
        lib.x = 2;
        lib.y = game_len + 4 + i;
        lib.sprite = _displays[i];
        if (_section == 1 && i == _cursor)
            lib.color = arc::Color::CYAN;
        else if (i == _selectedDisplay)
            lib.color = arc::Color::YELLOW;
        else
            lib.color = arc::Color::WHITE;
        total.push_back(lib);
    }
    return total;
}

extern "C" Menue *CreateGame() {
    return new Menue(std::vector<std::string> games, std::vector<std::string> displays);
}
