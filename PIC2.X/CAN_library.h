// CAN Library for PIC #2. 
// This PIC is used to receive data via CAN from PIC #3 and PIC #3bis which transmit data coming from rear and front ultrasonic sensors.
// PIC #2 doesn't use CAN Bus for transmitting messages.

typedef unsigned char BYTE;

// Structure of a CAN Message
typedef struct{             
	unsigned long identifier;                       // Message Identifier
	BYTE data;                                      // Data of the message
	BYTE type;                                      // Type of the data. 1 = IDE	0 = standard
	BYTE length;                                    // Data length
	BYTE RTR;                                       // Remote flag. RTR = 1 means remote frame

} CANmessage;

CANmessage *msg;                                    // Definition of the pointer used to read message in RX Buffers

// Initialization of the CAN Protocol for the message reception
void CAN_RX_initialize(void){                       

    CANCON = 0x80;                                  // Configuration mode Setting
                                                    // REQOP<2:0> = 100
    while(!(CANSTATbits.OPMODE ==0x04));            // Wait until CANSTAT isn't in Configuration mode
    
    ECANCON = 0x00;                                 // Operation mode 0 (Legacy mode)
 
    BRGCON1 = 0x01;                                 // Baud Rate Settings (100 kbs)
    BRGCON2 = 0xBA;
    BRGCON3 = 0x07;
      
    CIOCONbits.ENDRHI = 0x01;                       // 1 = CANTX pin will drive VDD when recessive
    
    //-------------------------------------------------------------
    // MASKS AND FILTERS CONFIGURATION
    //-------------------------------------------------------------
    
    // Mask 0 (M0) is configured only for standard messages
    RXM0EIDH = 0x00;    // Extended Address receive acceptance mask, high byte 
    RXM0EIDL = 0x00;    // Extended Address receive acceptance mask, low byte
    RXM0SIDH = 0xFF;    // Standard Address receive acceptance mask, high byte
    RXM0SIDL = 0xE0;    // Standard Address receive acceptance mask, low byte
    
    // Mask 1 (M1) is configured only for standard messages 
    RXM1EIDH = 0x00;    // Extended Address receive acceptance mask, high byte    
    RXM1EIDL = 0x00;    // Extended Address receive acceptance mask, low byte
    RXM1SIDH = 0xFF;    // Standard Address receive acceptance mask, high byte
    RXM1SIDL = 0xE0;    // Standard Address receive acceptance mask, low byte
    
    // Filter settings for the two RX Buffers
    RXF0EIDH = 0x00;    //Extended Address Filter-0 unused, set high byte to 0
    RXF0EIDL = 0x00;    //Extended Address Filter-0 unused, set low byte to 0
    RXF0SIDH = 0x00;    //Standard Address Filter-0 high byte set to 0x00
    RXF0SIDL = 0xA0;    //Standard Address Filter-0 low byte set to 0xA0  (ID = 0x05)
    
    RXF2EIDH = 0x00;    //Extended Address Filter-1 unused, set high byte to 0
    RXF2EIDL = 0x00;    //Extended Address Filter-1 unused, set low byte to 0
    RXF2SIDH = 0x00;    //Standard Address Filter-1 high byte set to 0x00
    RXF2SIDL = 0x40;    //Standard Address Filter-1 low byte set to 0x40  (ID = 0x02)
    
    //-------------------------------------------------------------
    // ACCEPTANCE FILTERS SETTINGS
    //-------------------------------------------------------------
    
    RXB0CONbits.FILHIT0 = 0;                        // This bit indicates which acceptance filter enabled the message reception into Receive Buffer 0.
                                                    // 0 = Acceptance Filter 0 (RXF0)
                                                    
    RXB0CONbits.RXM1    = 0;                        // RXM<1:0> = 01 -> Receive only valid messages with standard identifier
    RXB0CONbits.RXM0    = 1;   
    
    RXB1CONbits.FILHIT2 = 0;                        // FILHIT<2:0>: Filter Hit bits
    RXB1CONbits.FILHIT1 = 1;                        // These bits indicate which acceptance filter enabled the last message reception into Receive Buffer 1.
    RXB1CONbits.FILHIT0 = 0;                        // 010 = Acceptance Filter 2 (RXF2)         
    
    RXB1CONbits.RXM1    = 0;                        // RXM<1:0> = 01 -> Receive only valid messages with standard identifier
    RXB1CONbits.RXM0    = 1;   
    
    
    // Enter CAN module into normal mode
    CANCON = 0x00;                                  // Normal mode
    
    while(CANSTATbits.OPMODE==0x00);
    
    while (CANSTATbits.OPMODE != 0);                // Wait until CANSTAT isn't in Normal mode
    
}

//Reading the message in RX Buffer 0
unsigned char CAN_RX_read_0(){

    //Check for buffers overflows
    if (COMSTATbits.RXB0OVFL == 0x01) {
        
        COMSTATbits.RXB0OVFL = 0x00;                // Clear the overflow flag for RX Buffer 0
    }

    if (COMSTATbits.RXB1OVFL == 0x01) {
        
        COMSTATbits.RXB1OVFL = 0x00;                // Clear the overflow flag for RX Buffer 1
    }

    //RX Buffer 0 is read
    if (RXB0CONbits.RXFUL == 0x01) {                // Check if buffer is full
        // Arrow operator (->) is used for entering directly in the members of a struct variable which is pointed by a pointer
        // Clear the identifier
        msg->identifier = 0;

        //Retrieve the data                 
        msg->data = RXB0D0;                         // Filling the first Byte of RX Buffer 0
        
        //Retrieve the RTR bit
        msg->RTR = RXB0DLCbits.RXRTR;

        //Retrieve the length
        msg->length = RXB0DLC;

        //Retrieve the format (standard or extended)
        msg->type = RXB0SIDLbits.EXID;

        //Reading the identifier standard format
        if (RXB0SIDLbits.EXID == 0) {
            msg->identifier = ((unsigned long) RXB0SIDL) << 3;
        }

        RXB0CONbits.RXFUL = 0x00;                   // Clear the bit flag of buffer full for allowing the successive transmission

    }
        
    return RXB0D0;                              
}

//Reading the message in RX Buffer 1
unsigned char CAN_RX_read_1(){

    //Check for buffers overflows
    if (COMSTATbits.RXB0OVFL == 0x01) {

        COMSTATbits.RXB0OVFL = 0x00;                // Clear the overflow flag for RX Buffer 0
    }

    if (COMSTATbits.RXB1OVFL == 0x01) {

        COMSTATbits.RXB1OVFL = 0x00;                // Clear the overflow flag for RX Buffer 1
    }
        
    //RX Buffer 1 is read 
    if (RXB1CONbits.RXFUL == 0x01) {                // Check if buffer is full

        //UART_Write_Text("Buff1 Full");
        // Arrow operator (->) is used for entering directly in the members of a struct variable which is pointed by a pointer
        // Clear the identifier
        msg->identifier = 0;

        //Retrieve the data
        msg->data = RXB1D0;                         // Filling the first Byte of RX Buffer 1

        //Retrieve the RTR bit
        msg->RTR = RXB1DLCbits.RXRTR;

        //Retrieve the length
        msg->length = RXB1DLC;

        //Retrieve the format (standard or extended)
        msg->type = RXB1SIDLbits.EXID;

        //Reading the identifier standard format
        if (RXB1SIDLbits.EXID == 0) {
            msg->identifier = ((unsigned long) RXB1SIDL) << 3;
        }
        
        RXB1CONbits.RXFUL = 0x00;               // Clear the bit flag of buffer full for allowing the successive transmission
       
        }
    
    return RXB1D0;
}
