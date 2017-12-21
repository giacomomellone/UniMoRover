char UART_Init_2(const long int baudrate)
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
	  SPBRG2 = x;
	  TXSTA2bits.SYNC = 0;
	  RCSTA2bits.SPEN = 1;
      TRISDbits.TRISD7 = 1; //RX2
      TRISDbits.TRISD6 = 0; //TX2
      RCSTA2bits.CREN = 1;
      TXSTA2bits.TXEN = 1;
	  return 1;
	}
	return 0;
}

char UART_TX_Empty_2()
{
  return TXSTA2bits.TRMT;
}

char UART_Data_Ready_2()
{
   return RC2IF;
}

char UART_Read_2()
{
 
  while(!RC2IF);
  return RCREG2;
}

void UART_Write_2(char data)
{
  while(!TXSTA2bits.TRMT);
  TXREG2 = data;
}

void UART_Write_Text_2(char *text)
{
  int i;
  for(i=0;text[i]!='\0';i++)
	  UART_Write_2(text[i]);
}