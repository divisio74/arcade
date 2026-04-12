#include "../../include/games/PacMan.hpp"

static const int MAP[21][21] = {
    {0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0},
    {0,1,1,2,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
    {3,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,3},
    {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,0,1,1,3,3,3,3,3,1,1,0,1,1,1,1,0},
    {0,0,0,0,2,1,1,0,3,3,3,3,3,0,1,1,2,0,0,0,0},
    {0,1,1,1,1,0,1,1,3,3,3,3,3,1,1,0,1,1,1,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1,1,0},
    {0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,1,0},
    {0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
    {0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,3,0,3,0,0,0,0,0,0,0,0,0}
};

PacMan::PacMan()
{
    _pacgumsLeft = 0;
    _score = 0;
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 21; x++) {
            _map[y][x] = MAP[y][x];
            if (_map[y][x] == 1 || _map[y][x] == 2)
                _pacgumsLeft++;
        }
    }
    _vunerabilityActivated = false;
    _ghostsOut = false;
    _gameOver= false;
    _won = false;
    _pacmanX = 9;
    _pacmanY = 13;
    _pacmanDirX = 0;
    _pacmanDirY = 0;
    _pacmanKeyDirX = 0;
    _pacmanKeyDirY = 0;
    _ghosts.push_back({8,  9,  1,  0, false, false});
    _ghosts.push_back({9,  9,  0,  1, false, false});
    _ghosts.push_back({10, 9, -1,  0, false, false});
    _ghosts.push_back({9, 10,  0, -1, false, false});
    _startTime = std::chrono::steady_clock::now();
}

bool PacMan::isWall(int x, int y)
{
    if (x < 0)
        x = 20;
    if (x > 20)
        x = 0;
    if (y < 0)
        y = 20;
    if (y > 20)
        y = 0;

    return _map[y][x] == 0;
}

void PacMan::movePacman()
{
    int nextX = _pacmanX + _pacmanKeyDirX;
    int nextY = _pacmanY + _pacmanKeyDirY;

    if (!isWall(nextX, nextY)) {
        _pacmanDirX = _pacmanKeyDirX;
        _pacmanDirY = _pacmanKeyDirY;
    }
    nextX = _pacmanX + _pacmanDirX;
    nextY = _pacmanY + _pacmanDirY;
    if (!isWall(nextX, nextY)) {
        _pacmanX = nextX;
        _pacmanY = nextY;
        if (_pacmanX < 0)
            _pacmanX = 20;
        if (_pacmanX > 20)
            _pacmanX = 0;
        if (_pacmanY < 0)
            _pacmanY = 20;
        if (_pacmanY > 20)
            _pacmanY = 0;
    }
    if (_map[_pacmanY][_pacmanX] == 1) {
        _map[_pacmanY][_pacmanX] = 3;
        _pacgumsLeft--;
        _score += 10;
    }
    else if (_map[_pacmanY][_pacmanX] == 2) {
        _map[_pacmanY][_pacmanX] = 3;
        _pacgumsLeft--;
        _score += 50;
    }if (_pacgumsLeft == 0)
        _won = true;
}

void PacMan::moveGhosts()
{
    float timePassed = std::chrono::duration<float>(std::chrono::steady_clock::now() - _startTime).count();

    if (!_ghostsOut && timePassed >= 10.0f)
        _ghostsOut = true;
    if (!_ghostsOut)
        return;
    
    int dx[4] = {1, -1, 0,  0};
    int dy[4] = {0,  0, 1, -1};

    for (int i = 0; i < 4; i++) {
        int nx = _ghosts[i]._x + _ghosts[i]._direction_x;
        int ny = _ghosts[i]._y + _ghosts[i]._direction_y;
        if (isWall(nx, ny)) {
            int tries = 0;
            while (tries < 10) {
                int r = rand() % 4;
                nx = _ghosts[i]._x + dx[r];
                ny = _ghosts[i]._y + dy[r];
                if (!isWall(nx, ny)) {
                    _ghosts[i]._direction_x = dx[r];
                    _ghosts[i]._direction_y = dy[r];
                    break;
                }
                tries++;
            }
        }
        _ghosts[i]._x += _ghosts[i]._direction_x;
        _ghosts[i]._y += _ghosts[i]._direction_y;
        if (_ghosts[i]._x < 0)
            _ghosts[i]._x = 20;
        if (_ghosts[i]._x > 20)
            _ghosts[i]._x = 0;
        if (_ghosts[i]._y < 0)
            _ghosts[i]._y = 20;
        if (_ghosts[i]._y > 20)
            _ghosts[i]._y = 0;
        if (_ghosts[i]._x == _pacmanX && _ghosts[i]._y == _pacmanY)
            _gameOver = true;
    }
}

void PacMan::update(arc::TouchSignal signal)
{
    if (signal.touch == arc::Touch::UP) {
        _pacmanKeyDirX = 0;
        _pacmanKeyDirY = -1;
    }
    if (signal.touch == arc::Touch::DOWN){
        _pacmanKeyDirX = 0;
        _pacmanKeyDirY = 1;
    }
    if (signal.touch == arc::Touch::LEFT){
        _pacmanKeyDirX = -1;
        _pacmanKeyDirY = 0;
    }
    if (signal.touch == arc::Touch::RIGHT){
        _pacmanKeyDirX =  1;
        _pacmanKeyDirY =  0;
    }
    if (!_gameOver && !_won) {
        movePacman();
        moveGhosts();
    }
    if (_won) {
        int score = _score;
        reset();
        _score = score;
    }
}

std::vector<arc::compo> PacMan::get_element()
{
    std::vector<arc::compo> elements;
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 21; x++) {
            arc::compo c;
            c.x = x;
            c.y = y;

            if (_map[y][x] == 0) {
                c.sprite = "#square";
                c.color = arc::Color::BLUE;
                elements.push_back(c);
            }
            else if (_map[y][x] == 1) {
                c.sprite = ".";
                c.color = arc::Color::WHITE;
                elements.push_back(c);
            }
            else if (_map[y][x] == 2) {
                c.sprite = "o";
                c.color = arc::Color::WHITE;
                elements.push_back(c);
            }
        }
    }
    arc::compo pacman;
    pacman.x = _pacmanX;
    pacman.y = _pacmanY;
    pacman.sprite = "#square";
    pacman.color = arc::Color::YELLOW;
    elements.push_back(pacman);

    arc::Color colors[4] = {
    arc::Color::RED,
    arc::Color::MAGENTA,
    arc::Color::CYAN,
    arc::Color::GREEN
    };
    for (int i = 0; i < 4; i++) {
        arc::compo ghost;
        ghost.x = _ghosts[i]._x;
        ghost.y = _ghosts[i]._y;
        ghost.sprite = "#square";
        ghost.color = colors[i % 4];
        elements.push_back(ghost);
    }
    arc::compo score;
    score.x = 0;
    score.y = 21;
    score.sprite = "Score: " + std::to_string(_score);
    score.color = arc::Color::WHITE;
    elements.push_back(score);
    return elements;
}

void PacMan::reset()
{
    _pacgumsLeft = 0;
    _score = 0;
    for (int y = 0; y < 21; y++) {
        for (int x = 0; x < 21; x++) {
            _map[y][x] = MAP[y][x];
            if (_map[y][x] == 1 || _map[y][x] == 2)
                _pacgumsLeft++;
        }
    }
    _vunerabilityActivated = false;
    _ghostsOut = false;
    _gameOver= false;
    _won = false;
    _pacmanX = 9;
    _pacmanY = 13;
    _pacmanDirX = 0;
    _pacmanDirY = 0;
    _pacmanKeyDirX = 0;
    _pacmanKeyDirY = 0;
    _ghosts.clear();
    _ghosts.push_back({8,  9,  1,  0, false, false});
    _ghosts.push_back({9,  9,  0,  1, false, false});
    _ghosts.push_back({10, 9, -1,  0, false, false});
    _ghosts.push_back({9, 10,  0, -1, false, false});
    _startTime = std::chrono::steady_clock::now();
}

bool PacMan::get_end()
{
    return _gameOver || _won;
}

int PacMan::get_score()
{
    return _score;
}


extern "C" PacMan *CreateGame()
{
    return new PacMan();
}