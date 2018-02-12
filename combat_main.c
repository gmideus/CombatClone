

#include <stdint.h> 
#include <pic32mx.h>  

int main(void) {
	SYSKEY = 0xAA996655;  
	SYSKEY = 0x556699AA; 
	while(OSCCON & (1 << 21)); 
	OSCCONCLR = 0x180000;
	while(OSCCON & (1 << 21)); 
	SYSKEY = 0x0; 
	

	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	

	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	

	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	

	SPI2CON = 0;
	SPI2BRG = 4;

	SPI2STATCLR = 0x40;

        SPI2CONSET = 0x40;

	SPI2CONSET = 0x20;

	SPI2CONSET = 0x8000;
	
	
	/*
	 * GPIO Test setup
	 */
	TRISECLR = (0xff);   //Sets J6-2,4,6,8 as output

	unsigned int position = 7;
	PORTE = (0x1 << position);
	
	
	TRISDSET = 0x6;
	TRISDCLR = 0x600;
	
	char* display_data[512];

	
	display_init();
	display_update(display_data);
	
	portd_clr(0);
	portd_clr(3);
	
	int p_position[2][2] = {{1, 1}, {13, 6}};  // player positions [player][coordinate]

	
	
	char p_model[2][10];          //player model [player][model data]  model data = sizex, sizey, 8 chars representing the model
	
	model_setup(p_model);
	
	int i = 0;
	int wait_time = 5;
	char p_buttons[2][8];
	while( 1 )
	{
		clear_data(display_data);
		controller_update(p_buttons);
		int p;
		for(p = 0; p < 2; p++){
			if(!p_buttons[p][7]){
				p_position[p][0] += 1;
			} else if(!p_buttons[p][6]){
				p_position[p][0] -= 1;
			}
			
			
			if(!p_buttons[p][5]){
				p_position[p][1] += 1;
			}else if(!p_buttons[p][4]){
				p_position[p][1] -= 1;
			}
			
			boundary_check(p_position[p], p_model[p]);
		}
		
		
	

		display_data_update(display_data, p_position, p_model);
		
		//PORTE = 0x1 << (p_position[0]%8);
		delay(wait_time);
	  
		display_update(display_data);
	  //display_image(96, icon);
	}
	return 0;
}
