#ifndef DS18B20_H
#define	DS18B20_H


#include "pic16f690.h"
#include <stdint.h>  
#include <xc.h>

#define _XTAL_FREQ 8000000
#define DS18B20_PIN      RA2
#define DS18B20_PIN_Dir  TRISA2

uint16_t raw_temp;

__bit ds18b20_start();

void ds18b20_write_bit( uint8_t );

void ds18b20_write_byte( uint8_t );

__bit ds18b20_read_bit();

uint8_t ds18b20_read_byte();

__bit ds18b20_read( uint16_t * );

void read_temperature( unsigned char * );

#endif