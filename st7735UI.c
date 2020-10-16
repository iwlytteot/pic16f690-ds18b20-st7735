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

void show_screen( Screen *screen ) {
    show_name( screen->temp, 0, 5, 0 );
    
    /* view mode  */
    if ( screen->mode == 0 ) {
        
        show_temperature( screen->temp, 15, 57 );
        __delay_ms( 3000 );
        
        for ( int i = 0; i < 5; ++i )
            screen->temp->prev_real_temp[ i ] = screen->temp->real_temp[ i ];

        read_temperature( screen->temp->real_temp );               
    }
    
    /* temperature change mode */
    if ( screen->mode == 1 ) {
        if ( 1 ) {  // 1 is prepared for button trigger UP
            if ( screen->temp->set_temp[ 3 ] == 57 ) { 
                if ( screen->temp->set_temp[ 1 ] == 57 ) {
                    ++screen->temp->set_temp[ 0 ];
                    screen->temp->set_temp[ 1 ] = 48; 
                } else {
                    ++screen->temp->set_temp[ 1 ];
                }
                screen->temp->set_temp[ 3 ] == 48;
            }
            else if ( screen->temp->set_temp[ 3 ] != 57 ) {
                ++screen->temp->set_temp[ 3 ];
            }
        }
        
        if ( 0 ) {  // 0 is prepared for button trigger DOWN
            if ( screen->temp->set_temp[ 3 ] == 48 ) { 
                if ( screen->temp->set_temp[ 1 ] == 48 ) {
                    --screen->temp->set_temp[ 0 ];
                    screen->temp->set_temp[ 1 ] = 57; 
                } else {
                    --screen->temp->set_temp[ 1 ];
                }
                    screen->temp->set_temp[ 3 ] == 57;
            }
            else if ( screen->temp->set_temp[ 3 ] != 48 ) {
                --screen->temp->set_temp[ 3 ];
            } 
        }
    }    
}


