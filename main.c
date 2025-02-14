#pragma config FOSC = EXTRCIO  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <string.h>
#include "ds18b20.h"
#include "st7735.h"
#include "st7735UI.h"

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BUTTON_SWAP     TRISBbits.TRISB7
#define BUTTON_SWAP_F   PORTBbits.RB7
#define BUTTON_SET      TRISBbits.TRISB4
#define BUTTON_SET_F    PORTBbits.RB4
#define BUTTON_UP       TRISCbits.TRISC3
#define BUTTON_DOWN     TRISCbits.TRISC4


int CHANGE = 0;

void __interrupt() isr() {
    if ( INTCONbits.RABIF == 1 ) {
        if ( BUTTON_SWAP_F == 0 ) {
           CHANGE = 1; 
        }        
        if ( BUTTON_SET_F == 0 ) {
            CHANGE = 2;
        }
        INTCONbits.RABIF = 0;
    }
}

void init_pic() {
    OSCCON = 0x70;
    TRISC = 0; 
    BUTTON_SWAP = 1;
    BUTTON_SET = 1;
    BUTTON_UP = 1;
    BUTTON_DOWN = 1;
    TRISB5 = 0;
    TRISB6 = 0;
    ANSEL = 0;            //digital port
    ANSELH = 0;            //digital port
    OPTION_REG = 0b00001111;    //tmr0 1:1
    
    OPTION_REGbits.INTEDG = 1;  //interrupt on the rising edge
    INTCON = 0b11011000;
    IOCB = 0b10010000;

    
    //SPI init
    SSPCON = 0B100000;    //0B100000=full speed, enabled,clock idle=L
    CKE = 1;    //Data transmitted on rising edge of SCK
    rst = 1;
}

void init_temp( Temperature *obj, char *name ) {
    strcpy( obj->name, name );
    memset( &obj->real_temp, 49, 5);
    memset( &obj->prev_real_temp, 49, 5);
    memset( &obj->set_temp, 49, 5);
    memset( &obj->prev_set_temp, 49, 5);
    obj->real_temp[ 2 ] = obj->set_temp[ 2 ] = 46;
    obj->real_temp[ 4 ] = obj->set_temp[ 4 ] = 123;
}

void init_screen( Screen *screen, Temperature *temperature ) {
    screen->temp = temperature;
    screen->id = 0;
    screen->mode = 0;
}

int main() {
    init_pic();
    LCDinit();
    
    Temperature fst;
    Temperature snd;
    init_temp( &fst, "Pokoj  " );
    init_temp( &snd, "Podlaha" );
        
    Screen first; 
    Screen second;
    init_screen( &first, &fst );
    init_screen( &second, &snd );

    Screen *current_screen = &first;
    
    rectan( 0, 0, 128, 128, BLACK );
    show_screen( &first );
    int screen_id = 0;
    WDTCON = 0b01101;  // Enabling watchdog timer with prescaler
    
    while ( 1 ) { 
        if ( CHANGE == 1 ) {
            current_screen->mode = 0;
            if ( screen_id == 0 ) {
                screen_id = 1;
                current_screen = &second;
            }
            else {
                screen_id = 0;
                current_screen = &first;
            }
            rectan( 0, 0, 128, 128, BLACK );
            CHANGE = 0;  
        } 
        else if ( CHANGE == 2 ) {
            current_screen->mode = 1;
            rectan( 0, 0, 128, 128, BLACK );
            show_screen( current_screen );
            rectan( 0, 0, 128, 128, BLACK );
            current_screen->mode = 0;
            CHANGE = 0;  
        }
        show_screen( current_screen );
        SLEEP();
    }
    
    return 0;
}












  


	
