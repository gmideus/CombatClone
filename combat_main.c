
#include <stdint.h> 
#include <pic32mx.h> 
#include "combat.h" 

//Test

int main(void) {
	SYSKEY = 0xAA996655;  
	SYSKEY = 0x556699AA; 
	while(OSCCON & (1 << 21)); 
	OSCCONCLR = 0x180000;
	while(OSCCON & (1 << 21)); 
	SYSKEY = 0x0; 

	AD1PCFG = 0xFFFF;
	ODCE = 0x0;

	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	SPI2CON = 0;
	SPI2BRG = 4;

	SPI2STATCLR = 0x40;
	SPI2CONSET = 0x40;
	SPI2CONSET = 0x20;
	SPI2CONSET = 0x8000;
	
	/*Variable init*/
	char display_data[512];
	int p_position[NUMBER_OF_PLAYERS][2] = {{1, 1}, {13, 6}};  	//Player positions [player][coordinate]
	char p_model[NUMBER_OF_PLAYERS][10];          				//Player model [player][model data]  model data = sizex, sizey, 8 chars representing the model
	char p_buttons[NUMBER_OF_PLAYERS][8]; 						//8 possible buttons 
	int p_HP[NUMBER_OF_PLAYERS];								//Health Points for Players which determine if a player is still alive
	int cooldown[NUMBER_OF_PLAYERS];							//Prevents players from shooting in every single frame. Stores the current cooldown until you can shoot again 
	int timer_count = 0;					//?
	int bullets[NUMBER_OF_BULLETS][6];							//keeps track of all int bullet information 
	float bullets_f[NUMBER_OF_BULLETS][4];						// bullet speed and position in x and y directions as floats 
	
	char models[8][8];											//all possible player sprites (to show direction) 
	
	char* player1_text = " PLAYER 1 WINS"; //Display if this pla
	char* player2_text = " PLAYER 2 WINS"; //--"--
	
	//an array that stores the possible x and y speed for different angles becasue trig is the worst 
	static const float angles[16][2] = {{1, 0}, {0.9238, 0.3826}, {0.7071, 0.7071}, {0.3826, 0.9238}, {0, 1}, {-0.3826, 0.9238}, { -0.7071, 0.7071}, {-0.9238, 0.3826},
		 {-1, 0}, { -0.9238, -0.3826}, {-0.7071, -0.7071}, { -0.3826, -0.9238}, {0, -1}, {0.3826, -0.9238}, {0.7071, -0.7071}, {0.9238,  -0.3826}};
	
	char p_angle[NUMBER_OF_PLAYERS]; 							//angle of player
	float p_position_f[NUMBER_OF_PLAYERS][2];				 	//position of player (float) 
	float p_direction_f[NUMBER_OF_PLAYERS][2];					//direction of player (float) 
	int turn_cooldown[NUMBER_OF_PLAYERS];						//prevents player from turning too quickly 
	
	//matches the correct sprite model to the angle of the player 
	static const int p_model_type[NUMBER_OF_PLAYERS][16] = {{0, 1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7}, {0, 1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7}};
	float speed = 0.3;											//players move at a constant rate 0.3 pixels per frame 
	
	/*Display and game setup*/
	io_init();
	timer_init();
	display_init();
	model_setup(p_model, models);
	bullet_init(bullets);

	/* initializes players angle and cooldown(wait time) */ 
	p_angle[0] = 0;
	p_angle[1] = 0;
	turn_cooldown[0] = 0;
	turn_cooldown[1] = 0;
	
	//sets initial values for both players 
	int p; //p is 0 (player 1) or 1 (player2)
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){
		cooldown[p] = 0;										//allows players to shoot
		p_HP[p] = MAX_HP; 										//full health
		p_position_f[p][0] = p*10;								//x position
		p_position_f[p][1] = p*10;								//y position
		p_direction_f[p][0] = angles[0][0];						//x direction 
		p_direction_f[p][1] = angles[0][1];						//y direction 
		p_model[p][2] = p_model_type[p][p_angle[p]];			//sets corresponding sprite
	}
	
	
	while( 1 ) 															//infinite loop 
	{
		if(IFS(0)){
			
			clear_data(display_data);
			controller_update(p_buttons);
							
			for(p = 0; p < NUMBER_OF_PLAYERS; p++){
				
				if(cooldown[p] > 0){									//enables players to shoot
					cooldown[p] -= 1;
				}
				if(turn_cooldown[p] > 0){								//enables players to turn
					turn_cooldown[p] -= 1;
				}
				
				if(!p_buttons[p][7] && !turn_cooldown[p]){				//right arrow (clockwise)
					
					p_angle[p] = (p_angle[p] + 1)%16 ;					//16 different angle options 
					p_direction_f[p][0] = angles[p_angle[p]][0];		//x direction 
					p_direction_f[p][1] = angles[p_angle[p]][1];		//y direction
					p_model[p][2] = p_model_type[p][p_angle[p]];		//corresponding sprite image
					turn_cooldown[p] = TURN_COOLDOWN;					//8 frames until you can turn again 
					
				} else if(!p_buttons[p][6] && !turn_cooldown[p]){		//left arrow (counter clockwise)
					
					p_angle[p] -= 1;									
					if(p_angle[p] < 0){									//16 angle options 
						p_angle[p] += 16;
					}
					p_direction_f[p][0] = angles[p_angle[p]][0];		//x direction	
					p_direction_f[p][1] = angles[p_angle[p]][1];		//y direction
					p_model[p][2] = p_model_type[p][p_angle[p]];		//sprite
					turn_cooldown[p] = TURN_COOLDOWN;					//frames until you are allowed to turn 

				}
										
				if(!p_buttons[p][5]){									//down arrow (reverse)
					
					p_position_f[p][0] -= p_direction_f[p][0]*speed;	//x direction movement	
					p_position_f[p][1] -= p_direction_f[p][1]*speed;	//y direction movement 
				
				}else if(!p_buttons[p][4]){								//up arrow (forward movement)
					
					p_position_f[p][0] += p_direction_f[p][0]*speed;	//x direction 	
					p_position_f[p][1] += p_direction_f[p][1]*speed;	//y direction movement 
				
				}
				
				p_position[p][0] = (int) (p_position_f[p][0] + 0.5);	//x position
				p_position[p][1] = (int) (p_position_f[p][1] + 0.5);	//y position 

				
				if(!p_buttons[p][0]){									//A button (shoots)
					if(cooldown[p] <= 0){
						create_bullet(bullets, bullets_f, p_position[p][0], p_position[p][1], p_direction_f[p]);
						cooldown[p] = BULLET_COOLDOWN;					//frames until you are allowed to shoot again 
					}
				}
									
				boundary_check(p_position[p], p_model[p], p_position_f[p]); //make sure player is within boundary
				if(hit_check(p_position[p], p_model[p], bullets, &p_HP[p])){ //if game ending conditions are met the other player wins 
					clear_data(display_data);
					char* winner;
					if(p){
						winner = player1_text;
					} else {
						winner = player2_text;
					}
					display_string(0, winner);
					display_string(2, "     TANKS");					//super amazing pun 
					display_string(3, "  FOR PLAYING");
					display_string_update();
					return 0;
				}
				
			}
			bullet_update(bullets, bullets_f);
			display_data_update(display_data, p_position, p_model, bullets, models);
			display_update(display_data);
			PORTE = (p_HP[0] << 4) | p_HP[1];
			
			IFS(0) = 0;
		}
	}
	return 0;
}
