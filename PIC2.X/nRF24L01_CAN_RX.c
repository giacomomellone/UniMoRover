// PIC18F45K80 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config RETEN = OFF      // VREG Sleep Enable bit (Ultra low-power regulator is Disabled (Controlled by REGSLP bit))
#pragma config INTOSCSEL = HIGH // LF-INTOSC Low-power Enable bit (LF-INTOSC in High-power mode during Sleep)
#pragma config SOSCSEL = DIG   // SOSC Power Selection and mode Configuration bits (High Power SOSC circuit selected)
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
#include <pic18f45k80.h>
#include "uart2.h"
#include "spi.h"
#include "nRF24L01_RX.h"
#include "CAN_library.h"
#include "VNH5019_lib.h"

// Define names for LED pins
#define LED1        LATAbits.LATA3           // Main
#define LED3        LATAbits.LATA2           // IRQ event

#define BUZZER      LATAbits.LATA5            //Buzzer pin

#define GO      ADCON0bits.GO
#define MAX_I   2250                        //0 for 0A, 4096 for 10A 

/***************************************************** 
        Function Prototypes & Variables
**************************************************** */ 

void initPIC(void);

unsigned char spi_transmission_done;
unsigned char data_ACK;
unsigned char MAX_RT;
unsigned char retransmissions;
unsigned char CAN_msg_0;
unsigned char CAN_msg_1; 
char buff_retr[8];
char buff[10];
char FPGA,last_FPGA;
int back_ultrasonic;
int front_ultrasonic;
int GO_STOP;
int REVERSE_STOP;
int duty,error_motor;
int horn_counter;
int counter_error_motor;
unsigned int value,value1,value0;
int ADC; 
int counter_no_data; //Count each time you don't receive a data from PIC1

void interrupt adc(void)     //Interrupt occurs once ADC has converted a value on RA0
{
    if(ADIF == 1)                                                 //interupt for saving adc result
    {
        GIE = 0;
        ADIE = 0;
        
        value = (((unsigned int)ADRESH)<<8)|ADRESL;             //value goes from 0 (0V) to 4095 (5V)
        
        if(ADC == 0)                                            //token mechanisms, driver currents are evaluated alternatively
        {
            value0 = value;
            ADCON0bits.CHS0 = 1;
            ADC = 1;
        }
        else
        {
            value1 = value;
            ADCON0bits.CHS0 = 0;
            ADC = 0;
        }
        
        ADIF = 0;
        ADIE = 1;
        GIE = 1;   
    }
    asm("retfie");
}



/*************************************************
            Initialize the PIC
**************************************************/

void initPIC(){
    // Firstly set to zero all registers
    PORTA = 0x00;            // reset all PORT registers
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    INTCON = 0x00;
    INTCON2 = 0x00;
    INTCON3 = 0x00;
    PIR1 = 0x00;
    RCON = 0x00;
    
    TRISA = 0x00;            // set all PORTA to be OUTPUT
    TRISB = 0x00;            // set all PORTB to be OUTPUT
    TRISC = 0x00;            // set all PORTC to be OUTPUT, INA(RC0) output
    TRISD = 0x00;            // set all PORTD to be OUTPUT
    TRISE = 0x00;            // set all PORTE to be OUTPUT
    
    INTCON3bits.INT2IE = 0;
    INTCON3bits.INT3IE = 0;
    ANCON0 = 0b00000011;
    ANCON1 = 0x00;           //PORTD as digital, RB4 too
    HLVDCON = 0b00000000;
    //Then start setting up
    TRISA = 0b00000011;      //BUZZER is output RA5, ADC signal on input RA0 - RA1
    TRISB = 0b00001001;      //RB3(CANRX) INPUT and RB2(CANTX) OUTPUT, RB1 (INB_2) OUTPUT, RB0 (ENB_2) INPUT
    TRISD = 0b00010001;      //IRQ (RD0) as INPUT and INB(RD5) OUTPUT and ENB (RD4)
    TRISC = 0b00000010;      //RC0 for INA, RC1 for ENA, RC7 for PWM_1, RC6 for PWM_2
    
    TRISE0 = 1;                         //RE0 for ENA_2
    TRISE1 = 0;                         //RE1 for INA_2

    // VARIABLES
    MAX_RT = 1;
    retransmissions = 0;
    back_ultrasonic = 0;
    front_ultrasonic = 0;
    CAN_msg_0 = 0;
    CAN_msg_1 = 0;
    FPGA = 0;
    last_FPGA=0;
    duty = 0;
    value = 0;
    value1 = 0;
    value0 = 0;
    error_motor = 0;
    GO_STOP = 0;
    REVERSE_STOP = 0;
    horn_counter = 0;
    ADC = 0;
    counter_no_data = 0;
    counter_error_motor=0;
    
    BUZZER = 0;
}

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main() {

    //Initialization
    initPIC();
    UART_Init_2(2400);
    init_spi_master();
    CAN_RX_initialize();
    set_dir(stop);                      //direction setting
    set_PWM();                          //PWM initialization
    set_duty(duty);                     //Duty cycle setting
    __delay_ms(10);
    configure_RX();
    __delay_ms(20);
    
    PIR1bits.ADIF = 0;                  
    PIE1bits.ADIE = 1;
    set_AD();                           //ADC initialization
    PEIE = 1;
    GIE = 1;                            //Global Interrupt Enable
    
    T4CONbits.TMR4ON = 1;               //timer 4 is started needed for driver
    
    while(1){ //Receiver Mode
        
        LED1 = !LED1;           // toggle LED1 - program is running
        
        if(GO == 0)   GO = 1;       //it starts ADC if it's not converting any number
        
        if (check_MAX_RT() == 1) {
            reset_MAX_RT(); //I reset MAX_RT interrupt, such as it can retransmit
            flush();
            configure_RX();
            __delay_ms(1);
        }
        
        CAN_msg_0 = CAN_RX_read_0();
        CAN_msg_1 = CAN_RX_read_1();
        
        switch (CAN_msg_0){ //Back flag
            
            case 0x42: //B - Alert but reverse speed still ON
                REVERSE_STOP = 0;
                back_ultrasonic = 1;
                break;
              
            case 0x62: //b - Alert AND motors OFF + Horn
                REVERSE_STOP = 1;
                back_ultrasonic = 1;
                break;
              
            case 0x57: //W - NO Alert
                REVERSE_STOP = 0;
                back_ultrasonic = 0;
                break;

            default: 
                REVERSE_STOP = 0;
                back_ultrasonic = 0;
                      
        }
        
        switch (CAN_msg_1){ //Front flag
            
            case 0x41: //A - Alert but motors still ON
                GO_STOP = 0;
                front_ultrasonic = 1;
                break;
                
            case 0x61: //a - Alert AND motors OFF + Horn
                GO_STOP = 1;
                front_ultrasonic = 1;
                break;
              
            case 0x58: //X - No Alert
                GO_STOP = 0;
                front_ultrasonic = 0;
                break;

            default: 
                GO_STOP = 0;
                front_ultrasonic = 0;
                      
        }
        
        /******************************************************************/
        /********************         MOTOR            ********************/
        /******************************************************************/
        
        //In case of the current values exceed MAX_I (0 = 0 Ampere, 4096 = 10 Ampere)
        //and the diagnosis pins are equal to 1, the motors are stopped and error appears
        
        if((value0<MAX_I)&&(value1<MAX_I)&&(ENA_1==1)&&(ENB_1==1)&&(ENA_2==1)&&(ENB_2==1))   error_motor = 0;            
        else    
            {
            if (counter_error_motor == 2) //Motor error counter (Time redundancy)
                {
                FPGA = 0x53;        //S -> Stop
                error_motor = 1;
                counter_error_motor = 0;
                }
            else counter_error_motor++;
            }  
        
        /******************************************************************/
        /*********************       nRF24L01          ********************/
        /******************************************************************/
        if (IRQ == 0){    //wait for anything   
            
            counter_no_data = 0; //Reset the variable: data has been received
            
            LED3 = 1;
            __delay_ms(10);
            LED3 = 0;
            
            /******************************************************************/
            /********************      ACK_PAYLOAD         ********************/
            /******************************************************************/
            
            if(front_ultrasonic == 0 && back_ultrasonic == 0 && error_motor == 0){
                write_ACK(0x41);    //A
                FPGA = reset_RX(); 
            }else if(front_ultrasonic == 0 && back_ultrasonic == 0 && error_motor == 1){
                write_ACK(0x42);    //B
                FPGA = reset_RX();
            }else if(front_ultrasonic == 0 && back_ultrasonic == 1 && error_motor == 0){
                write_ACK(0x43);    //C
                FPGA = reset_RX();  
            }else if(front_ultrasonic == 0 && back_ultrasonic == 1 && error_motor == 1){
                write_ACK(0x44);    //D
                FPGA = reset_RX();  
            }else if(front_ultrasonic == 1 && back_ultrasonic == 0 && error_motor == 0){
                write_ACK(0x45);    //E
                FPGA = reset_RX();  
            }else if(front_ultrasonic == 1 && back_ultrasonic == 0 && error_motor == 1){
                write_ACK(0x46);    //F
                FPGA = reset_RX();  
            }else if(front_ultrasonic == 1 && back_ultrasonic == 1 && error_motor == 0){
                write_ACK(0x47);    //G
                FPGA = reset_RX();  
            }else if(front_ultrasonic == 1 && back_ultrasonic == 1 && error_motor == 1){
                write_ACK(0x48);    //H
                FPGA = reset_RX();  
            }else{
                write_ACK(0x65);    //e
                FPGA = reset_RX();
            } 
        }else{
            counter_no_data++;
        }
        
        if(counter_no_data > 20){ //This means that non data has been received 
            //from the FPGA for 20 main cycles. Signal lost, the rover has to be 
            //stopped for safety
            FPGA = 0x53;        //S -> Stop
            error_motor = 1;
        }
        
        switch (FPGA) {

            case 0x55: //U -Up
                //GO
                if(GO_STOP == 0){ //Car is allowed to go straight, no obstacles ahead
                    duty = engine(duty,up);
                    last_FPGA = up;
                    BUZZER = 0; //Horn off;
                }else{
                    if(last_FPGA == up)
                    {
                        brake(up);
                        last_FPGA = stop;
                    }
                    set_dir(stop);
                    duty = 0;                               
                    set_duty(duty);
                    BUZZER = 1; //Horn on;
                }
                break;
                
            case 0x44: //D -Down
                //Backward
                if(REVERSE_STOP == 0){ //Car is allowed to go reverse, no obstacles behind
                    duty = engine(duty,down);
                    last_FPGA = down;
                    if(horn_counter < 15) 
                        {
                            horn_counter++;
                        }
                    else{
                            BUZZER = !BUZZER;   //Buzzer at 1Hz
                            horn_counter = 0;
                        }
                }else{
                    if(last_FPGA == down)
                    {
                        brake(down);
                        last_FPGA = stop;
                    }
                    set_dir(stop);
                    duty = 0;                               
                    set_duty(duty);
                    BUZZER = 1; //Horn on;
                }
                break;
               
            case 0x4C: //L - Left
                //Left
                duty = engine_left(duty,left);
                break;
             
            case 0x52: //R - Right
                //Right
                duty = engine_right(duty,right);
                break;
             
            case 0x48: //H - Horn
                BUZZER = 1; //Horn on;
                break;
                
            case 0x68: //h - Up+Horn
                if(GO_STOP == 0){ //Car is allowed to go straight, no obstacles ahead
                    duty = engine(duty,up);
                    last_FPGA = up_horn;
                }else{
                    if(last_FPGA == up_horn)
                    {
                        brake(up);
                        last_FPGA=stop;
                    }
                    set_dir(stop);
                    duty = 0;                               
                    set_duty(duty);
                }
                BUZZER = 1; //Horn on;
                break;
                
            case 0x53: //S
                //STOP
                if((last_FPGA == up)||(last_FPGA == up_horn))
                    {
                        //brake(up);
                        last_FPGA = stop;
                    }
                else if(last_FPGA == down)
                    {
                        //brake(down);
                        last_FPGA = stop;
                    }
                BUZZER = 0; //Buzzer off;
                last_FPGA = stop;
                set_dir(stop);
                duty = 0;                               
                set_duty(duty);
                break;

            default:
                //STOP
                BUZZER = 0; //Buzzer off;
                set_dir(stop);
                duty = 0;                               
                set_duty(duty);
        }
        
        __delay_ms(20);
    }
}

