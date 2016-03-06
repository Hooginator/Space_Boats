#include "stdio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL_functions.h"

#include "Weapon_Template.h"
#include "Ship_Spawner.h"
#include <string>
#include <cstddef>
#include <math.h> 
#include "cstring"

#include "unistd.h" // For usleep() function
#include "time.h"

int game(std::string Ships_File);

bool Move_Ship(bool &quit);
bool Move_Enemy_Ships();
bool Move_Background(int &background1_x_pos, int &background1_y_pos, int &background2_x_pos, int &background2_y_pos);
bool Generate_Projectiles();
bool Handle_Projectiles();