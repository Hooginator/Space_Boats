#include "Weapon.h"

bool Weapons::generateProjectiles(Projectiles* projectiles, double x_pos, double y_pos, double angle, 
				  double target_x_pos, double target_y_pos, double target_x_vel, double target_y_vel, double target_x_accel, double target_y_accel)
{
  // projectiles is the list of projectiles to add to
  // x_pos, y_pos and angle are related to the host ship
 
  weapon *a = head;
  double angle_miss;
  while(a!=NULL)
  {
    a->last_fired++;
    if(a->last_fired > a->firing_rate)
    {
      angle_miss = 0;
      a->last_fired = 0;
      angle_miss = aimWeapon(a->x_pos + x_pos,a->y_pos + y_pos,target_x_pos,target_y_pos,target_x_accel,target_y_accel,-pi*0.1,pi*0.1,a->firing_pattern);
      //projectiles->addProjectile(a->x_pos+x_pos, a->y_pos+y_pos, a->projectile_speed*sin(a->angle+angle+angle_miss), 
	//			 -a->projectile_speed*cos(a->angle+angle+angle_miss), a->angle + angle + angle_miss, a->projectile_radius, a->damage, a->projectile_graphic); 
       projectiles->addProjectile(a->x_pos+x_pos, a->y_pos+y_pos, a->projectile_speed*sin(angle_miss), 
				 -a->projectile_speed*cos(angle_miss), angle_miss, a->projectile_radius, a->damage, a->projectile_graphic); 
    
      
    }
    a = a->next;
  }
}

double Weapons::aimWeapon(double x_pos, double y_pos, double target_x_pos, double target_y_pos, double target_x_speed, double target_y_speed, 
			 double angle_min, double angle_max, int strategy)
{
  double angle = 0;
  double dist_x = target_x_pos - x_pos;
  double dist_y = target_y_pos - y_pos;
  switch(strategy)
  {
    case 0: // Straight ahead shooting
      angle = angle_min + (angle_max-angle_min)*rand()/std::numeric_limits<int>::max();
    break;
    case 1: 
      if(y_pos < target_y_pos){
        angle = pi*0.5 + acos((target_x_pos - x_pos)/pow(pow(target_x_pos - x_pos,2)+pow(target_y_pos - y_pos,2),0.5));
	printf("target higher x");
      }
      else if(target_y_pos < y_pos)
      {
        angle = pi*0.5 - acos((target_x_pos - x_pos)/pow(pow(target_x_pos - x_pos,2)+pow(target_y_pos - y_pos,2),0.5));
      }
      printf("Angle: %f\n",angle);
    break;
   
    default:
      break;
   
  }
   return angle;
}

bool Weapons::addWeapon(double x_pos, double y_pos, double angle, int firing_rate,
    int projectile_speed, double projectile_radius, double damage, SDL_Surface* weapon_graphic, SDL_Surface* projectile_graphic, int firing_pattern)
{
  weapon *a = new weapon;
  a->x_pos = x_pos;
  a->y_pos = y_pos;
  a->angle = angle;
  a->firing_rate = firing_rate;
  a->projectile_speed = projectile_speed;
  a->projectile_radius = projectile_radius;
  a->damage = damage;
  a->firing_pattern = firing_pattern;
  a->weapon_graphic = weapon_graphic;
  a->projectile_graphic = projectile_graphic;
  a->last_fired = 0;
  a->next = head;
  a->previous = NULL;
  if(head != NULL)
  {
    head->previous = a;
  }
  head = a;
}

bool Weapons::addWeapon(int type)
{
  
}