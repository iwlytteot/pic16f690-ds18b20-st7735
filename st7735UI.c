#include "st7735UI.h"
#include "st7735.h"

void show_name( Temperature *temperature, int x, int y, int clear ) {
    for ( int i = 0; i < 8; ++i) { 
        draw( x + ( i * 18 ), y, temperature->name[ i ], clear ? 0x0000 : 0x07FF, 3 );
    }
}

void show_temperature( Temperature *temperature, int x, int y, int clear ) {
    for ( int i = 0; i < 5; ++i) { 
        draw( x + ( i * 22 ), y, temperature->real_temp[ i ], clear ? 0x0000 : 0x07FF, 3 );
    }
    
}

void show_screen( Screen *screen ) {
    show_name( screen->temp, 0, 5, 0 );
    show_temperature( screen->temp, 15, 57, 0 );
    /* drawing underlines for numbers */
    if ( screen->mode == 1 ) {
        if ( screen->align == 0 )
            draw( 15 + 22 * ( screen->align + 3 ), 62, 95, 0x0000, 3 );
        else
            draw( 15 + 22 * ( screen->align - 1 ), 62, 95, 0x0000, 3 );
        draw( 15 + 22 * ( screen->align ), 62, 95, 0xFFE0, 3 );
    }    
}


