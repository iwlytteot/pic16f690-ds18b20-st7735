/* 
 * File:  st7735UI.h 
 * Author: Leo Tovary?
 * Comments:
 * Revision history: 
 */

#ifndef ST7735UI_H
#define	ST7735UI_H

#include <xc.h> // include processor files - each processor file is guarded. 

typedef struct Temperature {
    char name[8];
    unsigned char real_temp[6];
    unsigned char set_temp[6];
} Temperature; 

void view_temperature( Temperature *, Temperature * );

void set_temperature( Temperature * );

#endif	/* XC_HEADER_TEMPLATE_H */

