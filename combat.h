#include <stdint.h> 
#include <pic32mx.h> 


#define NUMBER_OF_PLAYERS 2			//2 players
#define MAX_HP 10					//Health point (how many times a player can be shot)

#define WIDTH 128					//screen width (pixels)
#define HEIGHT 32					//screen height (pixels)
#define NUMBER_OF_ROWS 4			//height (4 rows of 8 pixels)

#define NUMBER_OF_BULLETS 20		//maximum number of bullets
#define BULLET_DURATION 100			//maximum number of frames a bullet can exist
#define BULLET_COOLDOWN 20			//number of frames between shots

#define TURN_COOLDOWN 8				//number of frames between turns 



