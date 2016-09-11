#include "class.h"

void Projectiles::addProjectile(){
  printf("HELLO");
  projectile *a = new projectile;
  a->next = head; //THIS LINE IS GIVING A SEG FAULT.  FIX IT!
  /*head = a;*/
}
/*temp::projectile temp::getHead()
{
  return *head;
}*/
Projectiles::Projectiles()
{
  printf("creating stuff");
}