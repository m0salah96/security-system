#define F_CPU 1000000UL  	// define crystal frequency for delay.h
#include "LCD_Lib.h"
#include <avr/io.h>  		// standard AVR header
#include <util/delay.h>
#define SS 4			// Slave Select        is Bit No.4
#define MOSI 5 			// Master Out Slave In is Bit No.5
#define MISO 6			// Master In Slave Out is Bit No.6
#define SCK 7 			// Shift Clock         is Bit No.7

void SPI_SlaveInit(void){
	DDRB |= (1<<MISO); 	// Set MISO as an Output Pin
	// Set MOSI, SCK and SS as Input Pins
	DDRB &= ~(1<<MOSI) & ~(1<<SCK) & ~(1<<SS) ;
	// Enable SPI as a Slave Device
	SPCR = (1<<SPE);
}
////////////////////// SPI SLAVE PROGRAM PAGE 2/2  ///////////////////////
unsigned char SPI_SlaveReceive(unsigned char cData){
	SPDR = cData; 				// send cData to master
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));
	// Return received data
	return SPDR;
}

int main(){LCD_Initialization();
	
	SPI_SlaveInit();				// configure as SPI Slave
      char x[6]={'1','2','3','4','5','6'};
	// send value of PORTA to Master and
	// Show Received data at PORTA
	while (1)
	{char i = SPI_SlaveReceive(x[i]);
		//LCD_Write_Character(x[i]);
	}
	
	return 0;
}
