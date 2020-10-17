#ifndef ST7735_H
#define	ST7735_H

#include "pic16f690.h"
#include <xc.h>

#define _XTAL_FREQ 8000000

#define cs RC2		//Chip select
#define dc RC0      //DC or AO
#define rst RC1     //Reset

void SPI( unsigned char val );

void command( unsigned char cmd );

void LCDinit( void );

void send_data( unsigned char data );

void area( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1 );

void rectan( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color );

void pixel( unsigned char x, unsigned char y, unsigned int color );

void draw( unsigned char x, unsigned char y, unsigned char c, unsigned int color, unsigned char size );

#endif