#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "COMSerial.h"


// Serial & Timing Parameters
static double const Fosc              = 4000000;// Oscillator Frequency in Hz
static double       Tosc              = 1/Fosc; // Tosc in sec
static double const desired_BaudRate  = 9600;    // Desired Baud Rate in bps


// USART configuration
void init_USART(void)
{
    SPBRG = 25; // round(((Fosc / desired_BaudRate)/16)-1); // baud rate
        
    TXSTAbits.TX9=0;   //TX 8 bits data
    TXSTAbits.TXEN=1;  //TX enable
    TXSTAbits.SYNC=0;  //Asynchronous Mode
    TXSTAbits.BRGH=1;  //High baud rate bit
    RCSTAbits.SPEN=1;  //Serial Port enable
    RCSTAbits.RX9=0;   //RX 8 bits data
    RCSTAbits.CREN=1;  //RX enable
}

void serial_txchar(unsigned char val)
{
  TXREG = val;
  while(!TXSTAbits.TRMT);
}

void serial_txnum(unsigned int  num)
{
  TXREG = num;
  while(!TXSTAbits.TRMT);
}



