
#include "stdio.h"

class Projectiles
{
  struct projectile{
  projectile* next;
  };
public:  
  // Tracking for allowing me to go through the list of projectiles
  projectile *temp;
  
  //Constructor
  Projectiles();
    //head = NULL;
  void addProjectile();
  //struct projectile getHead();
private:
  projectile *head;
};