#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main() {
    srand(time(NULL));
    Game g;
    g.StartGame();
    return 0;
}
