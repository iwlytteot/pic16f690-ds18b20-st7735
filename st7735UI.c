#include "st7735UI.h"
#include "st7735.h"
#include "ds18b20.h"

void show_name( Temperature *temperature, int x, int y, int clear ) {
    for ( int i = 0; i < 8; ++i) { 
        draw( x + ( i * 18 ), y, temperature->name[ i ], clear ? 0x0000 : 0x07FF, 3 );
    }
}

void show_temperature( Temperature *temperature, int x, int y ) {
    for ( int i = 0; i < 5; ++i) { 
        if ( temperature->prev_real_temp[ i ] != temperature->real_temp[ i ] ) {
            draw( x + ( i * 22 ), y, temperature->prev_real_temp[ i ], 0x0000, 3 );
        }
        draw( x + ( i * 22 ), y, temperature->real_temp[ i ], 0x07FF, 3 );
    } 
}

void show_set_temperature( Temperature *temperature, int x, int y ) {
    for ( int i = 0; i < 5; ++i) { 
        if ( temperature->prev_set_temp[ i ] != temperature->set_temp[ i ] ) {
            draw( x + ( i * 22 ), y, temperature->prev_set_temp[ i ], 0x0000, 3 );
        }
        draw( x + ( i * 22 ), y, temperature->set_temp[ i ], 0x07FF, 3 );
    } 
}

void show_screen( Screen *screen ) {
    show_name( screen->temp, 0, 5, 0 );
    
    /* view mode  */
    if ( screen->mode == 0 ) {
        
        for ( int i = 0; i < 5; ++i )
            screen->temp->prev_real_temp[ i ] = screen->temp->real_temp[ i ];

        read_temperature( screen->temp->real_temp );          
        
        show_temperature( screen->temp, 15, 57 );

    }
    
    /* temperature change mode */
    if ( screen->mode == 1 ) {
        WDTCON = 0; // Turning OFF Watchdog timer, as we do not need him here
        while ( BUTTON_SET_F ) {
            for ( int i = 0; i < 5; ++i )
                screen->temp->prev_set_temp[ i ] = screen->temp->set_temp[ i ];

            int integer_part = ( screen->temp->set_temp[0] - 48 ) * 10 + ( screen->temp->set_temp[1] - 48 );
            if ( !BUTTON_UP_F ) {
                if ( screen->temp->set_temp[ 3 ]++ == 57 ) { //eg 18.9
                    ++integer_part;
                    screen->temp->set_temp[ 3 ] = 48;
                }
            }
            if ( !BUTTON_DOWN_F ) {
                if ( screen->temp->set_temp[ 3 ]-- == 48 ) {
                    --integer_part;
                    screen->temp->set_temp[ 3 ] = 57;
                }
            }

            screen->temp->set_temp[0] = ( ( integer_part / 10 ) % 10 ) + 48;
            screen->temp->set_temp[1] = ( integer_part % 10 ) + 48;
            show_set_temperature( screen->temp, 15, 57 );
        }
        WDTCON = 0b01101; //Turning Watchdog timer back ON
    }    
}


