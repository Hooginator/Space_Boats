all:
	g++ main.cpp game.cpp game.h SDL_functions.cpp SDL_functions.h Ship.cpp Ship.h Weapon.h Weapon.cpp Projectile.h Projectile.cpp Ship_Spawner.cpp Ship_Spawner.h Powerup.cpp Powerup.h Weapon_Template.cpp Weapon_Template.h -o Space_Boats -I/usr/local/include -L/usr/local/lib -lSDL -lSDL_image
