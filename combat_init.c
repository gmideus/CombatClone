#include <stdint.h>   
#include <pic32mx.h> 
#include "combat.h"



void timer_init(){
	T2CON = 0x70;
	PR2 = 0x1458;
	T2CONSET = 0x8000;
	IFS(0) = 0;
}

void io_init(void){
	TRISECLR = 0xff;   	//set LEDs as output
	PORTE = 0x0;
	TRISDCLR = 0x600;	//set output port for controller (latch and clock)
	TRISDSET = 0x6;		//set input ports for controller data

}

void display_init(void) {
    PORTFCLR = 0x10;
	quicksleep(10);
	PORTFCLR = 0x40;
	quicksleep(1000000);
	
	spi_send_recv(0xAE);
	PORTGCLR = 0x200;
	quicksleep(10);
	PORTGSET = 0x200;
	quicksleep(10);
	
	spi_send_recv(0x8D);
	spi_send_recv(0x14);
	
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);
	
	PORTFCLR = 0x20;
	quicksleep(10000000);
	
	spi_send_recv(0xA1);
	spi_send_recv(0xC8);
	
	spi_send_recv(0xDA);
	spi_send_recv(0x20);
	
	spi_send_recv(0xAF);
}


/*Creates sprites for both players */
void model_setup(char model[2][10], char models[8][8]){
	int i;
	for(i = 0; i < 2; i++){
		model[i][0] = 5;
		model[i][1] = 5;
		/*
		model[i][2] = 0x6;
		model[i][3] = 0xf;
		model[i][4] = 0xf;
		model[i][5] = 0x6;
		*/
		model[i][2] = 0x04;
		model[i][3] = 0x06;
		model[i][4] = 0x1f;
		model[i][5] = 0x0e;
		model[i][6] = 0x05;
		/*
		model[i][2] = 0x1e;
		model[i][3] = 0x1c;
		model[i][4] = 0x0f;
		model[i][5] = 0x1c;
		model[i][6] = 0x1e;
		*/
	}
	//Right
	models[0][0] = 0x1b;
	models[0][1] = 0x1f;
	models[0][2] = 0x1f;
	models[0][3] = 0x15;
	models[0][4] = 0x04;

	//Right down
	models[1][0] = 0x04;
	models[1][1] = 0x0c;
	models[1][2] = 0x1f;
	models[1][3] = 0x0e;
	models[1][4] = 0x14;

	//Down
	models[2][0] = 0x0f;
	models[2][1] = 0x07;
	models[2][2] = 0x1e;
	models[2][3] = 0x07;
	models[2][4] = 0x0f;

	//left down
	models[3][0] = 0x14;
	models[3][1] = 0x0e;
	models[3][2] = 0x1f;
	models[3][3] = 0x0c;
	models[3][4] = 0x04;

	//Left
	models[4][0] = 0x04;
	models[4][1] = 0x15;
	models[4][2] = 0x1f;
	models[4][3] = 0x1f;
	models[4][4] = 0x1b;

	//up left
	models[5][0] = 0x05;
	models[5][1] = 0x0e;
	models[5][2] = 0x1f;
	models[5][3] = 0x06;
	models[5][4] = 0x04;

	//Up
	models[6][0] = 0x1e;
	models[6][1] = 0x1c;
	models[6][2] = 0x0f;
	models[6][3] = 0x1c;
	models[6][4] = 0x1e;

	//up left
	models[7][0] = 0x04;
	models[7][1] = 0x06;
	models[7][2] = 0x1f;
	models[7][3] = 0x0e;
	models[7][4] = 0x05;

	
}

void bullet_init(int bullets[NUMBER_OF_BULLETS][6]){
	int i;
	for(i = 0; i < NUMBER_OF_BULLETS; i++){
		bullets[i][0] = 0;
	}
}


	
