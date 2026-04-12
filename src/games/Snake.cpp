#include "../../include/games/Snake.hpp"

Snake::Snake()
{
    reset();
}

void Snake::reset()
{
    _score = 0;
    _end = false;
    _snake.clear();
    _snake.push_back({6,10});
    _snake.push_back({5,10});
    _snake.push_back({4,10});
    _snake.push_back({3,10});
    _dir = arc::Touch::RIGHT;
    spawn_apple();

}

void Snake::spawn_apple()
{
    bool good_spawn = false;
    while (!good_spawn) {
        _apple.first = rand() % 19 + 1;
        _apple.second = rand() % 19 + 1;
        good_spawn = true;
        for (size_t i = 0; i < _snake.size(); i++) {
            if (_snake[i] == _apple) {
                good_spawn = false;
                break;
            }
        }
    }
}

void Snake::update(arc::TouchSignal input)
{
    if ((input.touch == arc::Touch::UP    && _dir != arc::Touch::DOWN)  ||
        (input.touch == arc::Touch::DOWN  && _dir != arc::Touch::UP)    ||
        (input.touch == arc::Touch::LEFT  && _dir != arc::Touch::RIGHT) ||
        (input.touch == arc::Touch::RIGHT && _dir != arc::Touch::LEFT))
        _dir = input.touch;

    std::pair<int,int> head = _snake.front();

    if (_dir == arc::Touch::UP)
        head.second--;
    if (_dir == arc::Touch::DOWN)
        head.second++;
    if (_dir == arc::Touch::RIGHT)
        head.first++;
    if (_dir == arc::Touch::LEFT)
        head.first--;

    if (head.first < 1 || head.first > 19 || head.second < 1 || head.second > 19) {
        _end = true;
        return;
    }

    for (size_t i = 0; i < _snake.size() - 1; i++) {
        if (_snake[i] == head) {
            _end = true;
            return;
        }
    }
    _snake.insert(_snake.begin(), head);

    if (head == _apple) {
        _score++;
        spawn_apple();
    } else {
        _snake.pop_back();
    }
}

std::vector<arc::Compo> Snake::get_element()
{
    std::vector<arc::Compo> element;

    for (int x = 0; x < 21; x++) {
        arc::Compo c;
        c.sprite = "carre.jpg";
        c.color = arc::Color::BLUE;
        c.x = x;
        c.y = 0; 
        element.push_back(c);
        c.y = 20;
        element.push_back(c);
    }
    for (int y = 0; y < 21; y++) {
        arc::Compo c;
        c.sprite = "carre.jpg";
        c.color = arc::Color::BLUE;
        c.y = y;
        c.x = 0;
        element.push_back(c);
        c.x = 20;
        element.push_back(c);
    }
    for (size_t i = 0; i < _snake.size(); i++)
    {
        arc::Compo c;
        c.x = _snake[i].first;
        c.y = _snake[i].second;
        c.sprite = "carre.jpg";
        if (i == 0)
            c.color = arc::Color::CYAN;
        else
            c.color = arc::Color::GREEN;
        element.push_back(c);
    }

    arc::Compo apple;
    apple.x = _apple.first;
    apple.y = _apple.second;
    apple.sprite = "carre.jpg";
    apple.color = arc::Color::RED;
    element.push_back(apple);

    arc::Compo score;
    score.x = 0;
    score.y = 21;
    score.sprite = "Score: " + std::to_string(_score);
    score.color = arc::Color::WHITE;
    element.push_back(score);
    return element;
}

bool Snake::get_end()
{
    return _end;
}

int Snake::get_score()
{
    return _score;
}

extern "C" Snake *CreateGame()
{
    return new Snake();
}