#include "countergame.hpp"

countergame::countergame()
{

}

void countergame::update()
{
    _counter++;
}

std::vector<std::string> countergame::get_element()
{
    std::vector<std::string> vector;
    vector.push_back(std::to_string(_counter));
    return vector;
}

extern "C" countergame *CreateGame() {
    return new countergame();
}
