// Define names for SPI connection pins
#define CE          LATAbits.LATA3          // Chip Enable (CE)            -- Pin that activates RX or TX mode
#define IRQ         PORTBbits.RB2           // Interrupt Request (IRQ)    -- Pin that signals transmission
#define CSN         LATCbits.LATC2          // CSN

// Define commands for Nordic via SPI
#define R_REGISTER      0x00
#define W_REGISTER      0x20
#define R_RX_PAYLOAD    0x61
#define W_TX_PAYLOAD    0xA0
#define FLUSH_TX        0xE1
#define FLUSH_RX        0xE2
#define ACTIVATE        0x50
#define W_ACK_PAYLOAD   0xA8
#define R_RX_PL_WID     0x60
#define REUSE_TX_PL     0xE3
#define NOP             0xFF

// Define Nordic registers
#define CONFIG          0x00
#define EN_AA           0x01
#define EN_RXADDR       0x02
#define SETUP_AW        0x03
#define SETUP_RETR      0x04
#define RF_CH           0x05
#define RF_SETUP        0x06
#define STATUS          0x07
#define OBSERVE_TX      0x08
#define CD              0x09
#define RX_ADDR_P0      0x0A
#define RX_ADDR_P1      0x0B
#define RX_ADDR_P2      0x0C
#define RX_ADDR_P3      0x0D
#define RX_ADDR_P4      0x0E
#define RX_ADDR_P5      0x0F
#define TX_ADDR         0x10
#define RX_PW_P0        0x11
#define RX_PW_P1        0x12
#define RX_PW_P2        0x13
#define RX_PW_P3        0x14
#define RX_PW_P4        0x15
#define RX_PW_P5        0x16
#define FIFO_STATUS     0x17
#define DYNPD           0x1C
#define FEATURE         0x1D

/*************************************************
          Initialize the Nordic for TX
**************************************************/

void configure_TX() {
    //nRF24L01 must be in one of the standby modes or in power down mode
    //before writing to the configuration registers
    unsigned char j;
    
    CE = 0;
    __delay_ms(100);
    
    //Every new command must be started by a high to low transition on CSN
    
    CSN = 1;
    __delay_ms(5);
    
    CSN = 0;
    spi_write(W_REGISTER+CONFIG);     // Write to the CONFIG register
    spi_write(0b00011000);            // [7] Reserved - 0
                                      // [6] RX_DR Interrupt 0 - unmask / 1 - mask
                                      // [5] TX_DS Interrupt 0 - unmask
                                      // [4] MAX_RT Interrupt 0 - unmask
                                      // [3] Enable CRC - 1
                                      // [2] 1 byte CRC - 0
                                      // [1] PWR_UP:1, PWR_DOWN:0
                                      // [0] 1: PRX, 0: PTX
    CSN = 1;
    
    
    CSN = 0;
    //disable auto-ack, RX mode
    spi_write(W_REGISTER+EN_AA);
    spi_write(0x01); //ACK enabled on PIPE0
    CSN = 1;
    
    
    CSN = 0;
    spi_write(W_REGISTER+SETUP_AW);   // Write to the SETUP_AW register
    spi_write(0b00000011);            // Set the width to 5 bytes
    CSN = 1;
    
    
    CSN = 0;
    spi_write(W_REGISTER+SETUP_RETR);
    spi_write(0x3F); // Wait 1ms and then up to 15 Re-Transmit
    CSN = 1;
    
    
    CSN = 0;
    spi_write(W_REGISTER+RF_CH);
    spi_write(0x6E);            //set RF channel 110 => 2510MHz
    CSN = 1;
   
    
    CSN = 0;
    //data rate = 1MB
    spi_write(W_REGISTER+RF_SETUP);
    spi_write(0b00000111);            //set RF setup 
    CSN = 1;
   
    CSN = 0;
	//ACTIVATE   
  	spi_write(ACTIVATE);
	spi_write(0x73);    
    CSN = 1;
    
    CSN = 0;   
  	spi_write(W_REGISTER+FEATURE);
	spi_write(0x06); //Enable  Enables Dynamic Payload Length (bit 2)
    // and Enables Payload with ACK (bit 1))
    CSN = 1;
    
    CSN = 0;
  	spi_write(W_REGISTER+DYNPD);
	spi_write(0x01);    //Enable dyn. payload length data pipe 0
    CSN = 1;
    
    CSN = 0;
    //set address E7E7E7E7E7, default
   	spi_write(W_REGISTER+TX_ADDR);   
    for (j = 0; j < 5; j++)
    {
        spi_write(0xE7);
    }
    CSN = 1;
    
    CSN = 0;
    //set address E7E7E7E7E7
    spi_write(W_REGISTER+RX_ADDR_P0);
    for (j = 0; j < 5; j++)
 		spi_write(0xE7); 
    CSN = 1;
    
    CSN = 0;
    spi_write(FLUSH_RX);
    CSN = 1;
    
    CSN = 0;
    spi_write(FLUSH_TX);
    CSN = 1;
     
    //W_REGISTER is executable in power down or standby modes only
    //When you send any command byte, the nRF24L01 always returns to you the STATUS register.
    
}

void TX_nordic(unsigned char data) {
    
    CSN = 0;
    spi_write(W_REGISTER+STATUS);     // Reset the TX_DS interrupt and RX_DR
    spi_write(0x60); //Previously 0x20 (only TX_DS)
    CSN = 1;
    
	CSN = 0;
    spi_write(W_REGISTER+CONFIG);     // Write to the CONFIG register
    spi_write(0b00011010);            // [7] Reserved - 0
                                      // [6] RX_DR Interrupt 0 - unmask / 1 - mask
                                      // [5] TX_DS Interrupt 0 - unmask
                                      // [4] MAX_RT Interrupt 0 - unmask
                                      // [3] Enable CRC - 1
                                      // [2] 1 byte CRC - 0; 2 byte CRC - 1
                                      // [1] PWR_UP:1, PWR_DOWN:0
                                      // [0] 1: PRX, 0: PTX
    CSN = 1;
    
    // After the power up you have to wait at least 5ms
    __delay_ms(5);
    
    //clear TX fifo
    //the data sheet says that this is supposed to come up 0 after POR, but that doesn't seem to be the case
    CSN = 0;
   	spi_write(FLUSH_TX);
    CSN = 1;
    
    CSN = 0; 
    //With the following command the TX FIFO won't be empty, I'm gonna write
    spi_write(W_TX_PAYLOAD);    // send command for transmission
    spi_write(data);            // load data
    CSN = 1;
    
    //Pulse CE to start transmission
    // toggle CE for >10us to send packet
    
    CE = 1;
    __delay_ms(1);     
    CE = 0;
    
    
}

unsigned char read_ACK_payload(void){
    
    unsigned char ACK_payload;
    __delay_ms(1);
    
    CSN = 0;    
   	spi_write(R_RX_PAYLOAD);     
    ACK_payload = spi_write(0);
    CSN = 1;
    
    //Flush RX FIFO    
    CSN = 0;    
 	spi_write(FLUSH_RX);    
    CSN = 1;

    return ACK_payload;
}

unsigned char check_MAX_RT(void){
    //This checks wheter the maximum number of retrasmission has been reached
    
    unsigned char buffer = 0;
    unsigned char MAX_RT = 0;
    
    CSN = 0;    
   	buffer = spi_write(NOP);     
    CSN = 1;
    
    MAX_RT = buffer & 0x10; //Only MAX_RT is unmasked
    
    MAX_RT = MAX_RT >> 4; // I shift by 4 positions
    
    return MAX_RT;

}

unsigned char count_retr(void){ //This function counts the number of retransmission occurred
    
    unsigned char buffer = 0;
    unsigned char retr = 0;
    
    CSN = 0;    
   	spi_write(R_REGISTER+OBSERVE_TX);  
    buffer = spi_write(NOP);
    CSN = 1;
    
    retr = buffer & 0x0F;
    
    return retr;

}

void reset_MAX_RT(void){

    CSN = 0;
    spi_write(W_REGISTER+STATUS);     // Reset the MAX_RT
    spi_write(0x10); 
    CSN = 1;

}

void flush(void){

    CSN = 0;
   	spi_write(FLUSH_TX);
    CSN = 1;
    
    CSN = 0;
   	spi_write(FLUSH_RX);
    CSN = 1;
    
}