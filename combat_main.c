

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
	int p_position[2][2] = {{1, 1}, {13, 6}};  	//Player positions [player][coordinate]
	char p_model[2][10];          				//Pslayer model [player][model data]  model data = sizex, sizey, 8 chars representing the model
	int wait_time = 5;
	char p_buttons[2][8];
	
	
	/*Display and game setup*/
	io_init();
	display_init();
	model_setup(p_model);
	
	
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
		delay(wait_time);
		display_update(display_data);
	}
	return 0;
}
