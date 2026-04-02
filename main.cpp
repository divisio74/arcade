#include <dlfcn.h>
#include "include/Vm/Vm.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2)
        return 0;

    Vm vm;
    vm.main_boucle(argv[1]);
    return 0;
}
