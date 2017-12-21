// Define names for SPI connection pins
#define CE          LATDbits.LATD2           // Chip Enable (CE)            -- Pin that activates RX or TX mode
#define IRQ         PORTDbits.RD0           // Interrupt Request (IRQ)    -- Pin that signals transmission
#define CSN         LATDbits.LATD3          // CSN

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
          Initialize the Nordic for RX
**************************************************/

void configure_RX(void){

    unsigned char i, j;

    CE = 0;
    __delay_ms(100);
    
    //Every new command must be started by a high to low transition on CSN
    
    CSN = 1;
    __delay_ms(5);
    
    
    CSN = 0;
    spi_write(W_REGISTER+CONFIG);     // Write to the CONFIG register
    spi_write(0b00011001);            // [7] Reserved - 0
                                      // [6] RX_DR Interrupt 0 - unmask / 1 - mask
                                      // [5] TX_DS Interrupt 0 - unmask
                                      // [4] MAX_RT Interrupt 0 - unmask
                                      // [3] Enable CRC - 1
                                      // [2] 1 byte CRC - 0; 2 byte CRC - 1
                                      // [1] PWR_UP:1, PWR_DOWN:0
                                      // [0] 1: PRX, 0: PTX
    CSN = 1;
    
	CSN = 0;
	//disable auto-ack for all channels      
	spi_write(W_REGISTER+EN_AA);
	spi_write(0x01);    //ACK enabled on PIPE0
	CSN = 1; 
    
	CSN = 0;
	//address width = 5 bytes  
  	spi_write(W_REGISTER+SETUP_AW);
	spi_write(0x03);    
    CSN = 1;  
    
    CSN = 0;
    spi_write(W_REGISTER+SETUP_RETR);
    spi_write(0x3F); // Wait 1ms and then up to 15 Re-Transmit
    CSN = 1;
    
    CSN = 0;
	//data rate = 1MB   
  	spi_write(W_REGISTER+RF_SETUP);
	spi_write(0x07);    
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
    //set channel 110 => 2510MHz 
   	spi_write(W_REGISTER+RF_CH);
	spi_write(0x6E);    
    CSN = 1;
    
    CSN = 0;
    //set address E7E7E7E7E7
    spi_write(W_REGISTER+TX_ADDR);
    for (j = 0; j < 5; j++)
 		spi_write(0xE7); 
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
    
    CSN = 0;
    spi_write(W_REGISTER+CONFIG);     // Write to the CONFIG register
    spi_write(0b00011011);            // [7] Reserved - 0
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
    
    CE = 1;
}

void write_ACK(unsigned char data){

    // I flush all packets pending in TX FIFO
    CSN = 0;    
 	spi_write(FLUSH_TX);    
    CSN = 1;
    
    CSN = 0;    
 	spi_write(W_ACK_PAYLOAD); 
    spi_write(data);
    CSN = 1;

}
unsigned char reset_RX(void){
    
    unsigned char buffer_RX;    
    
	//Read RX payload   
    CSN = 0;    
   	spi_write(R_RX_PAYLOAD);     
    buffer_RX = spi_write(0);
    CSN = 1;    
    
	//Flush RX FIFO    
    CSN = 0;    
 	spi_write(FLUSH_RX);    
    CSN = 1;
    
    CSN = 0;
	//reset int Data Ready RX FIFO interrupt
    //Now I have to reset also TX_DS IRQ, because when I receive a new packet it
    //means that the ACK with payload has been correctly sent
  	spi_write(W_REGISTER+STATUS);
	spi_write(0x60);    //Previosly 0x60, reset the TX_DS interrupt and RX_DR
    CSN = 1;
    
    return buffer_RX;
    
}

unsigned char check_MAX_RT(void){
    
    unsigned char buffer = 0;
    unsigned char MAX_RT = 0;
    
    CSN = 0;    
   	buffer = spi_write(NOP);     
    CSN = 1;
    
    MAX_RT = buffer & 0x10; //Only MAX_RT is unmasked
    
    MAX_RT = MAX_RT >> 4; // I shift by 4 positions
    
    return MAX_RT;

}

unsigned char count_retr(void){
    
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