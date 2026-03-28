
#ifndef INCLUDED_COMPO_HPP
    #define INCLUDED_COMPO_HPP

#include <string>

namespace arc {
    enum class Color {BLACK, RED, GREEN, BLUE, YELLOW, WHITE, CYAN, MAGENTA};
    enum class Touch {UP, DOWN, LEFT, RIGHT, ENTER, SCAPE, ESPACE, TAB, NONE};

    struct compo {
        int x;
        int y;
        char symbol;
        std::string sprite;
        Color color;
    };

    struct TouchSignal {
        Touch touch;
    };
}

#endif
