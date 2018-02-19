
#include <stdint.h>   
#include <pic32mx.h>  
#include "combat.h"


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

display_data_update(char* data, int position[NUMBER_OF_PLAYERS][2], char model[NUMBER_OF_PLAYERS][10], int bullets[NUMBER_OF_BULLETS][6]){  
	int p, i, j;
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){
		for(i = 0; i < model[p][0]; i++){
			for(j = 0; j < model[p][1]; j++){
				if((model[p][i+2] >> j) & 0x1){
					int a = (position[p][1]+j)/8;
					data[a*WIDTH + position[p][0] + i] |= (0x1 << (position[p][1]+j)%8);
				}
			}
		}
	}
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0]){
			int a = (bullets[i][2])/8;
			data[a*WIDTH + bullets[i][1]] |= (0x1 << bullets[i][2]%8);
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
		
		for(j = 0; j < WIDTH; j++) {
			spi_send_recv(display_data[i*WIDTH + j]);
		}
	}
}

void boundary_check(int position[2], char size[10], float position_f[2]){
	int boundary[2]  = { WIDTH, HEIGHT };
	int i;
	for(i = 0; i < 2; i++){
		if(position[i] < 0){
			position[i] = 0;
			position_f[i] = 0;
			
		}
		if(position[i] > boundary[i] - size[i]){
			position[i] = (boundary[i] - size[i]);
			position_f[i] = (float) (boundary[i] - size[i]);
		}
	}
	
}

void hit_check(int position[2], char size[10], int bullets[NUMBER_OF_BULLETS][6], int* HP){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0]){
			if((bullets[i][1] >= position[0] && bullets[i][1] <= (position[0] + size[0])) && (bullets[i][2] >= position[1] && bullets[i][2] <= (position[1] + size[1]))){
				*HP -= 1;
				bullets[i][0] = 0;
			}
		}
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
			i++;
		}
	}


void create_bullet(int bullets[NUMBER_OF_BULLETS][6], int x_position, int y_position, int x_speed, int y_speed){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0] == 0){
			bullets[i][0] = 1;
			bullets[i][1] = x_position + 2 + (x_speed*3);
			bullets[i][2] = y_position + 2 + (y_speed*3);
			bullets[i][3] = x_speed;
			bullets[i][4] = y_speed;
			bullets[i][5] = 0;
			return;
		}
	}
}
	
void bullet_update(int bullets[NUMBER_OF_BULLETS][6]){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0]){
			if(bullets[i][1] <= 0 || bullets[i][1] >= WIDTH - 1){
				bullets[i][3] = - bullets[i][3];
			}
			if(bullets[i][2] <= 0 || bullets[i][2] >= HEIGHT - 1){
				bullets[i][4] = - bullets[i][4];
			}
			bullets[i][1] += bullets[i][3];
			bullets[i][2] += bullets[i][4];
			bullets[i][5] += 1;
			if(bullets[i][5] >= BULLET_DURATION){
				bullets[i][0] = 0;
			}
			
		}
	}
	
}

