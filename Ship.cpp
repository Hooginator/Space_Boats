#include "Ship.h"

bool Ships::addShip(double x_pos, double y_pos, double angle, double max_speed, double mass, double max_force, bool auto_fire, 
  double radius, double max_hp, double collide_damage, SDL_Surface* graphic, int controls, int nweapons, int *weapons, Weapon_Template *templates){
  // Adds a new ship at the head of the list of ships parameters are: 
  // doubles (x, y) start location of ship
  // double angle for the initial orientation of the ship
  // bool autofire decides whether or not the ship will fire on its own
  // double radius is the size for hitboxes
  // double max_hp to take damageshow much damage ramming enemy ships does
  // SDL_Surface graphic for the visual of the ship
  // int controls decides the flight path the ship will follow (-1 for wasd control)
  // int nweapons is the number of weapons the ship will have, and the size of the array:
  // int *weapons is an array with indicators of which weapons will be picked among: 
  // Weapon_Template *templates list of weapon templates to pick from.
  ship *a = new ship;
  a->x_pos = x_pos;
  a->y_pos = y_pos;
  a->x_vel = 0;
  a->y_vel = 0;
  a->x_accel = 0;
  a->y_accel = 0;
  a->angle = angle;
  a->max_speed = max_speed;
  a->mass = mass;
  a->max_force = max_force;
  a->auto_fire = auto_fire;
  if(radius !=0){
    a->radius = radius;
  }else{
    a->radius = std::min(graphic->w,graphic->h)/2;
  }
  a->max_hp = max_hp;
  a->current_hp = max_hp; 
  a->collide_damage = collide_damage;
  a->graphic = graphic;
  a->controls = controls;
  a->flight_time = 0;
  a->weapons = new Weapons;
  int i = 0;
  while(i < nweapons)
  {
    templates->addWeapon(weapons[i],a->weapons);
    i++;
  }
  a->next = head;
  a->previous = NULL;
  if(head != NULL)
  {
    head->previous = a;
  }
  head = a;
}

bool Ships::removeShip(ship *todelete)
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

bool Ships::addWeapon(double x_pos, double y_pos, double angle, int firing_rate,
    int projectile_speed, double projectile_radius, double damage, SDL_Surface* weapon_graphic, SDL_Surface* projectile_graphic, int firing_pattern)
{// For now this will always add weapons to the head ship.  I'll have to alter things if I want to change that.
  head->weapons->addWeapon(x_pos, y_pos, angle, firing_rate, projectile_speed, projectile_radius, damage, weapon_graphic, projectile_graphic, firing_pattern);
}


bool Ships::moveShips(bool &quit, int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
  double temp_x_accel;
  double temp_y_accel;
  double max_accel;
  ship *a = head;
  while(a!=NULL)
  {
    temp_x_accel = 0;
    temp_y_accel = 0;
    max_accel = a->max_force/a->mass;
    if(a->controls == 0)
    { 
      Uint8 *keystate = SDL_GetKeyState(NULL);
      //Quits when you press enter
      if(keystate[SDLK_RETURN]) {
        quit=true;
      }
      // Get x and y inputs
      temp_x_accel += max_accel*(keystate[SDLK_RIGHT] - keystate[SDLK_LEFT]);
      temp_y_accel += max_accel*(keystate[SDLK_DOWN] - keystate[SDLK_UP]);
      if(temp_x_accel != 0 && temp_y_accel != 0){
	temp_x_accel *= 0.707;
	temp_y_accel *= 0.707;
      }
      keepOnScreen(temp_x_accel,  temp_y_accel, a->max_force/a->mass, a->x_pos, a->y_pos, SCREEN_HEIGHT, SCREEN_WIDTH, a->graphic->h, a->graphic->w);
      calculateVelocities(a->x_vel, a->y_vel, temp_x_accel, temp_y_accel);
      calculatePositions(a->x_pos, a->y_pos, a->x_vel, a->y_vel);
      
    }
    else
    {
      //Here I will have to load different pregenerated paths
      getPremadePath(a->controls, a->flight_time, a->max_speed, a->max_force/a->mass, temp_x_accel, temp_y_accel, a->x_pos, a->y_pos, SCREEN_HEIGHT, SCREEN_WIDTH);
      calculateVelocitiesold(temp_x_accel, temp_y_accel, a->x_pos, a->y_pos, a->x_vel, a->y_vel, a->x_accel, a->y_accel);
      
    }
      a = a->next;
  }
}
bool Ships::calculateVelocitiesold(double new_x, double new_y, double &x_pos, double &y_pos, double &x_vel, double &y_vel, double &x_accel, double &y_accel)
{
  x_accel = (new_x - x_pos) - x_vel;
  y_accel = (new_y - y_pos) - y_vel;
  x_vel = new_x - x_pos;
  y_vel = new_y - y_pos;
  x_pos += new_x;
  y_pos += new_y;
  
}
bool Ships::calculateVelocities(double &x_vel, double &y_vel, double &x_accel, double &y_accel)
{
  x_vel += x_accel - 0.05*x_vel - 0.001*x_vel*x_vel;
  y_vel += y_accel - 0.05*y_vel - 0.001*y_vel*y_vel;
}
bool Ships::calculatePositions(double &x_pos, double &y_pos, double &x_vel, double &y_vel)
{
  x_pos += x_vel;
  y_pos += y_vel;
  
}
bool Ships::keepOnScreen(double &x_accel, double &y_accel, double max_accel, double x_pos, double y_pos, int SCREEN_HEIGHT, int SCREEN_WIDTH, double graphic_height, double graphic_width)
{
    // If ship is outside boundaries return it to the screen
    if(x_pos - graphic_width/2 < 0) x_accel = max_accel;
    if(x_pos > SCREEN_WIDTH - graphic_width/2) x_accel = -max_accel;
    if(y_pos - graphic_height/2 < 0) y_accel = max_accel;
    if(y_pos > SCREEN_HEIGHT - graphic_height/2) y_accel = -max_accel;
}

bool Ships::getPremadePath(int type, int &flight_time, double max_speed, double max_accel, double &x_accel, double &y_accel, double &x_pos, double &y_pos, int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
  x_accel = 0;
  y_accel = 0;
  //double random = rand();
  flight_time += 1;
  switch(type)
  {
    case 1: // Back and forth horizontally
      x_accel = max_accel*(pow(sin(flight_time/100.0),2)-0.5);
      break;
    case 2: // Near Circle
      x_accel = max_accel*(pow(sin(flight_time/100.0),2)-0.5);
      y_accel = max_accel*(pow(sin(flight_time/100.0-180*0.5),2)-0.5);
      break;
    case 3: // Circle
      x_accel = max_accel*(sin(flight_time*0.02));
      y_accel = max_accel*(cos(flight_time*0.02));
      break;
    case 4: // edge to edge while moving down
      if(x_pos < 50)
      {
	
      }else if(SCREEN_WIDTH - x_pos < 50)
      {
	
      }else{
	
      }
      x_accel = max_speed*0.9*sin(flight_time*0.01);
      y_accel = max_speed*0.1;
      break;
    default:
      break;
  }
  x_pos += x_accel;
  y_pos += y_accel;
}
bool Ships::showShips(SDL_Surface* screen)
{
  ship *a = head;
  while(a!=NULL)
  {
    if(a->graphic != NULL)
    {
      apply_surface( a->x_pos - a->graphic->w/2, a->y_pos - a->graphic->h/2, a->graphic, screen);//&main_ship->graphic, screen );
    }
    a = a->next;
    
  }
}

bool Ships::getLocation(double &target_x_pos, double &target_y_pos, double &target_x_vel, double &target_y_vel, double &target_x_accel, double &target_y_accel)
{// For enemy ships that want to track your motion to aim.  For now we will always aim at the head ship
  ship *a = head;
  if(a != NULL)
  {
    // I don't think the following should be here.. but it seems to work
    target_x_pos = a->x_pos - 0.5*a->graphic->w;
    target_y_pos = a->y_pos - 0.5*a->graphic->h;
    target_x_vel = a->x_vel;
    target_y_vel = a->y_vel;
    target_x_accel = a->x_accel;
    target_y_accel = a->y_accel;
  }
  else
  {
       
    target_x_pos = 0;
    target_y_pos = 0;
    target_x_pos = 0;
    target_y_vel = 0;
    target_x_accel = 0;
    target_y_accel = 0;
  }
}

bool Ships::generateProjectiles(Projectiles* projectiles, Ships *target)
{
  double target_x_pos = 0;
  double target_y_pos = 0;
  double target_x_vel = 0;
  double target_y_vel = 0;
  double target_x_accel = 0;
  double target_y_accel = 0;
  ship *a = head;
  while(a!=NULL)
  {
    if(a->weapons != NULL)
    {
      target->getLocation(target_x_pos, target_y_pos, target_x_vel, target_y_vel, target_x_accel, target_y_accel);
      // For now I am only targetting the first ship in target.  This can be improved later
      
      a->weapons->generateProjectiles(projectiles, a->x_pos, a->y_pos, a->angle, 
				      target_x_pos, target_y_pos, target_x_vel, target_y_vel, target_x_accel, target_y_accel);
    }
    a = a->next;
  }
  //This is a rather shitty way to do things. Pretty much autofire
  /*for(int i = 0;i < main_ship->n_weapons;i++)
  {
    if(main_ship->weapons[i].firing_rate <= main_ship->weapons[i].last_fired)
    {
      main_ship->weapons[i].last_fired = 0;
      //printf("PEW PEW PEW\n"); 
      projectiles->addProjectile(main_ship->weapons[i].x_pos+main_ship->x_pos,main_ship->weapons[i].y_pos+main_ship->y_pos,main_ship->weapons[i].projectile_speed*sin(main_ship->weapons[i].angle),-main_ship->weapons[i].projectile_speed*cos(main_ship->weapons[i].angle),main_ship->weapons[i].angle, main_ship->weapons[i].weapon_projectile);
      //projectiles->addProjectile(0,0,0,0,0,main_ship.weapons[i].weapon_projectile);
      
    }
    else
    {
      main_ship->weapons[i].last_fired++;
    }
  }*/
}


bool Ships::checkProjectileHit(Projectiles* projectiles)
{ // Checks if any Ship has touched any Projectile passed in. hit projectiels are removed and ships lose HP
  double damage;
  ship *a = head;
  ship *b = head;
  while(a!=NULL)
  {
    damage = 0;
    if(a->x_pos != NULL){
      damage = projectiles->checkHit(a->x_pos, a->y_pos, a->radius);
      a->current_hp -= damage;
      if(a->current_hp <=0 )
      {
	if(a->next != NULL)
	{
	  b = a->next;
	  removeShip(a);
	  a = b;
	}
	else
	{
	  removeShip(a);
	}
      } 
    }
    a = a->next;
  }
  return true;
}
double Ships::checkHit(double x, double y, double radius)
{
  // Checks if any Ship has touched any Projectile passed in. hit projectiels are removed and ships lose HP
  double damage;
  ship *a = head;
  ship *b = head;
  
  while (a!=NULL)
  {
    if(pow(pow((a->x_pos - x),2)+pow((a->y_pos - y),2),0.5) < radius + a->radius)
    {
      damage += a->collide_damage;
      if(a->next != NULL){
        b = a->next;
        removeShip(a);
        a = b;
      }
      else
      {
	removeShip(a);
      }
    }
    a = a->next;
  }
  return damage;
}

bool Ships::checkShipHit(Ships* other_ships)
{
  // Checks if any Ship has touched any Projectile passed in. hit projectiels are removed and ships lose HP
  double damage;
  ship *a = head;
  ship *b = head;
  while(a!=NULL)
  {
    damage = 0;
    if(a->x_pos != NULL){
      damage = other_ships->checkHit(a->x_pos, a->y_pos, a->radius);
      a->current_hp -= damage;
      if(a->current_hp <=0 )
      {
	if(a->next != NULL)
	{
	  b = a->next;
	  removeShip(a);
	  a = b;
	}
	else
	{
	  removeShip(a);
	}
      } 
    }
    a = a->next;
  }
  return true;
}