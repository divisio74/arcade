#ifndef SDL2_HPP
    #define SDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Vm/ADisplay.hpp"

class SDL2 : public ADisplay
{
    public:
        SDL2();
        ~SDL2() override = default;
        void display(std::vector<arc::compo>) override;
        arc::TouchSignal signal() override;
        void open_window() override;
        void close_window() override;
        void clear_window() override;
    private:
        SDL_Window*   _window;
        SDL_Renderer* _renderer;
        TTF_Font*     _font;
        bool          _fontLoaded;
        int           _cell_size = 20;
};

#endif
