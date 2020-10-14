#pragma config FOSC = EXTRCIO  // Oscillator Selection bits (RC oscillator: CLKOUT function on RA4/OSC2/CLKOUT pin, RC on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include "ds18b20.h"
#include "st7735.h"

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0  
#define WHITE   0xFFFF

uint16_t raw_temp;
unsigned char temp[6] = { 0, 0, 0, 0, 0, 0 };
unsigned char prev_temp[6] = { 0, 0, 0, 0, 0, 0 };

void init_pic() {
    OSCCON = 0x70;
    TRISC = 0;
	TRISB5 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
	ANSEL = 0;			//digital port
    ANSELH = 0;			//digital port
    OPTION_REG = 0b11111000;	//tmr0 1:1
	T1CON=0;		//timer OFF, 1:1
      	
	//SPI init
	SSPCON = 0B100000;	//0B100000=full speed, enabled,clock idle=L   
	CKE=1;	//Data transmitted on rising edge of SCK
	rst=1;
}

void read_temperature() {
    if(ds18b20_read(&raw_temp))
    {
        if(raw_temp & 0x8000)  // if the temperature is negative
        {
          temp[0] = 45;             // put minus sign (-)
          raw_temp = (~raw_temp) + 1;  // change temperature value to positive form
        }

        else
        {
          if((raw_temp >> 4) >= 100)  // if the temperature >= 100 °C
            temp[0] = 17;            // put 1 of hundreds
          else                        // otherwise
            temp[0] = 0;            // put space ' '
        }

        temp[1] = ( ( (raw_temp >> 4) / 10 ) % 10 ) + 48;  // put tens digit
        temp[2] = ( (raw_temp >> 4) % 10 ) + 48;  // put ones digit
        temp[3] = 46;
        temp[4] = ( ( (raw_temp & 0x0F) * 625) / 1000 ) + 48; // put thousands digit
        temp[5] = 123;
    }
    else {
        temp[0] = 10;
    }
}
 
int main()
{
    init_pic();
	LCDinit();
    
    rectan(0,0,128,128, BLACK);
    
    while(1) {
        for (int i = 0; i < 6; ++i) {
            if ( temp[i] != prev_temp[i] ) {
                draw( 0 + (i * 18), 64, prev_temp[i], BLACK, 2 );
                draw( 0 + (i * 18), 64, temp[i], RED, 2 );
            }   
        }
        __delay_ms( 3000 );
 
        for (int i = 0; i < 6; ++i ) 
            prev_temp[i] = temp[i];
      
        read_temperature();
    }
    return 0;
}












  


	
