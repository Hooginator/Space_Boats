
#ifndef __WEAPON_H_INCLUDED__
#define __WEAPON_H_INCLUDED__

#include "stdio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <limits>
#include <cstdlib>
#include "Projectile.h"


const int pi = 3.141592653589;


class Weapons
{
  struct weapon
  {
    // graphic will just be a pointer to the ship[i] array of SDL_Surfaces as there will be multiple ship instances that point to the same image 
    SDL_Surface* weapon_graphic;
    SDL_Surface* projectile_graphic;
    double x_pos;
    double y_pos;
    // Angle is in radians and starts forward x zero y when the angle is 0.  Rotates clockwise
    double angle;
    // Number of frames between each shot.  
    int firing_rate;
    // Number of frames since the weapon last fired.
    int last_fired;
    int projectile_speed;
    int firing_pattern;
    
    //Hitbox detection
    double projectile_radius;
    
    double damage;
    
    weapon *next;
    weapon *previous;
  };
  
public:
  Weapons()
  {//Constructor
    head = NULL;
  }
  bool generateProjectiles(Projectiles* projectiles, double x_pos, double y_pos, double angle, double target_x_pos, double target_y_pos, double target_x_vel, double target_y_vel, double target_x_accel, double target_y_accel);
  bool addWeapon(double x_pos, double y_pos, double angle, int firing_rate,int projectile_speed, double projectile_radius, double damage, SDL_Surface* weapon_graphic, SDL_Surface* projectile_graphic,int firing_pattern);
  bool addWeapon(int type);
  double aimWeapon(double x_pos, double y_pos, double target_x_pos, double target_y_pos, double x_speed, double y_speed, double angle_min, double angle_max, int strategy);
private:
  weapon* head;
};

#endif