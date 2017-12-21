// PIC18LF25K80 Configuration Bit Settings

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
        Includes
******************************************************/

// Include files
#define _XTAL_FREQ  8000000
#include <stdio.h>
#include <p18f4580.h>                       
#include <stdlib.h>
#include <xc.h>
#include "uart1.h"
#include "spi.h"
#include "nRF24L01_TX.h"

// Define names for LED pins
#define LED1        LATAbits.LATA0           // yellow blinky light (code is running) pin 2
#define LED2        LATAbits.LATA1           // blue blinky light (spi tx done) pin3

/***************************************************** 
        Function Prototypes & Variables
**************************************************** */ 

void initPIC(void);

unsigned char MAX_RT;
//unsigned char spi_transmission_done;
char buff[8];
char serial_read;
char alert_status;
char FPGA;
char PIC_ft232;

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
    
    INTCON3bits.INT2IE = 0;
    INTCON3bits.INT3IE = 0;
    
    ANCON0 = 0x00;
    ANCON1 = 0x00;           //PORTD as digital, RB4 too
    
    
    //Then start setting up something
    TRISB = 0b00111100;      // set as INPUT, and BUT1 / BUT2 / BUT3 / BUT4
                             // and the rest of PORTB as OUTPUT
    
    INTCON2bits.RBPU = 0;          // All PORTB pull-ups are enabled
    WPUB = 0b00111100;          
    
    //spi_transmission_done = 0; // initialize variables
    MAX_RT = 0;
    serial_read = 0;
    alert_status = 0;
    FPGA = 0;
    PIC_ft232 = 0;
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main() {
    
    //Initialization
    __delay_ms(1000);
    initPIC();
    UART_Init(9600);
    init_spi_master();
    __delay_ms(5);
    configure_TX();
    __delay_ms(20);
    /*UART_Write_Text("  UART1 initialized, TX configured");
    UART_Write_Text("\t");*/
    
    while (1){ //Transmission Mode
        
        LED1 = !LED1;           // toggle LED1 - program is running
        __delay_ms(10);    
        
        if (check_MAX_RT() == 1) { //If MAX_RT == 1 then I reached max number of retransmissions
            flush();
            reset_MAX_RT(); //I reset MAX_RT interrupt, such as it can retransmit
            flush();
            __delay_ms(5);
        }
        
        if(OVERRUN == 1){  //If UART RX gives OERR (Overrun) error, this reset it
            RCSTA1bits.CREN = 0;
            __delay_ms(1);
            RCSTA1bits.CREN = 1;
        }
        
        if (UART_Data_Ready() == 1){ //Data ready from FPGA
            FPGA = UART_Read(); //Read FPGA command data
            LED2 = !LED2;           // toggle LED2 - Data ready from FPGA
            TX_nordic(FPGA);
            __delay_ms(5);      //Wait for the ACK
            alert_status = read_ACK_payload();  //Read ACK with alert status
            UART_Write(alert_status);   //Send alert status to FPGA
        }

    }
}

