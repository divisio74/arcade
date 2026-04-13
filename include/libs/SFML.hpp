

#ifndef SFML_HPP
    #define SFML_HPP

#include "../Vm/ADisplay.hpp"
#include <SFML/Graphics.hpp>

class SFML : public ADisplay
{
    public:
        SFML();
        ~SFML() override = default;
        void display(std::vector<arc::compo>) override;
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
