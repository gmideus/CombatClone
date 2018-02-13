
#include <stdint.h>   
#include <pic32mx.h>  


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


/*Send display data with SPI to the display */
void display_update(char* display_data) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		PORTFCLR = 0x10;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		PORTFSET = 0x10;
		
		for(j = 0; j < 128; j++) {
			spi_send_recv(display_data[i*128 + j]);
		}
	}
}

boundary_check(int position[2], int size[10]){
	int boundary[2]  = { 128, 32 };
	int i;
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



