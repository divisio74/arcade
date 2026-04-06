#include <dlfcn.h>
#include "include/Vm/Vm.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 0;

    Vm vm;
    std::string display_path = argv[1];
    vm.main_boucle(display_path);
    return 0;
}
