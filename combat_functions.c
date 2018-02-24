
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
	0x00, 0x7e, 0x81, 0x81, 0x81, 0x7e, 0x00, 0x00,		//0
	0x00, 0x00, 0x00, 0x82, 0xff, 0x80, 0x00, 0x00,		//1
	0x00, 0xc6, 0xa1, 0x91, 0x89, 0x87, 0x00, 0x00,		//2
	0x00, 0x81, 0x89, 0x89, 0x89, 0xf7, 0x00, 0x00,		//3
	0x10, 0x18, 0x14, 0x12, 0x11, 0xff, 0x00, 0x00,		//4
	0x00, 0x8f, 0x89, 0x89, 0x91, 0x61, 0x00, 0x00,		//5
	0x00, 0x7f, 0x89, 0x89, 0x89, 0x71, 0x00, 0x00,		//6
	0x00, 0x03, 0x81, 0x61, 0x11, 0x09, 0x07, 0x00,		//7
	0x00, 0x76, 0x89, 0x89, 0x89, 0x89, 0x76, 0x00,		//8
	0x00, 0x0e, 0x11, 0x11, 0x11, 0xff, 0x00, 0x00, 	//9
	0, 0, 0, 102, 0, 0, 0, 0,
	0, 0, 128, 102, 0, 0, 0, 0,
	0, 0, 8, 20, 34, 65, 0, 0,
	0, 0, 20, 20, 20, 20, 0, 0,
	0, 0, 65, 34, 20, 8, 0, 0,
	0, 2, 1, 81, 9, 6, 0, 0,
	0, 28, 34, 89, 89, 82, 12, 0,
	0x80, 0xfc, 0x92, 0x11, 0x92, 0xfc, 0x80, 0x00,  	//A (0, 0, 126, 9, 9, 126, 0, 0,)
	0x81, 0xff, 0x89, 0x89, 0x89, 0x76, 0x00, 0x00,  	//B
	0x00, 0x7e, 0x81, 0x81, 0x81, 0xc3, 0x00, 0x00,  	//C
	0x81, 0xff, 0x81, 0x81, 0x81, 0x42, 0x3c, 0x00,		//D
	0x00, 0xff, 0x89, 0x89, 0x89, 0x81, 0xc3, 0x00,		//E
	0x80, 0xff, 0x89, 0x09, 0x09, 0x01, 0x03, 0x00,		//F
	0x00, 0x7e, 0x81, 0x81, 0x91, 0xf3, 0x10, 0x00,		//G
	0x81, 0xff, 0x89, 0x08, 0x08, 0x89, 0xff, 0x81,		//H
	0x00, 0x00, 0x81, 0xff, 0x81, 0x00, 0x00, 0x00,		//I
	0x00, 0x70, 0x80, 0x80, 0x81, 0x7f, 0x01, 0x00,		//J
	0x81, 0xff, 0x89, 0x14, 0x22, 0x41, 0x81, 0x80,		//K
	0x01, 0xff, 0x80, 0x80, 0x80, 0x80, 0xc0, 0x00,		//L
	0x81, 0xff, 0x82, 0x04, 0x08, 0x04, 0x83, 0xff,		//M
	0x81, 0xff, 0x06, 0x08, 0x10, 0x60, 0xff, 0x00,		//N
	0x00, 0x3c, 0x42, 0x81, 0x81, 0x42, 0x3c, 0x00,		//O
	0x00, 0x81, 0xff, 0x91, 0x11, 0x11, 0x0e, 0x00,		//P
	0x3c, 0x42, 0x81, 0x91, 0xa1, 0x42, 0xbc, 0x00,		//Q
	0x81, 0xff, 0x91, 0x11, 0x11, 0x2e, 0xc0, 0x80,		//R
	0x00, 0xce, 0x89, 0x89, 0x89, 0x73, 0x00, 0x00,		//S
	0x03, 0x01, 0x81, 0xff, 0x81, 0x01, 0x03, 0x00,		//T
	0x01, 0x7f, 0x80, 0x80, 0x81, 0x7f, 0x80, 0x00,		//U
	0x01, 0x1f, 0x21, 0xc0, 0x21, 0x1f, 0x01, 0x00,		//V
	0x01, 0xff, 0x41, 0x20, 0x10, 0x20, 0x41, 0xff,		//W
	0x81, 0xc3, 0xa5, 0x18, 0x18, 0xa5, 0xc3, 0x81,		//X
	0x01, 0x0f, 0x91, 0xe0, 0x91, 0x0f, 0x01, 0x00,		//Y
	0xc3, 0xa1, 0x91, 0x89, 0x85, 0x83, 0xc1, 0x00,		//Z
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
// This function updates the display.  
display_data_update(char* data, int position[NUMBER_OF_PLAYERS][2], char model[NUMBER_OF_PLAYERS][10], int bullets[NUMBER_OF_BULLETS][6], char models[8][8]){  
	int p, i, j;
	for(p = 0; p < NUMBER_OF_PLAYERS; p++){ //Display update for each player
		for(i = 0; i < model[p][0]; i++){ // Size in x
			for(j = 0; j < model[p][1]; j++){ // Size in y
				if((models[model[p][2]][i] >> j) & 0x1){
					int a = (position[p][1]+j)/8; // Calculates which row (4 rows, each 8 pixels wide) in which to draw.  
					data[a*WIDTH + position[p][0] + i] |= (0x1 << (position[p][1]+j)%8); 
				}
			}
		}
	}
	for(i = 0; i < NUMBER_OF_BULLETS; i++){ //Display update for bullets 
		if(bullets[i][0]){
			int a = (bullets[i][2])/8; //See above drawing method
			data[a*WIDTH + bullets[i][1]] |= (0x1 << bullets[i][2]%8);
		}
	}
}


//Copied from Lab. Sends Data to display 
uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}


/*Send display data with SPI to the display */
//Derived from Lab code
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

// This method prevents players and bullets from moving outside the boundaries of a screen 
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
