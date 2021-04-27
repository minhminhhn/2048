#include <iostream>
#include <ctime>
#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand (time(NULL));
    start();
    quitSDL();
    return 0;
}

