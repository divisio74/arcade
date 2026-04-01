
#ifndef SNAKE_HPP
    #define SNAKE_HPP

    #include "../Vm/AGame.hpp"

class Snake : public AGame
{
    public:
        Snake();
        ~Snake() override = default;
        void update(arc::TouchSignal) override;
        std::vector<arc::Compo> get_element() override;
        void reset() override;
        bool get_end() override;
        int get_score() override;
    private:
        int _score = 0;
        std::vector<std::pair<int,int>> _snake;
        std::pair<int,int> _apple;
        arc::Touch _dir;
        bool _end;
        void spawn_apple();
};

#endif
