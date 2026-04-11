#include "../../include/libs/CSFML.hpp"

CSFML::CSFML() : _window(nullptr), _fontLoaded(false)
{

}

void CSFML::open_window()
{
    _window = new sf::RenderWindow(sf::VideoMode(800, 800), "Arcade");
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
        _window->clear(sf::Color::Black);
}

arc::TouchSignal CSFML::signal()
{
    arc::TouchSignal input_signal;
    sf::Event event;

    input_signal.touch = arc::Touch::NONE;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            input_signal.touch = arc::Touch::ESCAPE;
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up)
                input_signal.touch = arc::Touch::UP;
            else if (event.key.code == sf::Keyboard::Down)
                input_signal.touch = arc::Touch::DOWN;
            else if (event.key.code == sf::Keyboard::Left)
                input_signal.touch = arc::Touch::LEFT;
            else if (event.key.code == sf::Keyboard::Right)
                input_signal.touch = arc::Touch::RIGHT;
            else if (event.key.code == sf::Keyboard::Escape)
                input_signal.touch = arc::Touch::ESCAPE;
            else if (event.key.code == sf::Keyboard::Enter)
                input_signal.touch = arc::Touch::ENTER;
            else if (event.key.code == sf::Keyboard::Tab)
                input_signal.touch = arc::Touch::TAB;
        }
    }
    return input_signal;
}
void CSFML::display(std::vector<arc::Compo> elems)
{
    if (!_window)
        return;
    _window->clear(sf::Color::Black);

    if (!_fontLoaded) {
        _font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
        _fontLoaded = true;
    }

    for (size_t i = 0; i < elems.size(); i++) {
        arc::Compo c = elems[i];

        sf::Color sfColor;
        if (c.color == arc::Color::GREEN)
            sfColor = sf::Color::Green;
        else if (c.color == arc::Color::RED)
            sfColor = sf::Color::Red;
        else if (c.color == arc::Color::CYAN)
            sfColor = sf::Color::Cyan;
        else if (c.color == arc::Color::YELLOW)
            sfColor = sf::Color::Yellow;
        else if (c.color == arc::Color::BLUE)
            sfColor = sf::Color::Blue;
        else if (c.color == arc::Color::MAGENTA)
            sfColor = sf::Color::Magenta;
        else
            sfColor = sf::Color::White;

        if (c.sprite.empty() || c.sprite == "carre.jpg") {
            sf::RectangleShape rect(sf::Vector2f(_cell_size, _cell_size));
            rect.setPosition(c.x * _cell_size, c.y * _cell_size);
            rect.setFillColor(sfColor);
            _window->draw(rect);
        } else {
            sf::Text text;
            text.setFont(_font);
            text.setString(c.sprite);
            text.setCharacterSize(_cell_size);
            text.setPosition(c.x * _cell_size + 10 , c.y * _cell_size - 10);
            text.setFillColor(sfColor);
            _window->draw(text);
        }
    }
    _window->display();
}

extern "C" IDisplay* CreateDisplay() {
    return new CSFML();
}