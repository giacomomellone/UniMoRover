#define OVERRUN     RCSTA1bits.OERR

char UART_Init(const long int baudrate)
{
	unsigned int x;
	x = (_XTAL_FREQ - baudrate*64)/(baudrate*64);
	if(x>255)
	{
		x = (_XTAL_FREQ - baudrate*16)/(baudrate*16);
		TXSTA1bits.BRGH = 1;
	}
	if(x<256)
	{
	  SPBRG1 = x;
	  TXSTA1bits.SYNC = 0;
	  RCSTA1bits.SPEN = 1;
      TRISCbits.TRISC7 = 1; //RX1
      TRISCbits.TRISC6 = 0; //TX1
      RCSTA1bits.CREN = 1;
      TXSTA1bits.TXEN = 1;
	  return 1;
	}
	return 0;
}

char UART_TX_Empty()
{
  return TXSTA1bits.TRMT;
}

char UART_Data_Ready()
{
   return RC1IF;
}

char UART_Read()
{
  while(!RC1IF);
  return RCREG1;
}

void UART_Read_Text(char *Output, unsigned int length)
{
	unsigned int i;
	for(i= 0; i < length; i++)
		Output[i] = UART_Read();
}

void UART_Write(char data)
{
  while(!TXSTA1bits.TRMT);
  TXREG1 = data;
}

void UART_Write_Text(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write(text[i]);
}