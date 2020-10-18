/* 
 * File:  st7735UI.h 
 * Author: Leo Tovarys
 * Comments:
 * Revision history: 
 */

#ifndef ST7735UI_H
#define	ST7735UI_H
#define BUTTON_UP_F     PORTCbits.RC3
#define BUTTON_DOWN_F   PORTCbits.RC4

#include <xc.h>

typedef struct Temperature {
    char name[ 8 ];
    unsigned char real_temp[ 5 ];
    unsigned char prev_real_temp[ 5 ];
    unsigned char set_temp[ 5 ];
    unsigned char prev_set_temp[ 5 ];
} Temperature; 

typedef struct Screen {
    Temperature *temp;
    int id;
    int mode;
} Screen;

void show_screen( Screen * );

void show_temperature( Temperature *, int, int );

void show_set_temperature( Temperature *, int, int );

void show_name( Temperature *, int, int, int );

void set_temperature( Temperature * );

#endif

