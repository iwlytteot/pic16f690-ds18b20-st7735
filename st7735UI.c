#include "st7735UI.h"
#include "st7735.h"

void view_temperature( Temperature *fst, Temperature *snd ) {
    for ( int i = 0; i < 7; ++i) {
        draw( 10 + ( i * 16 ), 10, fst->name[ i ], 0xF800, 2 );
        draw( 10 + ( i * 16 ), 64, snd->name[ i ], 0xF800, 2 );
        
        if ( i == 6 )
            break;
        
        draw( 10 + ( i * 17 ), 35, fst->real_temp[ i ], 0x07FF, 2 );
        draw( 10 + ( i * 17 ), 89, snd->real_temp[ i ], 0x07FF, 2 );
    }
}
