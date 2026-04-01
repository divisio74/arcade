#include "../../include/games/Menue.hpp"

Menue::Menue()
{

}

void Menue::update()
{
    _counter++;
}

std::vector<std::string> Menue::get_element()
{
    std::vector<std::string> vector;
    vector.push_back(std::to_string(_counter));
    return vector;
}

extern "C" Menue *CreateGame() {
    return new Menue();
}
