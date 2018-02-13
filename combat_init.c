#include <stdint.h>   
#include <pic32mx.h>  

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
