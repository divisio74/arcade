#include "../../include/libs/SDL2.hpp"

SDL2::SDL2() : _window(nullptr), _renderer(nullptr), _font(nullptr), _fontLoaded(false)
{

}

void SDL2::open_window()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void SDL2::clear_window()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

arc::TouchSignal SDL2::signal()
{
    arc::TouchSignal input_signal;
    SDL_Event event;

    input_signal.touch = arc::Touch::NONE;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            input_signal.touch = arc::Touch::ESCAPE;
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP)
                input_signal.touch = arc::Touch::UP;
            else if (event.key.keysym.sym == SDLK_DOWN)
                input_signal.touch = arc::Touch::DOWN;
            else if (event.key.keysym.sym == SDLK_LEFT)
                input_signal.touch = arc::Touch::LEFT;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                input_signal.touch = arc::Touch::RIGHT;
            else if (event.key.keysym.sym == SDLK_ESCAPE)
                input_signal.touch = arc::Touch::ESCAPE;
            else if (event.key.keysym.sym == SDLK_RETURN)
                input_signal.touch = arc::Touch::ENTER;
            else if (event.key.keysym.sym == SDLK_TAB)
                input_signal.touch = arc::Touch::TAB;
        }
    }
    return input_signal;
}

void SDL2::display(std::vector<arc::Compo> elems)
{
    clear_window();
    if (!_fontLoaded) {
        _font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20);
        _fontLoaded = true;
    }

     for (size_t i = 0; i < elems.size(); i++) {
        arc::Compo c = elems[i];

        SDL_Color color;
        if (c.color == arc::Color::GREEN)
            color = {0, 255, 0, 255};
        else if (c.color == arc::Color::RED)
            color = {255, 0, 0, 255};
        else if (c.color == arc::Color::CYAN)
            color = {0, 255, 255, 255};
        else if (c.color == arc::Color::YELLOW)
            color = {255, 255, 0, 255};
        else if (c.color == arc::Color::BLUE)
            color = {0, 0, 255, 255};
        else if (c.color == arc::Color::MAGENTA)
            color = {255, 0, 255, 255};
        else
            color = {255, 255, 255, 255};

        if (c.sprite.empty()) {
            SDL_Rect rect;
            rect.x = c.x * _cell_size;
            rect.y = c.y * _cell_size;
            rect.w = _cell_size;
            rect.h = _cell_size;
            SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(_renderer, &rect);
        } else {
            // a continuer la partie ou on v af ficher le texte
            // on va avoir besoin de la texture et surface a regarder
            // sur les docus dee SDL2 je crois il faut aussi charger le render pour
            // afficher ce qu'on dessine. Exactemznt comme CSFML
        }
     }
}

void SDL2::close_window()
{
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_Quit();
    SDL_Quit();
}

extern "C" IDisplay* CreateDisplay() {
    return new SDL2();
}