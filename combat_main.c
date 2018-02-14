

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

	
	
	/*Display and game setup*/
	io_init();
	timer_init();
	display_init();
	model_setup(p_model);
	bullet_init(bullets);
	
	
	int p;
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){
		cooldown[p] = 0;
		p_HP[p] = MAX_HP;
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
				
				if(!p_buttons[p][7]){
					p_position[p][0] += 1;
					p_direction[p][0] = 1;
				} else if(!p_buttons[p][6]){
					p_position[p][0] -= 1;
					p_direction[p][0] = -1;
				} else {
					p_direction[p][0] = 0;
				}
										
				if(!p_buttons[p][5]){
					p_position[p][1] += 1;
					p_direction[p][1] = 1;
				}else if(!p_buttons[p][4]){
					p_position[p][1] -= 1;
					p_direction[p][1] = -1;
				} else {
					p_direction[p][1] = 0;
				}
				
				if(p_direction[p][0]*p_direction[p][0]+p_direction[p][1]*p_direction[p][1]){
					b_direction[p][0] = p_direction[p][0];
					b_direction[p][1] = p_direction[p][1];
				}
				
				
				if(!p_buttons[p][0]){
					if(cooldown[p] <= 0){
						create_bullet(bullets, p_position[p][0], p_position[p][1], b_direction[p][0], b_direction[p][1]);
						cooldown[p] = BULLET_COOLDOWN;
					}
				}
									
				boundary_check(p_position[p], p_model[p]);
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
