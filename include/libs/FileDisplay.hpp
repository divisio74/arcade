
#ifndef FILEDISPLAY_HPP
    #define FILEDISPLAY_HPP

#include <iostream>
#include "IDisplay.hpp"

class FileDisplay : public IDisplay
{
    public:
        FileDisplay();
        ~FileDisplay() = default;

        void display(std::string);
    private:
};

#endif
