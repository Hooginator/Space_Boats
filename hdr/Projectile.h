#ifndef __PROJECTILE_H_INCLUDED__
#define __PROJECTILE_H_INCLUDED__

#include "stdio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL_functions.h"
#include <string>
#include <cstddef>
#include <math.h> 
#include "cstring"

// Constants
const int MAX_PROJECTILES = 10000; // Absolute maximim number of projectiles that are allowed


class Projectiles
{
  struct projectile{
  SDL_Surface* graphic;
  int graphic_number;
  double x_pos;
  double y_pos;
  double angle;
  double x_speed;
  double y_speed;
  // First order hitbox
  double radius;
  
  double damage;
  projectile* next;
  projectile* previous;
  };
public:  
  // Tracking for allowing me to go through the list of projectiles
  projectile *temp;
  
  //Constructor
  Projectiles(){
    head = NULL;
  }
  void moveProjectiles();
  void checkProjectilesandBoundaries(int SCREEN_WIDTH, int SCREEN_HEIGHT);
  void removeProjectile(projectile* todelete);
  double checkHit(double x, double y, double radius);
  void showProjectiles(SDL_Surface *screen);
  void addProjectile(double x_pos, double y_pos, double x_speed, double y_speed, double angle, double radius, double damage, SDL_Surface* graphic);
  struct projectile getHead();
  void reset_temp();
  double get_x_pos();
  double get_y_pos();
private:
  projectile *head;
};

#endif