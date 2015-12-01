#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "string"


SDL_Surface *load_image( std::string filename );
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
SDL_Surface *init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP);
bool load_files(SDL_Surface* &image, std::string filename);
void clean_up(SDL_Surface* image);
bool refresh_screen(SDL_Surface* &screen);