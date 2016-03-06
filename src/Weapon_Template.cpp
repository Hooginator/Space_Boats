#include "Weapon_Template.h"

bool Weapon_Template::loadTemplate(std::string filename)
{
  std::ifstream file;
  file.open(filename.c_str());
  if(file.fail())
  {
    printf("Error loading weapon templates \n");
    return false;
  }
  int num = 0;
  
  std::string weapon_graphic;
  std::string projectile_graphic;
  while(file >> weapon_graphic >> projectile_graphic >> templates[num].x_pos >> templates[num].y_pos >> templates[num].angle 
    >> templates[num].firing_rate >> templates[num].projectile_speed >> templates[num].projectile_radius >> templates[num].damage >> templates[num].firing_pattern)
  {
    if(load_files(templates[num].weapon_graphic, weapon_graphic) == false)
    {
      return 1;
    }
    if(load_files(templates[num].projectile_graphic, projectile_graphic) == false)
    {
      return 1;
    }
    num ++;
  }
}

bool Weapon_Template::addWeapon(int type, Weapons *weapon)
{
  weapon->addWeapon(templates[type].x_pos, templates[type].y_pos, templates[type].angle, templates[type].firing_rate, templates[type].projectile_speed, 
    templates[type].projectile_radius, templates[type].damage, templates[type].weapon_graphic, templates[type].projectile_graphic, templates[type].firing_pattern);
}