// PIC18F25K80 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = HIGH   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
#pragma config XINST = OFF       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config FOSC = HS1       // Oscillator (HS oscillator (Medium power, 4 MHz - 16 MHz))
#pragma config PLLCFG = OFF     // PLL x4 Enable bit (Disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor (Disabled)
#pragma config IESO = OFF       // Internal External Oscillator Switch Over Mode (Disabled)

// CONFIG2L
#pragma config PWRTEN = OFF     // Power Up Timer (Disabled)
#pragma config BOREN = SBORDIS  // Brown Out Detect (Enabled in hardware, SBOREN disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (1.8V)
#pragma config BORPWR = ZPBORMV // BORMV Power level (ZPBORMV instead of BORMV is selected)

// CONFIG2H
#pragma config WDTEN = SWDTDIS  // Watchdog Timer (WDT enabled in hardware; SWDTEN bit disabled)
#pragma config WDTPS = 1048576  // Watchdog Postscaler (1:1048576)

// CONFIG3H
#pragma config CANMX = PORTB    // ECAN Mux bit (ECAN TX and RX pins are located on RB2 and RB3, respectively)
#pragma config MSSPMSK = MSK7   // MSSP address masking (7 Bit address masking mode)
#pragma config MCLRE = ON       // Master Clear Enable (MCLR Enabled, RE3 Disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Overflow Reset (Enabled)
#pragma config BBSIZ = BB2K     // Boot Block Size (2K word Boot Block size)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protect 00800-01FFF (Disabled)
#pragma config CP1 = OFF        // Code Protect 02000-03FFF (Disabled)
#pragma config CP2 = OFF        // Code Protect 04000-05FFF (Disabled)
#pragma config CP3 = OFF        // Code Protect 06000-07FFF (Disabled)

// CONFIG5H
#pragma config CPB = OFF        // Code Protect Boot (Disabled)
#pragma config CPD = OFF        // Data EE Read Protect (Disabled)

// CONFIG6L
#pragma config WRT0 = OFF       // Table Write Protect 00800-01FFF (Disabled)
#pragma config WRT1 = OFF       // Table Write Protect 02000-03FFF (Disabled)
#pragma config WRT2 = OFF       // Table Write Protect 04000-05FFF (Disabled)
#pragma config WRT3 = OFF       // Table Write Protect 06000-07FFF (Disabled)

// CONFIG6H
#pragma config WRTC = OFF       // Config. Write Protect (Disabled)
#pragma config WRTB = OFF       // Table Write Protect Boot (Disabled)
#pragma config WRTD = OFF       // Data EE Write Protect (Disabled)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protect 00800-01FFF (Disabled)
#pragma config EBTR1 = OFF      // Table Read Protect 02000-03FFF (Disabled)
#pragma config EBTR2 = OFF      // Table Read Protect 04000-05FFF (Disabled)
#pragma config EBTR3 = OFF      // Table Read Protect 06000-07FFF (Disabled)

// CONFIG7H
#pragma config EBTRB = OFF      // Table Read Protect Boot (Disabled)

/***************************************************** 
                      CHANGELOG
******************************************************
******************************************************/

// Include files
#define _XTAL_FREQ  8000000
#include <stdio.h>
#include <p18f4580.h>                       
#include <stdlib.h>
#include <xc.h>
#include "uart1.h"
#include "hc_sr04.h"
#include "CAN_library.h"

#define LED1        LATAbits.LATA0           // yellow blinky light (code is running) pin 2
#define LED2        LATAbits.LATA1           // RED light indicating CAN error

char buff_retr[8];
unsigned int dist1;
unsigned int dist2;
char buff[10];
int token;
int treshold1;
int treshold2;
int cnt_B;
int cnt_b;
int cnt_W;
unsigned char message;

void interrupt echo(void) //Interrupt occurs once echo arrives, exploiting the
//Interrupt on Change of PORTB
{
  if(INTCONbits.RBIF == 1)                       //Makes sure that it is PORTB On-Change Interrupt                                      //Interrupt
  {
    INTCONbits.RBIE = 0;                         //Disable On-Change Interrupt
    
    switch(token){
        case 0: if(ECHO1 == 1)                      //As soon as ECHO is HIGH then
                    {   T1CONbits.TMR1ON = 1;                       //Start Timer
                    }
                if(ECHO1 == 0){                     //If ECHO is LOW
                        T1CONbits.TMR1ON = 0;                     //Stop Timer
                        //a = 0b10100010;
                        dist1 = (TMR1L | (TMR1H<<8))/58.82; //Calculate Distance
                        // This is a bitwise "or" and a 8 bit shifting of
                        // TMR1H towards left
                        // | is "or"
                        token=1;
                    }
                break;
        
        case 1: if(ECHO2 == 1)                      //As soon as ECHO is HIGH then
                    {   T1CONbits.TMR1ON = 1;                       //Start Timer
                    }
                if(ECHO2 == 0){                     //If ECHO is LOW
                        T1CONbits.TMR1ON = 0;                     //Stop Timer
                        //a = 0b10100010;
                        dist2 = (TMR1L | (TMR1H<<8))/58.82; //Calculate Distance
                        // This is a bitwise "or" and a 8 bit shifting of
                        // TMR1H towards left
                        // | is "or"
                        token=0;
                    }
                break;
        default:break;
        }
    }

  INTCONbits.RBIF = 0;                           //Clear PORTB On-Change Interrupt flag
  INTCONbits.RBIE = 1;                           //Enable PORTB On-Change Interrupt
}


/*************************************************
            Initialize the PIC
**************************************************/

void initPIC(){
    // Firstly set to zero all registers
    PORTA = 0x00;            // reset all PORT registers
    PORTB = 0x00;
    PORTC = 0x00;
    INTCON3 = 0x00;
    INTCON2 = 0x00;
    INTCON = 0x00;
    PIR1 = 0x00;
    RCON = 0x00;
    
    TRISA = 0x00;            // set all PORTA to be OUTPUT
    TRISB = 0x00;            // set all PORTB to be OUTPUT
    TRISC = 0x00;            // set all PORTC to be OUTPUT
    
    //Then start setting up
    
    TRISB = 0b00111000;      //RB4 and RB5 as Input PIN (ECHO)
                             //RB0 and RB1 as Output pin (Trigger))
                             //RB3(CANRX) INPUT and RB2(CANTX) OUTPUT
    
    INTCONbits.RBIF = 0;     //Clear PORTB On-Change Interrupt Flag
    INTCONbits.RBIE = 1;     //Enable PORTB On-Change Interrupt
    INTCON2bits.RBIP = 1;    //RB Port Change Interrupt Priority bit, high priority
    IOCB = 0b00110000;       //Enable only RB4 and RB5 as On-Change Interrupt
                             //if 1 = High priority
    ANCON1bits.ANSEL9 = 0;  //RB4 set as digital
    //Initialize Timer Module
    // T1CON = 0b00010000, prescaler value is 10=>1:4 prescale value
    T1CON = 0x10; 
  
    token = 0;                            //Initialize semaphore variable
    treshold1 = 100;
    treshold2 = 75;
    cnt_B = 0;
    cnt_b = 0;
    message = 0x57; //W

    INTCONbits.GIE = 1;           // enables all interrupts
    RCONbits.IPEN = 1;             // enable priorities levels on interrupts
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main() {

    //Initialization
    initPIC();
    //UART_Init(9600);
    CAN_TX_initialize();
    __delay_ms(10);
    
    TMR1H = 0;                          //Sets the Initial Value of Timer
    TMR1L = 0;                          //Sets the Initial Value of Timer
    
    while(1){ //Receiver Mode
        
        LED1 = !LED1;           // toggle LED1 - program is running
        
        TMR1H = 0;                          //Sets the Initial Value of Timer
        TMR1L = 0;                          //Sets the Initial Value of Timer
      

        if(token==0){                       //First sensor  
            IOCB = 0b00010000;              //Enable only RB4 On-Change Interrupt
            TRIG1 = 1;                      //TRIGGER HIGH
            __delay_us(10);                 //10uS Delay
            TRIG1 = 0;                      //TRIGGER LOW 
        }else if(token==1){                 //Second sensor
            IOCB = 0b00100000;              //Enable only RB5 On-Change Interrupt
            TRIG2 = 1;
            __delay_us(10); 
            TRIG2 = 0;
        }
        
        __delay_ms(50);
        
        if((dist1 > 2) && (dist2 > 2)){
            //treshold2 < treshold1
            //"The elseif statement is only executed if the preceding if 
            //expression and any preceding elseif expressions evaluated to FALSE 
            //and the current elseif expression evaluated to TRUE"
                if(dist1 < treshold2 || dist2 < treshold2){
                    if(cnt_b == 1){
                        message = 0x62;         //b
                        cnt_b = 0;
                    }else{
                        cnt_B = 0;
                        cnt_b++;
                    }
                }else if(dist1 < treshold1 || dist2 < treshold1){
                    //Enters here only if the distance is
                    //treshold2 < distance < treshold1
                    if(cnt_B == 2){ //Smaller counter, faster response
                        message = 0x42;         //B
                        cnt_B = 0;
                    }else{
                        cnt_B++;
                        cnt_b = 0;
                    }
                }else{
                        message = 0x57;         //W
                }
        }              
        CAN_TX_write_0(message);
    }
}

