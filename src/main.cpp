// headers
#include "SDL_functions.h"
#include "game.h"

int main( int argc, char* args[] )
{
    // Once Main_Menu is a thing call that instead of game
  std::string Ships_File = "ships.dat";
    game(Ships_File);
    return 0;
}
