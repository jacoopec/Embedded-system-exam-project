#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "FunctionsFile.h" 






void clean()              //this function clean the PORT B C D
{
	LATB = 0;
	LATD = 0;
	LATC = 0;
}




void horn(void)      //this function produces a noise
{
	LATEbits.LE1 = 1;
	_delay(200000);
	LATEbits.LE1 = 0;
}



void swapMsg2(unsigned int history[])         //tihs function swap the two variables in the array
{
	unsigned int swapMessage;
	swapMessage =history[1];
	history[1]     = history[0];
	history[0]     = swapMessage;
}






void itoa(unsigned int val, char* str )          //this function is used to convert the value acquired from the ADC
{
  str[0]=(val/10000)+0x30;  
  str[1]=((val%10000)/1000)+0x30;  
  str[2]=((val%1000)/100)+0x30;  
  str[3]=((val%100)/10)+0x30;
  str[4]=(val%10)+0x30;
  str[5]=0;
}



unsigned int getForce(void)        //this function gets the value of the force acting on the piston
{
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
   return ((((uint8_t)ADRESH)<<2)|(ADRESL>>6));
}