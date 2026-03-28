
#ifndef INCLUDED_COUNTERGAME_HPP
    #define INCLUDED_COUNTERGAME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "IGame.hpp"

class countergame : public IGame
{
    public:
        countergame();
        ~countergame() = default;
        void update(signal);
        std::vector<std::string> get_front_layer();
        std::vector<std::string> get_back_layer();
        std::vector<std::string> get_end();
        std::vector<std::string> get_start();
        int _score = 0;
    private:
        int _counter = 0;
};

#endif
