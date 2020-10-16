/* 
 * File:  st7735UI.h 
 * Author: Leo Tovarys
 * Comments:
 * Revision history: 
 */

#ifndef ST7735UI_H
#define	ST7735UI_H

#include <xc.h> // include processor files - each processor file is guarded. 

typedef struct Temperature {
    char name[ 8 ];
    unsigned char real_temp[ 5 ];
    unsigned char prev_real_temp[ 5 ];
    unsigned char set_temp[ 5 ];
} Temperature; 

typedef struct Screen {
    Temperature *temp;
    int id;
    int mode;
    int align;
} Screen;

void show_screen( Screen * );

void show_temperature( Temperature *, int, int );

void show_name( Temperature *, int, int, int );

void set_temperature( Temperature * );

#endif

