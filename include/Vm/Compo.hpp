
#ifndef INCLUDED_COMPO_HPP
    #define INCLUDED_COMPO_HPP

#include <string>
#include <vector>

namespace arc {
    enum class Color {BLACK, RED, GREEN, BLUE, YELLOW, WHITE, CYAN, MAGENTA};
    enum class Touch {UP, DOWN, LEFT, RIGHT, ENTER, ESCAPE, SPACE, TAB, NONE};

    struct Compo {
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
