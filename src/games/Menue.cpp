#include "../../include/games/Menue.hpp"

Menue::Menue()
{

}


void Menue::update(arc::TouchSignal signal)
{
    int lib_len = _displays.size();
    int game_len = _games.size();

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

std::vector<arc::compo> Menue::get_element()
{
    std::vector<arc::compo> total;
    int lib_len = _displays.size();
    int game_len = _games.size();

    for (int i = 0; i < game_len; i++) {
        arc::compo game;
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

    arc::compo game_title;
    game_title.x = 2;
    game_title.y = 1;
    game_title.sprite = "Games :";
    game_title.color = arc::Color::WHITE;
    total.push_back(game_title);

    arc::compo displays_title;
    displays_title.x = 2;
    displays_title.y = game_len + 2;
    displays_title.sprite = "Displays :";
    displays_title.color = arc::Color::WHITE;
    total.push_back(displays_title);


    for (int i = 0; i < lib_len; i++) {
        arc::compo lib;
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

    int scores_y = game_len + 4 + lib_len + 1;
    arc::compo scores_title;
    scores_title.x = 2;
    scores_title.y = scores_y;
    scores_title.sprite = "Best Scores :";
    scores_title.color = arc::Color::WHITE;
    total.push_back(scores_title);

    int row = 1;
    for (auto &pair : _scores) {
        arc::compo s;
        s.x = 2;
        s.y = scores_y + row;
        s.sprite = pair.first + " : " + std::to_string(pair.second);
        s.color = arc::Color::GREEN;
        total.push_back(s);
        row++;
    }
    return total;
}

void Menue::reset()
{
    _cursor = 0;
    _section = 0;
    _selectedGame = -1;
    _selectedDisplay = -1;
    _end = false;
}

bool Menue::get_end()
{
    return _end;
}

int Menue::get_score()
{
    return 0;
}

std::string Menue::get_lib()
{
    if (_selectedDisplay == -1)
        return "";
    return _displays[_selectedDisplay];
}

std::string Menue::get_game()
{
    if (_selectedGame == -1)
        return "";
    return _games[_selectedGame];
}

void Menue::set_games(std::vector<std::string> games)
{
    _games = games;
}

void Menue::set_displays(std::vector<std::string> displays)
{
    _displays = displays;
}

void Menue::set_scores(std::map<std::string, int> scores)
{
    _scores = scores;
}


extern "C" Menue *CreateGame() {
    return new Menue();
}

extern "C" void SetLists(IGame *game, std::vector<std::string> games, std::vector<std::string> displays) {
    Menue *m = static_cast<Menue*>(game);
    m->set_games(games);
    m->set_displays(displays);
}

extern "C" std::string GetChosenGame(IGame *game) {
    return static_cast<Menue*>(game)->get_game();
}

extern "C" std::string GetChosenDisplay(IGame *game) {
    return static_cast<Menue*>(game)->get_lib();
}

extern "C" void SetScores(IGame *game, std::map<std::string, int> scores) {
    static_cast<Menue*>(game)->set_scores(scores);
}
