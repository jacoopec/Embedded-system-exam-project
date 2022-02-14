
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "defrostFile.h"

unsigned int getT(void)       // new temperature measurement
{
    ADCON0bits.GO = 1;         //SoC
    while(ADCON0bits.GO == 1); //wait for EoC 
         
    return ADRESH;
}
//--------------------------------------------------




void update_HMI(unsigned int temp, unsigned int* tTarget)
{
    if ((unsigned int) (temp < 32))  LATD=0;             // T < -60°C            LEDs 00000000
    else if (((unsigned int)(32 <= temp)) && ((unsigned int)(temp <= 63)))   LATD=1; // -60°C < T < -50°C    LEDs 00000001
    else if (((unsigned int)(64 <= temp)) && ((unsigned int)(temp <= 95)))   LATD=3; // -50°C < T < -40°C    LEDs 00000011
    else if (((unsigned int)(96 <= temp)) && ((unsigned int)(temp <= 127)))  LATD=7; // -40°C < T < -30°C    LEDs 00000111
    else if (((unsigned int)(128 <= temp)) && ((unsigned int)(temp <= 159))) LATD=15; // -30°C < T < -20°C   LEDs 00001111
    else if (((unsigned int)(160 <= temp)) && ((unsigned int)(temp <= 191))) LATD=31; // -20°C < T < -10°C   LEDs 00011111
    else if (((unsigned int)(192 <= temp)) && ((unsigned int)(temp <= 223))) LATD=63; // -10°C < T <   0°C   LEDs 00111111
    else if (((unsigned int)(224 <= temp)) && ((unsigned int)(temp < 255))) 
	{
	  LATD=127;                 //   0°C < T < +10°C    LEDs 01111111
	  *tTarget = true;          // Stop defrost
	}
    else LATD=255;                                   // +10°C < T < +20°C   LEDs 11111111
    
    return;
}


