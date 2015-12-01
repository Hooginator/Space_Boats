#include "stdio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL_functions.h"

class Powerups
{
  struct powerup{
    SDL_Surface *graphic;
    double x_pos; 
    double y_pos;
    double max_speed;
    
    double radius;
    
    
  };
  
};