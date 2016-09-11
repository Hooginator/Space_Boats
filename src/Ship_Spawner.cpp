#include "Ship_Spawner.h"

bool Ship_Spawner::addSpawner(double x_pos, double y_pos, double angle, int flight_pattern, int ship_type, int ships_to_spawn, int separation, int spawn_time)
{
  printf("Ship_Spawner:addSpawner\n");
  ship *a = new ship;
  a->x_pos = x_pos;
  a->y_pos = y_pos;
  a->angle = angle;
  a->flight_pattern = flight_pattern;
  a->ship_type = ship_type;
  a->ships_to_spawn = ships_to_spawn;
  a->separation = separation;
  a->spawn_time = spawn_time;
  a->next = head;
  a->previous = NULL;
  if(head != NULL)
  {
    head->previous = a;
  }
  head = a;
}

bool Ship_Spawner::spawnShips(int time, Ships *ships, Weapon_Template *weapons)
{
  //printf("SHIP_SPAWNER:SPAWNSHIPS\n");
  ship *a = head;
  ship *b = head;
  int num;
  while(a != NULL)
  {
    if(a->spawn_time < time)
    {
      num = a->ship_type;
      ships->addShip(a->x_pos, a->y_pos, a->angle, templates[num].max_speed, templates[num].mass, templates[num].max_force, true, templates[num].radius, templates[num].max_hp, 
		     templates[num].collide_damage, templates[num].graphic, a->flight_pattern, templates[num].nweapons, templates[num].weapons, weapons);
      a->ships_to_spawn --;
      if(a->ships_to_spawn > 0)
      {
	a->spawn_time += a->separation;
	a = a->next;
      }
      else
      {
	b = a->next;
	removeSpawner(a);
	a = b;
      }
      
    }
    else
    {
      a = a->next;
    }
    num ++;
  }

}


bool Ship_Spawner::loadTemplates(std::string filename)
{
  std::ifstream file;
  file.open(filename.c_str());
  if(file.fail())
  {
    printf("Error loading ship templates \n");
    return false;
  }
  
  std::string graphic_file;
  int num = 0;
  printf("Bug Here, fix is use XML files.  ");
  // OK, so I got it to recognize when # is the first character!! BUUUT now it doesn't work.  it either constantly reads the first line
  // OR graphic_file doesn't change after the first run.
  // either way, graphics_file is '#' after the first line even though only 1 line starts with #
  // JUST CHANGE TO FUCKING XML
  bool done = false;
  while(!done){
    if(file >> graphic_file >> templates[num].max_speed >> templates[num].mass >> templates[num].max_force  >> templates[num].radius >> templates[num].max_hp >> templates[num].collide_damage 
  >> templates[num].nweapons)
    {
      if(load_files(templates[num].graphic, graphic_file) == false)
      {
	return 1;
      }
      int i = 0;
      while(i < templates[num].nweapons)
      {
	file >> templates[num].weapons[i];
	i++;
      }
      num ++;
      
    }else{
      if(graphic_file.at(0) == '#'){
	printf("Commented Line Detected\n");
      }else{
	done = true;
      }
    }
  }
  
  /*while(file >> graphic_file >> templates[num].max_speed >> templates[num].mass >> templates[num].max_force  >> templates[num].radius >> templates[num].max_hp >> templates[num].collide_damage 
    >> templates[num].nweapons)
  {
    if(load_files(templates[num].graphic, graphic_file) == false)
    {
      return 1;
    }
    int i = 0;
    while(i < templates[num].nweapons)
    {
      file >> templates[num].weapons[i];
      i++;
    }
    num ++;
  }*/
}
bool Ship_Spawner::loadSpawners(std::string filename)
{
  //printf(filename.c_str());
  std::ifstream file;
  file.open(filename.c_str());
  if(file.fail())
  {
    printf("Error loading ship spawners \n");
    return false;
  }
  int num = 0;
  
  double x_pos;
  double y_pos;
  double angle;
  int flight_pattern;
  int ship_type;
  int ships_to_spawn;
  int separation;
  int spawn_time;
  while(file >> x_pos >> y_pos >> angle >> flight_pattern >> ship_type >> ships_to_spawn >> separation >> spawn_time)
  {
    addSpawner(x_pos, y_pos, angle, flight_pattern, ship_type, ships_to_spawn, separation, spawn_time);
    num ++;
  }
}


bool Ship_Spawner::removeSpawner(ship *todelete)
{
  if(todelete == head)
  {
    head = todelete->next;
  }
  if(todelete->previous != NULL)
  {
    todelete->previous->next = todelete->next;
  }
  if(todelete->next != NULL)
  {
    todelete->next->previous = todelete->previous;
  }
  todelete = NULL;
  // FIND OUT HOW TO CLEAR MEMORY OF todelete
  // THIS MIGHT BE IT
  //memset(todelete,0,sizeof(Projectiles::projectile));
  return true;
}