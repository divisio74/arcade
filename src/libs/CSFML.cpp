#include "CSFML.hpp"

CSFML::CSFML() : _window(nullptr)
{

}

CSFML::~CSFML()
{
    close_window();
}

void CSFML::open_window()
{
    _window = new sf::RenderWindow(sf::VideoMode(640, 640), "Arcade");
}

void CSFML::close_window()
{
    if (_window) {
        _window->close();
        delete _window;
        _window = nullptr;
    }
}

void CSFML::clear_window()
{
    if (_window)
        _window->clear();
}
