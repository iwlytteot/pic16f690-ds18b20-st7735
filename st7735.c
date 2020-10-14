#include "st7735.h"
#include "tftfont.h"

void SPI( unsigned char val )        // send character over SPI
{
    cs = 0;    // Select the LCD	(active low)
    SSPBUF = val;            // load character
    while ( !BF );        // sent
    cs = 1;    // Deselect LCD (active low)
}

void command( unsigned char cmd ) {
    dc = 0;       // Command Mode
    SPI( cmd );    // set up data on bus
}

void LCDinit() {
    rst = 1;            //hardware reset
    __delay_ms( 200 );
    rst = 0;
    __delay_ms( 10 );
    rst = 1;
    __delay_ms( 10 );

    command( 0x01 ); // sw reset
    __delay_ms( 200 );

    command( 0x11 ); // Sleep out
    __delay_ms( 200 );

    command( 0x3A ); //color mode
    send_data( 0x05 );    //16 bits


    command( 0x36 ); //Memory access ctrl (directions)
    send_data( 0x60 );

    command( 0x13 ); //Normal display on
    command( 0x29 ); //Main screen turn on
}

void send_data( unsigned char data ) {
    dc = 1;       // data mode
    SPI( data );    // set up data on bus
}

void area( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1 ) {
    command( 0x2A ); // Column addr set
    send_data( 0x00 );
    send_data( x0 );     // XSTART
    send_data( 0x00 );
    send_data( x1 );     // XEND

    command( 0x2B ); // Row addr set
    send_data( 0x00 );
    send_data( y0 );     // YSTART
    send_data( 0x00 );
    send_data( y1 );     // YEND

    command( 0x2C ); // write to RAM
}

void rectan( unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned int color ) {
    unsigned int i;
    area( x0, y0, x1, y1 );
    for ( i = ( y1 - y0 + 1 ) * ( x1 - x0 + 1 ); i > 0; i-- ) {

        dc = 1;       // data mode
        cs = 0;
        SPI( color >> 8 );
        SPI( color );
        cs = 1;
    }
}

void pixel( unsigned char x, unsigned char y, unsigned int color ) {
    area( x, y, x + 1, y + 1 );
    send_data( color >> 8 );
    send_data( color );
}

void draw( unsigned char x, unsigned char y, unsigned char c, unsigned int color, unsigned char size ) //character
{
    unsigned char line;

    for ( int i = 0; i < 8; ++i ) {
        line = font[ ( c * 8 ) + i ];
        for ( int j = 7; j != -1; --j ) {
            if ( line & 0x1 ) {
                if ( size == 1 )
                    pixel( x + j, y + i, color );
                else
                    rectan( x + ( j * size ), y + ( i * size ), x + ( j * size ) + size, y + ( i * size ) + size,
                            color );
            }
            line >>= 1;
        }
    }
}