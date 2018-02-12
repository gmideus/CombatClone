

#include <stdint.h>   
#include <pic32mx.h>  


#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

void _on_bootstrap() {
	
}
void _on_reset() {
	
}
void _nmi_handler() {
	while(1);
}


void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

clear_data(char* data){
	int i;
	for(i = 0; i < 512; i++){
		data[i] = 0x00;
	}
}

display_data_update(char* data, int position[2][2], char model[2][10]){
	int p, i, j;
	for(p = 0; p < 2; p++){
		for(i = 0; i < model[p][0]; i++){
			for(j = 0; j < model[p][1]; j++){
				if((model[p][i+2] >> j) & 0x1){
					int a = (position[p][1]+j)/8;
					data[a*128 + position[p][0] + i] |= (0x1 << (position[p][1]+j)%8);
				}
			}
		}
	}
}



uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

void display_init(void) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}

/*Send display data with SPI to the display */
void display_update(char* display_data) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_CHANGE_TO_DATA_MODE;
		
		for(j = 0; j < 128; j++) {
			spi_send_recv(display_data[i*128 + j]);
		}
	}
}

boundary_check(int position[2], int size[10]){
	int boundary[2]  = { 128, 32 };
	int i;
	//int p;
	//for(p = 0; p < 2 
	for(i = 0; i < 2; i++){
		if(position[i] <= 0){
			position[i] = 0;
		}
		if(position[i] >= boundary[i] - 4){
			position[i] = (boundary[i] - 4);
		}
	}
	
}


void delay(int n){
	int i = 0;
	while(i < 10000*n){
		i++;
	}
}

volatile int porte_get(int i){
	return ((PORTE >> i) & 0x00000001);
}

void porte_set(int i){
	PORTESET = (0x1 << i);
}

void porte_clr(int i){
	PORTECLR = (0x1 << i);
}

int portd_get(int i){
	return (PORTD >> i) & 0x1;
}

void portd_set(int i){
	PORTDSET = (0x1 << i);
}

void portd_clr(int i){
	PORTDCLR = (0x1 << i);
}

/* Updates controller input and stores the state of the buttons 
 * for both controllers in the p_buttons array */
void controller_update(char p_buttons[2][8]){
		portd_set(9);
		portd_clr(9);
		int i = 0;
		while(i < 8){
			p_buttons[0][i] = portd_get(1);
			p_buttons[1][i] = portd_get(2);
			portd_set(10);
			portd_clr(10);
			//delay();
			
			i++;
		}
	}

/*Creates sprites for both players */
void model_setup(char model[2][10]){
	int i;
	for(i = 0; i < 2; i++){
		model[i][0] = 4;
		model[i][1] = 4;
		model[i][2] = 0x6;
		model[i][3] = 0xf;
		model[i][4] = 0xf;
		model[i][5] = 0x6;
	}
	
}
