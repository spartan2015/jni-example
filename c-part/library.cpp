#include "library.h"
#include <iostream>

char hello() {
    std::cout << "from c++ native library" << std::endl;
    return 'X';
}