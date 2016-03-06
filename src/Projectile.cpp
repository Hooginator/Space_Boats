#include "Projectile.h"


void Projectiles::addProjectile(double x_pos, double y_pos, double x_speed, double y_speed, double angle, double radius, double damage, SDL_Surface* graphic){
  projectile *a = new projectile;
  a->x_pos = x_pos;
  a->y_pos = y_pos;
  a->x_speed = x_speed;
  a->y_speed = y_speed;
  a->angle = angle;
  a->radius = radius;
  a->damage = damage;
  a->graphic = graphic;
  a->next = head; 
  a->previous = NULL;
  if(head != NULL)
  {
    head->previous = a;
  }
  head = a;
}

void Projectiles::moveProjectiles()
{
  projectile *a = head;
  int counter = 0;
  while((a !=NULL)&&counter < MAX_PROJECTILES)
  {
    a->x_pos += a->x_speed;
    a->y_pos += a->y_speed;
    a = a->next;
    counter ++;
  }
}

void Projectiles::checkProjectilesandBoundaries(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
  projectile *a = head;
  projectile *b = head;
  int counter = 0;
  while((a !=NULL)&&counter < MAX_PROJECTILES)
  {
    if((a->x_pos + a->graphic->w/2> SCREEN_WIDTH)||(a->y_pos + a->graphic->h/2> SCREEN_HEIGHT)||(a->x_pos < a->graphic->w/2)||(a->y_pos < + a->graphic->h/2))
    {
      if(a == head)
      {
	b = a->next;
	removeProjectile(a);
	a = b;
	head = a;
      }
      else
      {
	//This seems to never not be the case..
	if(a->next == NULL)
	{
	  removeProjectile(a);
	  a = NULL;
	}
	else
	{
	  b = a->next;
	  removeProjectile(a);
	  a = b;
	}
      }

    }
    else // I AM ASSUMING THAT REMOVING THE PROJECTILE a 
    {
      a = a->next;
    }
    counter ++;
  } 
}
void Projectiles::removeProjectile(projectile* todelete)
{// MIGHT NEED TO CHANGE THIS TO RETURN THE NEXT VALUE AFTER THE DELETED BUDDY
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
  return;
}
  
double Projectiles::checkHit(double x, double y, double radius)
{
  double damage = 0;
  projectile *a = head;
  projectile *b = head;
  while (a!=NULL)
  {
    if(pow(pow((a->x_pos - x),2)+pow((a->y_pos - y),2),0.5) < radius + a->radius)
    {
      damage += a->damage;
      if(a->next != NULL){
        b = a->next;
        removeProjectile(a);
        a = b;
      }
      else
      {
	removeProjectile(a);
      }
    }
    a = a->next;
  }
  return damage;
}
  
void Projectiles::showProjectiles(SDL_Surface *screen)
{
  projectile *a = head;
  int counter = 0;
  while((a !=NULL)&&counter < MAX_PROJECTILES)
  {
    apply_surface(  a->x_pos  - a->graphic->w/2, a->y_pos  - a->graphic->h/2, a->graphic, screen );
    a = a->next;
    counter ++;
  }
  //printf("Here we go: %i %i\n",a->x_pos,a->y_pos);
  // Can't seem to gte the apply_surface working here
  //apply_surface( a->x_pos, a->y_pos, a->graphic, screen );
  
}

Projectiles::projectile Projectiles::getHead()
{
  return *head;
}

void Projectiles::reset_temp()
{
  this->temp = this->head;
}
double Projectiles::get_x_pos()
{
  return this->temp->x_pos;
}
double Projectiles::get_y_pos()
{
  return temp->y_pos;
}
 