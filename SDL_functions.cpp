#include "SDL_functions.h"

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
            //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );

            //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }

    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Get the offsets
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

SDL_Surface *init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP)
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
	printf("Failed to initialize SDL\n");
        abort;
    }
    //Set up the screen
    SDL_Surface* screen = NULL;
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
	printf("Failed to initialize screen\n");
        abort;
    }
    //Set the window caption
    SDL_WM_SetCaption( "Space Boats", NULL );

    //If everything initialized fine
    return screen;
}

bool load_files(SDL_Surface* &image, std::string filename)
{
    //Load the image
    image = load_image( filename );

    //If there was an error in loading the image
    if( image == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up(SDL_Surface* image)
{
    //Free the surface
    SDL_FreeSurface( image );

    //Quit SDL
    SDL_Quit();
}

bool refresh_screen(SDL_Surface* &screen)
{
  return SDL_Flip( screen );
}