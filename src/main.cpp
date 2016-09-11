// headers
#include "SDL_functions.h"
#include "game.h"

int main( int argc, char* args[] )
{
    // Once Main_Menu is a thing call that instead of game, or maybe Main Menu will be defined here.  
  /* Ideally I will feed a lot more information into game.cppsuch as: 
  Level file (or pointer to it): Background, enemy list, type of enemy ships file
  Your Ship File: Visual, weapons and stats, experience?, upgrades
  */
  std::string Ships_File = "ships.dat";
    game(Ships_File);
    return 0;
}
