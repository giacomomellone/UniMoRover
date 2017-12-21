// CAN Library for PIC #3bis. 
// This PIC is used to send data via CAN to PIC #2 which receives data and establishes the presence of an obstacle in the back of the vehicle.
// The Identifier of the message is 5, which corresponds to the message containing the data of the rear ultrasonic sensors.
// PIC #3bis doesn't receive messages from CAN Bus.

#define LED2        LATAbits.LATA1                  // RED light indicating CAN error

typedef unsigned char BYTE;

// Structure of a CAN Message
typedef struct{             
	unsigned long identifier;                       // Message Identifier
	BYTE data;                                      // Data of the message
	BYTE type;                                      // Type of the data. 1 = IDE	0 = standard
	BYTE length;                                    // Data length
	BYTE RTR;                                       // Remote flag. RTR = 1 means remote frame

} CANmessage;


// Initialization of the CAN Protocol for the message transmission
void CAN_TX_initialize(void){

    //Configuration mode
    
    CANCON = 0b10000000;                            // Configuration mode
    CANSTATbits.OPMODE2 = 0x01;                     // Setting of CANSTAT in Configuration mode
    CANSTATbits.OPMODE1 = 0x00;
    CANSTATbits.OPMODE0 = 0x00;
    
    ECANCON = 0x00;                                 // Operation mode 0 (Legacy MOde))
    
    BRGCON1 = 0x01;                                 // Baud rate Setting (100kbs)
    BRGCON2 = 0xBA;
    BRGCON3 = 0x07;
             
    CIOCONbits.ENDRHI = 0x01;                       // 1 = CANTX pin will drive VDD when recessive
        
    //Normal mode
    
    CANCON = 0b00000000;                            // Normal mode
    CANSTATbits.OPMODE2 = 0x00;                     // Setting of CANSTAT in Normal mode
    CANSTATbits.OPMODE1 = 0x00;
    CANSTATbits.OPMODE0 = 0x00;
    
    while (CANSTATbits.OPMODE != 0);                // Wait until CANSTAT isn't in Normal mode

}

// Transmission of the CAN message with ID = 5 which is located on TX Buffer 0 
void CAN_TX_write_0(unsigned char data){

    TXB0DLC = 0x01;                                 // Data lenght = 1 byte
    TXB0DLCbits.TXRTR = 0x00;                       // Setting of RTR bit at 1  
    TXB0SIDLbits.EXIDE = 0x00;                      // Setting of transmission bits
    TXB0SIDH = 0x00;                            
    TXB0SIDL = 0xA0;                                // Identifier of message = 5 (101)
    TXB0CONbits.TXPRI0 = 0x01;                      // Priority bits of the message
    TXB0CONbits.TXPRI1 = 0x01;

    TXB0D0 = data;                                  // Filling the first register of TX buffer 0

    TXB0CONbits.TXREQ = 1;                          // Set the bit flag for the transmission request

    while (TXB0CONbits.TXREQ != 0) {                // Wait for the CAN TX buffer to be ready
        
        if (TXB0CONbits.TXERR == 1){                // Check if there is a bus error during transmission
            LED2 = 1;                               // Led2 switches on if there is an error
        }
    }

    if (TXB0CONbits.TXERR == 1) {                   // Check if there is a bus error during transmission
        LED2 = 1;                                   // Led2 switches on if there is an error
    }
    
    if (TXB0CONbits.TXERR == 0) {
        LED2 = 0;                                   // Led2 is off if the transmission is successfully completed
    }

}