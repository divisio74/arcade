# Arcade - Documentation architecture

- Mail of the group : Pierre.baud@epitech.eu

## Compilation

- Standard : **C++20** (`-std=c++20`)
- Compilateur : **g++**
- Les `.so` doivent etre compiles avec `-shared -fPIC`

## Factory functions (extern "C")

Chaque `.so` doit exposer **une** de ces fonctions :

```cpp
extern "C" IGame* CreateGame();       // pour les jeux
extern "C" IDisplay* CreateDisplay(); // pour les libs graphiques
```

## Fichiers partages

Trois fichiers a inclure tels quels : `IGame.hpp`, `IDisplay.hpp`, `Compo.hpp`.

Attention il faut utiliser la meme taille de sprite et de grille pour garantir que les jeux/lib passe sur les deux programme :

taille de la grille -> 20 par 20
taille des sprites -> 32 par 32

donc 1 compo = 1 case = 1 sprite == FACILE !

---

## Compo.hpp

```cpp
namespace arc {
    enum class Color {BLACK, RED, GREEN, BLUE, YELLOW, WHITE, CYAN, MAGENTA};
    enum class Touch {UP, DOWN, LEFT, RIGHT, ENTER, ESCAPE, SPACE, TAB, NONE};

    struct compo {
        int x;          // position x sur la grille
        int y;          // position y sur la grille
        char symbol;    // caractere affiche (ncurses)
        std::string sprite; // chemin vers le sprite (SFML/SDL2)
        Color color;
    };

    struct TouchSignal {
        Touch touch;
    };
}
```

## IGame.hpp

```cpp
class IGame {
    virtual ~IGame() = default;
    virtual void update(arc::TouchSignal) = 0;  // met a jour le jeu selon l'input
    virtual std::vector<arc::compo> get_element() = 0; // renvoie les elements a afficher
    virtual void reset() = 0;                    // reinitialise le jeu
    virtual bool is_finish() = 0;                // true si game over
};
```

## IDisplay.hpp

```cpp
class IDisplay {
    virtual ~IDisplay() = default;
    virtual void display(std::vector<arc::compo>) = 0; // affiche les elements
    virtual arc::TouchSignal signal() = 0;              // capture l'input
    virtual void open_window() = 0;
    virtual void close_window() = 0;
    virtual void clear_window() = 0;
};
```



## Jeux : Snake, Pacman

## Libs graphiques : nCurses, SDL2 (`arcade_sdl2.so`), SFML
