//pin assignment for the direction of the engine
#define INA_1   LATCbits.LATC0                  
#define INB_1   LATDbits.LATD5
#define INA_2   LATEbits.LATE1                
#define INB_2   LATBbits.LATB1

//pin assignment for diagnosis
#define ENA_1   PORTCbits.RC1
#define ENB_1   PORTDbits.RD4
#define ENA_2   PORTEbits.RE0
#define ENB_2   PORTBbits.RB0

//maximum allowed duty cycle 
#define MAX_duty_up         15
#define MAX_duty_down       15
#define MAX_duty_left       40
#define MAX_duty_right      40
#define duty_stop           10

//duty cycle increment
#define increment 5

//allowed state
#define stop    'S'
#define up      'U'
#define down    'D'
#define right   'R'
#define left    'L'
#define up_horn 'h'


int dec_to_bin(int n)                           //decimal to binary conversion
{
    int i, bin = 0, pos = 0, power = 1;
    int A[10] = {0,0,0,0,0,0,0,0,0,0};
    
    while(pos < 10)                               //convert the decimal number to an array of binary digits
        {
            if(n > 0)
                {
                    A[pos] = n%2;
                    n = n/2;
                }
            else A[pos]=0;
        
            pos++;
        }
    
    for (i=0; i<10; i++)                        //converts the binary array to a binary number
        {
            bin += A[i]*power;
            power *= 2;
        }
    
    return bin;
}


void set_duty(int D)                            //set the duty cycle on CCPR1L
{
    int d;
    
    d = dec_to_bin(D*10);                       //multiplied by 10 for correctly select CCPR1L value
    CCPR4L = d >> 2;                            //MSB of d
    CCPR3L = d >> 2;
}

void set_duty_left(int D)                       //set the duty cycle on CCP4 (driver 1,left)
{
    int d;
    
    d = dec_to_bin(D*10);                       //multiplied by 10 for correctly select CCPR1L value
    CCPR4L = d >> 2;                            //MSB of d
}

void set_duty_right(int D)                      //set the duty cycle on CCP3 (driver 2, right)
{
    int d;
    
    d = dec_to_bin(D*10);                       //multiplied by 10 for correctly select CCPR1L value
    CCPR3L = d >> 2;                            //MSB of d
}

void set_PWM()                                  //inizialization of the PWM operation for the CCP modules
{
    PR4 = 249;                                  //set f=500Hz with TMR4 prescaler at 16
    
    T4CON = 0b00000011;                         //configure TMR4 prescaler to 16 and postscaler to 1
    CCPTMRSbits.C4TSEL = 1;                     //set Timer 4 for CCP4
    CCPTMRSbits.C3TSEL = 1;                     //set Timer 4 for CCP3
    CCP4CON = 0b00001100;                       //set PWM mode and LSB of D for Driver 1
    CCP3CON = 0b00001100;                       //set PWM mode and LSB of D for Driver 2
    
    TMR4 = 0;                                   //inizialize Timer 4 value
}


void set_dir(char dir)                          //direction settings
{
    switch(dir) {
            case up:    INA_1 = 1;
                        INA_2 = 1;
                        INB_1 = 0;
                        INB_2 = 0;
                        break;
            
            case down:  INA_1 = 0;
                        INA_2 = 0;
                        INB_1 = 1;
                        INB_2 = 1;
                        break;
                        
            case left:  INA_1 = 0;
                        INA_2 = 1;
                        INB_1 = 1;
                        INB_2 = 0;
                        break;
                        
            case right: INA_1 = 1;
                        INA_2 = 0;
                        INB_1 = 0;
                        INB_2 = 1;
                        break;
                        
            case stop:  INA_1 = 0;
                        INA_2 = 0;
                        INB_1 = 0;
                        INB_2 = 0;
                        break;
                        
            default:    INA_1 = 0;
                        INA_2 = 0;
                        INB_1 = 0;
                        INB_2 = 0;
                        break; 
    }
}


int engine(int D,char dir)                      //engine function
{
    int next_duty,MAX;
    
    set_dir(dir); 
    
    if(dir == 'U') MAX = MAX_duty_up;          //duty in reverse direction is limited to reduce the maximum speed
    else if(dir == 'D') MAX = MAX_duty_down;
    
    if(D <= MAX)         
        {
            set_duty(D);
            next_duty = D+increment;                              
            __delay_ms(100);                            
        }
    return next_duty;
}

int engine_left(int D,char dir)                 //engine function for left driver (driver 1))
{
    int next_duty;
    
    set_dir(dir); 
    
    if(D <= MAX_duty_left)         
        {
            set_duty(D);
            next_duty = D+increment;                              
            __delay_ms(100);                            
        }
    return next_duty;
}

int engine_right(int D,char dir)                //engine function for right driver (driver2 )
{
    int next_duty;
    
    set_dir(dir); 

    if(D <= MAX_duty_right)         
        {
            set_duty(D);
            next_duty = D+increment;                              
            __delay_ms(100);                            
        }
    return next_duty;
}

void brake(char last_dir)
{
    int duty;
    char dir;
    
    if(last_dir == up) dir = down;
    else if(last_dir == down) dir = up;
    
    set_dir(dir);
    duty = duty_stop;                               
    set_duty(duty);
    __delay_ms(30);
}



void set_AD()
{
    ADCON0 = 0b00000000;        //ADC is setted but disabled
    ADCON1 = 0x00;              //ADC uses Vdd and GND as reference voltages
    ADCON2bits.ADFM = 1;        //Result is right justified
    ANCON0bits.ANSEL0 = 1;
    ADCON0bits.ADON = 1;        //ADC is enabled
}