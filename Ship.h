#ifndef __SHIP_H_INCLUDED__
#define __SHIP_H_INCLUDED__



#include "stdio.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL_functions.h"
#include "Weapon_Template.h"

#include <string>

class Ships
{
  struct ship{
    // graphic will just be a pointer to the ship[i] array of SDL_Surfaces as there will be multiple ship instances that point to the same image 
    SDL_Surface* graphic;
    double x_pos;
    double y_pos;
    double x_vel;
    double y_vel;
    double x_accel;
    double y_accel;
    // orientation
    double angle;
    
    // Want to get rid of max_speed
    double max_speed;
    double max_force;
    double mass;
    bool auto_fire;
    
    //Hitbox properties
    double radius;
    
    // Dictates how the ship will move.  lets call 0 the arrow keys
    int controls;
    // For tracking where you are along a pre registered path
    int flight_time;
    
    // Health
    double max_hp;
    double current_hp;
    double collide_damage;
    
    Weapons *weapons;
    ship *next;
    ship *previous;
  };
public:
  Ships()
  {// Constructor
    head = NULL;//new ship;
    //head->next = NULL;
    //head->previous = NULL;
    //head->weapons = NULL;
  }
  bool moveShips(bool &quit,  int SCREEN_HEIGHT, int SCREEN_WIDTH);
  bool addShip(double x_pos, double y_pos, double angle, double max_speed, double mass, double max_force, bool auto_fire, double radius, double max_hp, 
	       double collide_damage, SDL_Surface* graphic, int controls, int nweapons, int *weapons, Weapon_Template *templates);
  bool removeShip(ship *todelete);
  bool addWeapon(double x_pos, double y_pos, double angle, int firing_rate,
    int projectile_speed, double projectile_radius, double damage, SDL_Surface* weapon_graphic, SDL_Surface* projectile_graphic, int firing_pattern);
  bool showShips(SDL_Surface *screen);
  bool generateProjectiles(Projectiles* projectiles, Ships *target);
  bool getPremadePath(int type, int &flight_time, double max_speed, double max_accel, double &x_accel, double &y_accel, double &xtomove, double &ytomove, int SCREEN_HEIGHT, int SCREEN_WIDTH);
  bool keepOnScreen(double &x_accel, double &y_accel, double max_accel, double x_pos, double y_pos, int SCREEN_HEIGHT, int SCREEN_WIDTH, double graphic_height, double graphic_weight);
  bool addWeapons();
  bool checkProjectileHit(Projectiles* projectiles);
  bool checkShipHit(Ships* other_ships);
  double checkHit(double x, double y, double radius);
  bool getLocation(double &target_x_pos, double &target_y_pos, double &target_x_vel, double &target_y_vel, double &target_x_accel, double &target_y_accel);
  bool calculateVelocitiesold(double new_x, double new_y, double &x_pos, double &y_pos, double &x_vel, double &y_vel, double &x_accel, double &y_accel);
  bool calculateVelocities(double &x_vel, double &y_vel, double &x_accel, double &y_accel);
  bool calculatePositions(double &x_pos, double &y_pos, double &x_vel, double &y_vel);
private:
  ship *head;
  
};

#endif