#ifndef __WEAPON_TEMPLATE_H_INCLUDED__
#define __WEAPON_TEMPLATE_H_INCLUDED__

#include "stdio.h"
#include <fstream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#include "Weapon.h"

const int unique_templates = 20;

class Weapon_Template
{
  struct Template{
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
    int projectile_speed;
    int firing_pattern;
    
    //Hitbox detection
    double projectile_radius;
    
    double damage;
  };
public:
  //Constructor
  Weapon_Template()
  {
  }
  
  bool loadTemplate(std::string filename);
  bool addWeapon(int type, Weapons *weapon);
private:
  Template templates[unique_templates];
};

#endif