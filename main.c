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

void init_pic() {
    OSCCON = 0x70;
    TRISC = 0;
    TRISB5 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    ANSEL = 0;            //digital port
    ANSELH = 0;            //digital port
    OPTION_REG = 0b11111000;    //tmr0 1:1
    T1CON = 0;        //timer OFF, 1:1

    //SPI init
    SSPCON = 0B100000;    //0B100000=full speed, enabled,clock idle=L
    CKE = 1;    //Data transmitted on rising edge of SCK
    rst = 1;
}

int main() {
    init_pic();
    LCDinit();
    
    rectan( 0, 0, 128, 128, BLACK );
       
    Temperature fst;
    strcpy( fst.name, "Podlaha" );
    memset( &fst.real_temp, 50, 5);
    memset( &fst.prev_real_temp, 50, 5);
    memset( &fst.set_temp, 51, 5);
    
    Temperature snd;
    strcpy( snd.name, "Pokoj  " );
    memset( &snd.real_temp, 52, 5);
    memset( &snd.set_temp, 53, 5);
    
    fst.real_temp[ 2 ] = fst.set_temp[ 2 ] = 46;
    fst.real_temp[ 4 ] = fst.set_temp[ 4 ] = 123;
    
        
    Screen first;
    first.temp = &fst;
    first.id = 0;
    first.mode = 0;
    
    Screen second;
    second.temp = &snd;
    second.id = 0;
    second.mode = 0;
    

    rectan( 0, 0, 128, 128, BLACK );
    
    while( 1 ) {
        show_screen( &first );
    }
    return 0;
}












  


	
