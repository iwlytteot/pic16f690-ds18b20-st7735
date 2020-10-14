#include "ds18b20.h"

__bit ds18b20_start() {
    DS18B20_PIN = 0;      // send reset pulse to the DS18B20 sensor
    DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
    __delay_us( 500 );      // wait 500 us

    DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
    __delay_us( 100 );      // wait 100 us to read the DS18B20 sensor response

    if ( !DS18B20_PIN ) {
        __delay_us( 400 );    // wait 400 us
        return 1;           // DS18B20 sensor is present
    }

    return 0;   // connection error
}

void ds18b20_write_bit( uint8_t value ) {
    DS18B20_PIN = 0;
    DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
    __delay_us( 2 );        // wait 2 us

    DS18B20_PIN = ( __bit ) value;
    __delay_us( 80 );       // wait 80 us

    DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
    __delay_us( 2 );        // wait 2 us
}

void ds18b20_write_byte( uint8_t value ) {
    for ( uint8_t i = 0; i < 8; i++ )
        ds18b20_write_bit( value >> i );
}

__bit ds18b20_read_bit() {
    static __bit value;

    DS18B20_PIN = 0;
    DS18B20_PIN_Dir = 0;  // configure DS18B20_PIN pin as output
    __delay_us( 2 );

    DS18B20_PIN_Dir = 1;  // configure DS18B20_PIN pin as input
    __delay_us( 5 );        // wait 5 us

    value = DS18B20_PIN;  // read and store DS18B20 state
    __delay_us( 100 );      // wait 100 us

    return value;
}

uint8_t ds18b20_read_byte() {
    uint8_t value = 0;

    for ( uint8_t i = 0; i < 8; i++ )
        value |= ds18b20_read_bit() << i;

    return value;
}

__bit ds18b20_read( uint16_t *raw_temp_value ) {
    if ( !ds18b20_start())   // send start pulse
        return 0;             // return 0 if error

    ds18b20_write_byte( 0xCC );   // send skip ROM command
    ds18b20_write_byte( 0x44 );   // send start conversion command

    while ( !ds18b20_read_byte());  // wait for conversion complete

    if ( !ds18b20_start())  // send start pulse
        return 0;            // return 0 if error

    ds18b20_write_byte( 0xCC );  // send skip ROM command
    ds18b20_write_byte( 0xBE );  // send read command

    // read temperature LSB byte and store it on raw_temp_value LSB byte
    *raw_temp_value = ds18b20_read_byte();
    // read temperature MSB byte and store it on raw_temp_value MSB byte
    *raw_temp_value |= ( uint16_t )( ds18b20_read_byte() << 8 );

    return 1;   // OK --> return 1
}