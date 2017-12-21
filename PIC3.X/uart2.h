void init_UART(void){
    //Initialize UART
    //TXSTA = 0b00100100;
    TXSTA2bits.TXEN = 1;
    TXSTA2bits.TX9 = 0;
    TXSTA2bits.SYNC = 0;                             //Asynchronous mode
    TXSTA2bits.BRGH = 1;                             //High Baud Rate Select bit
    //RCSTA = 0b10010000;
    RCSTA2bits.SPEN = 1;
    RCSTA2bits.RX9 = 0;
    RCSTA2bits.CREN = 1;
    //BAUDCON
    BAUDCON2bits.BRG16 = 0;                            //16-Bit Baud Rate Register Enable bit
    SPBRG2 = 207;                          //When SYNC=0,BRGH=1,BRG16=0 and Fosc=8Mhz,
    // for having a low error value and a baud rate of 2400bit/s, you should set
    //SPBRG like this
}

char UART_Init(const long int baudrate)
{
	unsigned int x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
	if(x>255)
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
		TXSTA2bits.BRGH = 1;
	}
	if(x<256)
	{
	  SPBRG = x;
	  TXSTA2bits.SYNC = 0;
	  RCSTA2bits.SPEN = 1;
          TRISC7 = 1;
          TRISC6 = 1;
          RCSTA2bits.CREN = 1;
          TXSTA2bits.TXEN = 1;
	  return 1;
	}
	return 0;
}

char UART_TX_Empty()
{
  return TXSTA2bits.TRMT;
}

char UART_Data_Ready()
{
   return RCIF;
}

char UART_Read()
{
 
  while(!RCIF);
  return RCREG2;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	unsigned int i;
	for(int i=0;i<length;i++)
		Output[i] = UART_Read();
}

void UART_Write(char data)
{
  while(!TXSTA2bits.TRMT);
  TXREG = data;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}