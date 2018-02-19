
#include <stdint.h> 
#include <pic32mx.h> 
#include "combat.h" 

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
	char* display_data[512];
	int p_position[NUMBER_OF_PLAYERS][2] = {{1, 1}, {13, 6}};  	//Player positions [player][coordinate]
	char p_model[NUMBER_OF_PLAYERS][10];          				//Player model [player][model data]  model data = sizex, sizey, 8 chars representing the model
	char p_buttons[NUMBER_OF_PLAYERS][8];
	int p_HP[NUMBER_OF_PLAYERS];
	int p_direction[NUMBER_OF_PLAYERS][2];
	int b_direction[NUMBER_OF_PLAYERS][2];
	int cooldown[NUMBER_OF_PLAYERS];
	int timer_count = 0;
	int bullets[NUMBER_OF_BULLETS][6];
	
	
	static const float angles[16][2] = {{1, 0}, {0.9238, 0.3826}, {0.7071, 0.7071}, {0.3826, 0.9238}, {0, 1}, {-0.3826, 0.9238}, { -0.7071, 0.7071}, {-0.9238, 0.3826},
		 {-1, 0}, { -0.9238, -0.3826}, {-0.7071, -0.7071}, { -0.3826, -0.9238}, {0, -1}, {0.3826, -0.9238}, {0.7071, -0.7071}, {0.9238,  -0.3826}};
	char p_angle[NUMBER_OF_PLAYERS];
	float p_position_f[NUMBER_OF_PLAYERS][2];
	float p_direction_f[NUMBER_OF_PLAYERS][2];
	int turn_cooldown[NUMBER_OF_PLAYERS];
	
	float speed = 0.3;
	
	
	/*Display and game setup*/
	io_init();
	timer_init();
	display_init();
	model_setup(p_model);
	bullet_init(bullets);

	
	p_angle[0] = 0;
	p_angle[1] = 0;
	turn_cooldown[0] = 0;
	turn_cooldown[1] = 0;
	
	int p;
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){
		cooldown[p] = 0;
		p_HP[p] = MAX_HP;
		p_position_f[p][0] = p*10;
		p_position_f[p][1] = p*10;
		p_direction_f[p][0] = angles[0][0];
		p_direction_f[p][1] = angles[0][1];
		
	}
	
	
	while( 1 )
	{
		if(IFS(0)){
			
			clear_data(display_data);
			controller_update(p_buttons);
							
			for(p = 0; p < NUMBER_OF_PLAYERS; p++){
				
				if(cooldown[p] > 0){
					cooldown[p] -= 1;
				}
				if(turn_cooldown[p] > 0){
					turn_cooldown[p] -= 1;
				}
				
				if(!p_buttons[p][7] && !turn_cooldown[p]){
					
					p_angle[p] = (p_angle[p] + 1)%16 ;
					p_direction_f[p][0] = angles[p_angle[p]][0];
					p_direction_f[p][1] = angles[p_angle[p]][1];
					turn_cooldown[p] = TURN_COOLDOWN;
				
					//p_position_f[p][0] += 1;
				} else if(!p_buttons[p][6] && !turn_cooldown[p]){
					
					p_angle[p] -= 1;
					if(p_angle[p] < 0){
						p_angle[p] += 16;
					}
					p_direction_f[p][0] = angles[p_angle[p]][0];
					p_direction_f[p][1] = angles[p_angle[p]][1];
					turn_cooldown[p] = TURN_COOLDOWN;
					//p_position_f[p][0] -= 1;
				} else {
					p_direction[p][0] = 0;
				}
										
				if(!p_buttons[p][5]){
					
					p_position_f[p][0] -= p_direction_f[p][0]*speed;
					p_position_f[p][1] -= p_direction_f[p][1]*speed;
					//p_direction[p][1] = 1;
					
					//p_position_f[p][1] += 1;
				}else if(!p_buttons[p][4]){
					
					p_position_f[p][0] += p_direction_f[p][0]*speed;
					p_position_f[p][1] += p_direction_f[p][1]*speed;
					
					//p_position_f[p][1] -= 1;
				} else {
					p_direction[p][1] = 0;
				}
				
				p_position[p][0] = (int) (p_position_f[p][0] + 0.5);
				p_position[p][1] = (int) (p_position_f[p][1] + 0.5);
				/*
				if(p_direction[p][0]*p_direction[p][0]+p_direction[p][1]*p_direction[p][1]){
					b_direction[p][0] = p_direction[p][0];
					b_direction[p][1] = p_direction[p][1];
				}
				*/
				
				if(!p_buttons[p][0]){
					if(cooldown[p] <= 0){
						create_bullet(bullets, p_position[p][0], p_position[p][1], b_direction[p][0], b_direction[p][1]);
						cooldown[p] = BULLET_COOLDOWN;
					}
				}
									
				boundary_check(p_position[p], p_model[p], p_position_f[p]);
				hit_check(p_position[p], p_model[p], bullets, &p_HP[p]);
				
			}
			bullet_update(bullets);
			display_data_update(display_data, p_position, p_model, bullets);
			display_update(display_data);
			PORTE = (p_HP[0] << 4) | p_HP[1];
			
			IFS(0) = 0;
		}
	}
	return 0;
}
