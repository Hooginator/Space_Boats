
#ifndef __SHIP_SPAWNER_H_INCLUDED__
#define __SHIP_SPAWNER_H_INCLUDED__

#include "stdio.h"
#include <string>
#include "Ship.h"
#include <fstream>

//Maximum Number of Ship Images
const int unique_ships = 10;
// Most weapons a ship will ever have
const int max_weapons = 5;

class Ship_Spawner
{
  struct ship{
    double x_pos;
    double y_pos;
    double angle;
    int flight_pattern;
    
    int ship_type;
    int ships_to_spawn;
    int spawn_time;
    int separation;
    
    int nweapons;
    int weapons[max_weapons];
    
    ship *next;
    ship *previous;
  };
  struct ship_template{
    SDL_Surface* graphic;
    double max_speed;
    double mass;
    double max_force;
    double radius;
    double max_hp;
    double collide_damage;
    int nweapons;
    int weapons[max_weapons];
  };
public:
  Ship_Spawner()
  {
    head = NULL;
  }
  bool addSpawner(double x_pos, double y_pos, double angle, int flight_pattern, int ship_type, int ships_to_spawn, int separation, int spawn_time);
  bool spawnShips(int time, Ships *ships, Weapon_Template *weapons);
  bool loadTemplates(std::string filename);
  bool removeSpawner(ship *todelete);
  bool loadSpawners(std::string filename);
  
private:
  ship *head;
  ship_template templates[unique_ships];
};

#endif