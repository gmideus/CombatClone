
#include <stdint.h>   
#include <pic32mx.h>  
#include "combat.h"

const uint8_t const font[] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 94, 0, 0, 0, 0,
	0, 0, 4, 3, 4, 3, 0, 0,
	0, 36, 126, 36, 36, 126, 36, 0,
	0, 36, 74, 255, 82, 36, 0, 0,
	0, 70, 38, 16, 8, 100, 98, 0,
	0, 52, 74, 74, 52, 32, 80, 0,
	0, 0, 0, 4, 3, 0, 0, 0,
	0, 0, 0, 126, 129, 0, 0, 0,
	0, 0, 0, 129, 126, 0, 0, 0,
	0, 42, 28, 62, 28, 42, 0, 0,
	0, 8, 8, 62, 8, 8, 0, 0,
	0, 0, 0, 128, 96, 0, 0, 0,
	0, 8, 8, 8, 8, 8, 0, 0,
	0, 0, 0, 0, 96, 0, 0, 0,
	0, 64, 32, 16, 8, 4, 2, 0,
	0, 62, 65, 73, 65, 62, 0, 0,
	0, 0, 66, 127, 64, 0, 0, 0,
	0, 0, 98, 81, 73, 70, 0, 0,
	0, 0, 34, 73, 73, 54, 0, 0,
	0, 0, 14, 8, 127, 8, 0, 0,
	0, 0, 35, 69, 69, 57, 0, 0,
	0, 0, 62, 73, 73, 50, 0, 0,
	0, 0, 1, 97, 25, 7, 0, 0,
	0, 0, 54, 73, 73, 54, 0, 0,
	0, 0, 6, 9, 9, 126, 0, 0,
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0, 0, 126, 9, 9, 126, 0, 0,
	0, 0, 127, 73, 73, 54, 0, 0,
	0, 0, 62, 65, 65, 34, 0, 0,
	0, 0, 127, 65, 65, 62, 0, 0,
	0, 0, 127, 73, 73, 65, 0, 0,
	0, 0, 127, 9, 9, 1, 0, 0,
	0, 0, 62, 65, 81, 50, 0, 0,
	0, 0, 127, 8, 8, 127, 0, 0,
	0, 0, 65, 127, 65, 0, 0, 0,
	0, 0, 32, 64, 64, 63, 0, 0,
	0, 0, 127, 8, 20, 99, 0, 0,
	0, 0, 127, 64, 64, 64, 0, 0,
	0, 127, 2, 4, 2, 127, 0, 0,
	0, 127, 6, 8, 48, 127, 0, 0,
	0, 0, 62, 65, 65, 62, 0, 0,
	0, 0, 127, 9, 9, 6, 0, 0,
	0, 0, 62, 65, 97, 126, 64, 0,
	0, 0, 127, 9, 9, 118, 0, 0,
	0, 0, 38, 73, 73, 50, 0, 0,
	0, 1, 1, 127, 1, 1, 0, 0,
	0, 0, 63, 64, 64, 63, 0, 0,
	0, 31, 32, 64, 32, 31, 0, 0,
	0, 63, 64, 48, 64, 63, 0, 0,
	0, 0, 119, 8, 8, 119, 0, 0,
	0, 3, 4, 120, 4, 3, 0, 0,
	0, 0, 113, 73, 73, 71, 0, 0,
	0, 0, 127, 65, 65, 0, 0, 0,
	0, 2, 4, 8, 16, 32, 64, 0,
	0, 0, 0, 65, 65, 127, 0, 0,
	0, 4, 2, 1, 2, 4, 0, 0,
	0, 64, 64, 64, 64, 64, 64, 0,
	0, 0, 1, 2, 4, 0, 0, 0,
	0, 0, 48, 72, 40, 120, 0, 0,
	0, 0, 127, 72, 72, 48, 0, 0,
	0, 0, 48, 72, 72, 0, 0, 0,
	0, 0, 48, 72, 72, 127, 0, 0,
	0, 0, 48, 88, 88, 16, 0, 0,
	0, 0, 126, 9, 1, 2, 0, 0,
	0, 0, 80, 152, 152, 112, 0, 0,
	0, 0, 127, 8, 8, 112, 0, 0,
	0, 0, 0, 122, 0, 0, 0, 0,
	0, 0, 64, 128, 128, 122, 0, 0,
	0, 0, 127, 16, 40, 72, 0, 0,
	0, 0, 0, 127, 0, 0, 0, 0,
	0, 120, 8, 16, 8, 112, 0, 0,
	0, 0, 120, 8, 8, 112, 0, 0,
	0, 0, 48, 72, 72, 48, 0, 0,
	0, 0, 248, 40, 40, 16, 0, 0,
	0, 0, 16, 40, 40, 248, 0, 0,
	0, 0, 112, 8, 8, 16, 0, 0,
	0, 0, 72, 84, 84, 36, 0, 0,
	0, 0, 8, 60, 72, 32, 0, 0,
	0, 0, 56, 64, 32, 120, 0, 0,
	0, 0, 56, 64, 56, 0, 0, 0,
	0, 56, 64, 32, 64, 56, 0, 0,
	0, 0, 72, 48, 48, 72, 0, 0,
	0, 0, 24, 160, 160, 120, 0, 0,
	0, 0, 100, 84, 84, 76, 0, 0,
	0, 0, 8, 28, 34, 65, 0, 0,
	0, 0, 0, 126, 0, 0, 0, 0,
	0, 0, 65, 34, 28, 8, 0, 0,
	0, 0, 4, 2, 4, 2, 0, 0,
	0, 120, 68, 66, 68, 120, 0, 0,
};

char textbuffer[4][16];

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

display_data_update(char* data, int position[NUMBER_OF_PLAYERS][2], char model[NUMBER_OF_PLAYERS][10], int bullets[NUMBER_OF_BULLETS][6], char models[8][8]){  
	int p, i, j;
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){
		for(i = 0; i < model[p][0]; i++){
			for(j = 0; j < model[p][1]; j++){
				if((models[model[p][2]][i] >> j) & 0x1){
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

int hit_check(int position[2], char size[10], int bullets[NUMBER_OF_BULLETS][6], int* HP){
	int i;
	int ret = 0;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0]){
			if((bullets[i][1] >= position[0] && bullets[i][1] <= (position[0] + size[0])) && (bullets[i][2] >= position[1] && bullets[i][2] <= (position[1] + size[1]))){
				*HP -= 1;
				if(*HP <= 0){
					ret = 1;
				}
				bullets[i][0] = 0;
			}
		}
	}
	return ret;
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


void create_bullet(int bullets[NUMBER_OF_BULLETS][6], float bullets_f[NUMBER_OF_BULLETS][4], int x_position, int y_position, float* speed){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0] == 0){
			bullets_f[i][0] = x_position + 2 + (speed[0]*5);
			bullets_f[i][1] = y_position + 2 + (speed[1]*5);
			bullets_f[i][2] = speed[0];
			bullets_f[i][3] = speed[1];
			bullets[i][0] = 1;
			bullets[i][1] = (int) (bullets_f[i][0] + 0.5);
			bullets[i][2] = (int) (bullets_f[i][1] + 0.5);
			bullets[i][5] = 0;
			return;
		}
	}
}
	
void bullet_update(int bullets[NUMBER_OF_BULLETS][6], float bullets_f[NUMBER_OF_BULLETS][4]){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		if(bullets[i][0]){
			
			if(bullets[i][1] <= 0 || bullets[i][1] >= WIDTH - 1){
				bullets_f[i][2] = - bullets_f[i][2];
			}
			if(bullets[i][2] <= 0 || bullets[i][2] >= HEIGHT - 1){
				bullets_f[i][3] = -bullets_f[i][3];
			}
			bullets_f[i][0] += bullets_f[i][2];
			bullets_f[i][1] += bullets_f[i][3];
			bullets[i][1] = (int) (bullets_f[i][0] + 0.5);
			bullets[i][2] = (int) (bullets_f[i][1] + 0.5);
			bullets[i][5] += 1;
			if(bullets[i][5] >= BULLET_DURATION){
				bullets[i][0] = 0;
			}
			
		}
	}
	
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void display_string_update(void) {
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		PORTFCLR = 0x10;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		PORTFSET = 0x10;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}
