#define SDO         TRISCbits.TRISC5        // Serial Data Out (SDO)    -- Pin that data goes out from
#define SDI         TRISCbits.TRISC4        // Serial Data In (SDI)        -- Pin that data comes in to
#define SCK         TRISCbits.TRISC3        // Serial Clock (SCK)        -- Pin that sends clock signal to sync all  SPI device

// Define names for SPI configuration pins
#define SMP         SSPSTATbits.SMP         // Sample Bit (SMP)            -- Pin that sets where to sample data
#define CKE         SSPSTATbits.CKE         // Clock Edge Select (CKE)    -- Pin that sets which transition transmission takes place
#define CKP         SSPCON1bits.CKP         // Clock Polarity (CKP)        -- Pin that sets where SCK will idle
#define SSPEN       SSPCON1bits.SSPEN       // Serial Prt Enbl (SSPEN)    -- Pin that will enable serial port and configure SCK, SDO, SDI and SS as serial port pins

/*************************************************
            Initialize the SPI Master
**************************************************/

void init_spi_master() {
    
    PIE1bits.SSPIE = 0;
    SSPEN = 0;          //1 = Enables serial port and configures SCK, SDO, SDI and SS as serial port pins
                        //0 = Disables serial port and configures these pins as I/O port pins
    
    SDI = 1;    // Serial Data In             - enable master mode
    SCK = 0;    // Serial Clock                - clear TRISB1 for master
    SDO = 0;    // Serial Data Out             - clear TRISC7
    

    SMP = 0;    // Sample bit                 1 = Input data sampled at end of data output time
                                            //0 = Input data sampled at middle of data output time
    CKE = 1;    // Clock Edge Select          1 = Transmit occurs on transition from active to Idle clock state
                                            //0 = Transmit occurs on transition from Idle to active clock state
    CKP = 0;    // Clock Polarity             1 = Idle state for clock is a high level
                                            //0 = Idle state for clock is a low level
    
    SSPCON1bits.SSPM3 = 0;    // Set the clock rate in master mode
    SSPCON1bits.SSPM2 = 0;    // to be FOSC/64 (Frequency of Oscillation)
    SSPCON1bits.SSPM1 = 1;
    SSPCON1bits.SSPM0 = 0;
    
    SSPEN = 1;  
    
}

/*************************************************
            Functions for Writing Data
**************************************************/

unsigned char spi_write(unsigned char data) {
    SSPSTATbits.BF = 0;
    SSPBUF = data;
    while(SSPSTATbits.BF == 0){}
    return SSPBUF;  
}