#include "window/GameWindow.hpp"

#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    GameWindow gameWindow;
    gameWindow.run();
    return 0;
}
