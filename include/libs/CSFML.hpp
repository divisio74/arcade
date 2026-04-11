

#ifndef CSFML_HPP
    #define CSFML_HPP

#include "../Vm/ADisplay.hpp"
#include <SFML/Graphics.hpp>

class CSFML : public ADisplay
{
    public:
        CSFML();
        ~CSFML() override = default;
        void display(std::vector<arc::Compo>) override;
        arc::TouchSignal signal() override;
        void open_window() override;
        void close_window() override;
        void clear_window() override;
    private:
        sf::RenderWindow* _window;
        int _cell_size = 30;
        sf::Font _font;
        bool _fontLoaded = false;
};

#endif
