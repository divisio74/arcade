#ifndef PACMAN_HPP
    #define PACMAN_hpp

    #include "../Vm/AGame.hpp"
    #include <vector>
    #include <chrono>

    class PacMan : public AGame
    {
    private:
        struct Ghost
        {
            int _x;
            int _y;
            int _direction_x;
            int _direction_y;
            bool _vunerable;
            bool _eaten;
        };
        std::vector<Ghost> _ghosts;
        std::chrono::steady_clock::time_point _vunerabilityStart;
        bool _vunerabilityActivated;
        bool _ghostsOut;

        int _pacmanX;
        int _pacmanY;
        int _pacmanDirX;
        int _pacmanDirY;
        int _pacmanKeyDirX;
        int _pacmanKeyDiry;

        std::chrono::steady_clock::time_point _startTime;
        int _map[20][20];
        int _score;
        int _pacgumsLeft;
        bool _gameOver;
        bool _won;
            
    public:
        PacMan();
        ~PacMan() override = default;
        void update(arc::TouchSignal signal) override;
        std::vector<arc::Compo> get_element() override;
        void reset() override;
        bool get_end() override;
        int  get_score() override;
    };
    
#endif