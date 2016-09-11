#include "game.h"

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

//const int FPS = 60;
const int FPS = 300; // NOT REALLY working as FPS BUT CLOCKS_PER_SEC IS NOT WHAT IT APPEARS TO BE....
const double Clocks_Per_Refresh = CLOCKS_PER_SEC/FPS;
// This will dictate how long to wait each time it is not time to refresh the screen (between frames)
const double Clocks_Error = Clocks_Per_Refresh / 100;

//Maximum Number of unique Projectile Images
// This will likely be put into Projectiles.cpp soon
const int unique_projectiles = 10;

// Rate at which the background scrolls
const int BACKGROUND_SPEED = 5;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;

// Collection of ship and projectile images to be displayed on the screen 
SDL_Surface *ship_images[unique_ships];
SDL_Surface *projectile_images[unique_projectiles];

//The event structure that will be used
//I'm not sure if this is needed right now.  Maybe for queueing up inputs?
SDL_Event event;

// Projectile tracking, essentially a list of all ally / enemy projectiles on the screen
Projectiles *ally_projectiles = new Projectiles;
Projectiles *enemy_projectiles = new Projectiles;


// Current number of projectiles on screen
int nprojectiles = 0;

int game(std::string Ships_File)
{
    printf("/*************************************************/\n");
    printf("/*************** Starting Game *******************/\n");
    printf("/*************************************************/\n");
    
    // Filenames and stuff that will later be in an input file
    std::string ship1 = "ships/main_ship.png";
    std::string ship2 = "yellow.png";
    std::string projectile1 = "projectiles/shot1.png";
    std::string background1 = "background.png";
    std::string ship_templates = "ship_templates.dat";
    std::string weapon_templates = "weapon_templates.dat";
    
    //Make sure the program waits for a quit until quit == true
    bool quit = false;
    
    //Initialize screen 
    screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);

    //Load the image files.  This will should depend on inputs from the input file
    std::string ship_filename[unique_ships];
    ship_filename[0] = ship1;
    // pink.png was showing up with white border.  
    // Fixed it by making the bg black AND zero alpha
    ship_filename[1] = ship2;
    
    // Names of all of the projectile image files.
    std::string projectile_filename[MAX_PROJECTILES];
    projectile_filename[0] = projectile1;
    
    // Load all of the images , if any fails kill game with error message
    if( load_files(background, background1) == false )
    {
        printf("Error loading background image\n");
        return 1;
    }    
    if( load_files(ship_images[0], ship_filename[0]) == false )
    {
        printf("error loading ship image 1\n");
        return 1;
    }
    if( load_files(ship_images[1], ship_filename[1]) == false )
    {
        printf("error loading ship image 2\n");
        return 1;
    }
    if( load_files(projectile_images[0], projectile_filename[0]) == false )
    {
        printf("error loading proectile image\n");
        return 1;
    }
    
    
    // load the template for which types of weapons each enemy will have
    Weapon_Template *weapons = new Weapon_Template;
    weapons->loadTemplate(weapon_templates);
    
    // Ship_Spawner will create enemy ships according to certain parameters within the .dat files
    Ship_Spawner *ship_spawner = new Ship_Spawner;
    printf("about to load Ship Spawner templates\n");
    ship_spawner->loadTemplates(ship_templates);
    ship_spawner->loadSpawners(Ships_File);
   
    
    // I can't remember what this parameter is :S I will have to make all of these in the INPUT file
    int array[1];
    array[0] = 0;
    // Create the "list" of main ships and Initialize main ship parameters.
    Ships *main_ship = new Ships;
    main_ship->addShip(300,300,0,5,3,1,true,0,20,10,ship_images[0],0,1,array,weapons);
    
    // Enemy ships which will be created via the spawner
    Ships *enemy_ships = new Ships;
    
    // Initial configuration for the background images
    // There are two at al times so that the screen is guaranteed to be covered (they move back in a leapfrog fashion.)
    int background1_x_pos = 0;
    int background1_y_pos = 0;
    int background2_x_pos = 0;
    int background2_y_pos = -background->h;
    
    // Valiables for screen refreshing
    clock_t t1;// time that the frame starts at
    clock_t t2;
    clock_t delta_t;
    bool New_Frame;
    
    //Number of frames that have passed so far
    int frames = 0;
    
    printf("Setup complete, starting Main Loop\n");
    //While the user hasn't quit
    while( quit == false )
    {
	//Get time for the start of the frame
	t1 = clock();
	
	// Empty the screen of anything in the previous frame
	SDL_FillRect(screen, 0, 0);
	
	/********************** BACKGROUND *************************************/
	// Force the background to move at a constant rate towards the player and have it repeat when we run out of background
	Move_Background(background1_x_pos, background1_y_pos, background2_x_pos, background2_y_pos);
	
	
	
	/********************** ENEMY SHIPS *************************************/
	// Spawning enemy ships from the ship spawner for the level
	ship_spawner->spawnShips(frames, enemy_ships, weapons);

	
	/********************** MAIN SHIP ***************************************/ 
	// Read input commands for the main ship, also read for quitting with Enter (I'll remove this after testing)
	main_ship->moveShips(quit, SCREEN_HEIGHT, SCREEN_WIDTH);
	main_ship->showShips(screen);
	main_ship->generateProjectiles(ally_projectiles, enemy_ships);

	
	
	//Move Enemy Ships
	enemy_ships->moveShips(quit, SCREEN_HEIGHT, SCREEN_WIDTH);
	enemy_ships->showShips(screen);
	enemy_ships->generateProjectiles(enemy_projectiles,main_ship);
	
	// Manage projectiles
	ally_projectiles->moveProjectiles();
	ally_projectiles->showProjectiles(screen);
	
	enemy_projectiles->moveProjectiles();
	enemy_projectiles->showProjectiles(screen);
	
	// COLLISION DETECTION
	main_ship->checkProjectileHit(enemy_projectiles);
	enemy_ships->checkProjectileHit(ally_projectiles);
	
	main_ship->checkShipHit(enemy_ships);
	
	// REMOVE OUT OF BOUNDS PROJECTIELS
	ally_projectiles->checkProjectilesandBoundaries(SCREEN_WIDTH, SCREEN_HEIGHT);
	enemy_projectiles->checkProjectilesandBoundaries(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Get time again to control refresh rate before updating screen
	New_Frame = false;
	while (New_Frame == false)
	{
	  // Check how much time has elapsed since last frame refresh
	  t2 = clock();
	  delta_t = t2-t1;
	  // If enough time has passed, start the next frame
	  if(delta_t > Clocks_Per_Refresh - Clocks_Error)
	  {
	    New_Frame = true;
	  }
	  else
	  {
	    usleep(Clocks_Error/CLOCKS_PER_SEC*1e6);
	  }
	}
	//Update the screen  
	if( refresh_screen(screen)  == -1 )
	  {
	    return 1;
	  }
	  // Update the frame number that we are on
	  frames ++;
	
        //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }

    //Free the surface and quit SDL
    clean_up(ship_images[0]);

    return 0;
}

/*bool Move_Ship(Ship* main_ship, bool &quit)
{
  //Quits when you press enter
  Uint8 *keystate = SDL_GetKeyState(NULL);
  if(keystate[SDLK_RETURN]) {
    quit=true;
  }
  if(keystate[SDLK_LEFT]&&(main_ship->x_pos > 0)) {
    main_ship->x_pos-=main_ship->speed;
  }
  if(keystate[SDLK_RIGHT]&&(main_ship->x_pos < SCREEN_WIDTH - main_ship->width)) {
    main_ship->x_pos+=main_ship->speed;
  }
  if(keystate[SDLK_DOWN]&&(main_ship->y_pos < SCREEN_HEIGHT - main_ship->height)) {
    main_ship->y_pos+=main_ship->speed;
  }
  if(keystate[SDLK_UP]&&(main_ship->y_pos > 0)) {
    main_ship->y_pos-=main_ship->speed;
  }
  //Update Main_Ship position
  apply_surface( main_ship->x_pos, main_ship->y_pos, ship_images[0], screen);//&main_ship->graphic, screen );
}*/
bool Move_Background(int &background1_x_pos, int &background1_y_pos, int &background2_x_pos, int &background2_y_pos)
{
  background1_y_pos+= BACKGROUND_SPEED;
  background2_y_pos+= BACKGROUND_SPEED;
  if(background1_y_pos > background->h){background1_y_pos -=2*background->h;}
  if(background2_y_pos > background->h){background2_y_pos -=2*background->h;}
  //Update Background position
  apply_surface( background1_x_pos, background1_y_pos, background, screen );
  apply_surface( background2_x_pos, background2_y_pos, background, screen );
}
/*bool Generate_Projectiles(Ship *main_ship)
{
  //This is a rather shitty way to do things. Pretty much autofire
  for(int i = 0;i < main_ship->n_weapons;i++)
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
  }
}*/
bool Handle_Projectiles()
{
  //Generate_Projectiles(main_ship);
  //projectiles->moveProjectiles();
  // PROJECTILE OUT OF BOUNDAR CRASH IS PROBABLY DUE TO THE HEAD BEING REMOVED
  //projectiles->checkProjectilesandBoundaries(SCREEN_WIDTH, SCREEN_HEIGHT);
  // Check for hit / out f bounds
  // SHOW projectiles needs to be able to rotate the images.  LOOK UP HOW TO DO THAT!!
  //projectiles->showProjectiles(screen,projectile_images[0]);
}