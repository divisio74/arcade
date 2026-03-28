
#include "FileDisplay.hpp"

FileDisplay::FileDisplay()
{

}

void FileDisplay::display(std::string str)
{
    std::ofstream fichier("test.txt", std::ios::in);

    if(fichier) {
        fichier << str;
    } else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    return;
}

extern "C" IDisplay* CreateDisplay() {
    return new FileDisplay();
}


