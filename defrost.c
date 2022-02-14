
uint8_t getT(void)       // new temperature measurement
{
    ADCON0bits.GO = 1;         //SoC
    while(ADCON0bits.GO == 1); //wait for EoC 
         
    return ADRESH;
}
//--------------------------------------------------

void update_HMI(uint8_t temp)
{
   if ((uint8_t) (temp < 32))  
    { serial_tx(0x10);}       // T < -60°C            LEDs 00000000
    else if (((uint8_t)(32 <= temp)) && ((uint8_t)(temp <= 63))) 
    { serial_tx(0x11);}       // -60°C < T < -50°C    LEDs 00000001
    else if (((uint8_t)(64 <= temp)) && ((uint8_t)(temp <= 95)))  
    { serial_tx(0x13);}       // -50°C < T < -40°C    LEDs 00000011
    else if (((uint8_t)(96 <= temp)) && ((uint8_t)(temp <= 127))) 
    { serial_tx(0x14);}       // -40°C < T < -30°C    LEDs 00000111
    else if (((uint8_t)(128 <= temp)) && ((uint8_t)(temp <= 159)))
    { serial_tx(0x15);}       // -30°C < T < -20°C   LEDs 00001111
    else if (((uint8_t)(160 <= temp)) && ((uint8_t)(temp <= 191))) 
    { serial_tx(0x16);}       // -20°C < T < -10°C   LEDs 00011111
    else if (((uint8_t)(192 <= temp)) && ((uint8_t)(temp <= 223)))
    { serial_tx(0x17);}       // -10°C < T <   0°C   LEDs 00111111
    else if (((uint8_t)(224 <= temp)) && ((uint8_t)(temp < 255))) 
	{
	  serial_tx(0x18);                //   0°C < T < +10°C    LEDs 01111111
	  T_target_reached = true;          // Stop defrost
	}
    else serial_tx(0x19);                                   // +10°C < T < +20°C   LEDs 11111111
    
    return;
}



void update_HMI2(uint8_t temp)
{
    if ((uint8_t) (temp < 32))  LATD=0;             // T < -60°C            LEDs 00000000
    else if (((uint8_t)(32 <= temp)) && ((uint8_t)(temp <= 63)))   LATD=1; // -60°C < T < -50°C    LEDs 00000001
    else if (((uint8_t)(64 <= temp)) && ((uint8_t)(temp <= 95)))   LATD=3; // -50°C < T < -40°C    LEDs 00000011
    else if (((uint8_t)(96 <= temp)) && ((uint8_t)(temp <= 127)))  LATD=7; // -40°C < T < -30°C    LEDs 00000111
    else if (((uint8_t)(128 <= temp)) && ((uint8_t)(temp <= 159))) LATD=15; // -30°C < T < -20°C   LEDs 00001111
    else if (((uint8_t)(160 <= temp)) && ((uint8_t)(temp <= 191))) LATD=31; // -20°C < T < -10°C   LEDs 00011111
    else if (((uint8_t)(192 <= temp)) && ((uint8_t)(temp <= 223))) LATD=63; // -10°C < T <   0°C   LEDs 00111111
    else if (((uint8_t)(224 <= temp)) && ((uint8_t)(temp < 255))) 
                                                {
                                                  LATD=127;                 //   0°C < T < +10°C    LEDs 01111111
                                                  T_target_reached = true;          // Stop defrost
                                                }
    else LATD=255;                                   // +10°C < T < +20°C   LEDs 11111111
    
    return;
}


void defrost(void)
{
	LATD = 0;       // reset HMI
            
            do             
                {
                 TempSys  = getT();       //get new temperature
                }while (TempSys != 0);
            
            LATDbits.LATD7 = 1;        //toggle led start defrost
            _delay(500);
            LATDbits.LATD7 = 0;
            
            GO_defrost = true;
            
            if (GO_defrost)
            {    
            while (!T_target_reached)      // Stop acquisition when the target temperature is reached
              {
                TempSys = getT();          //get T
                update_HMI(TempSys);       //update HMI 
              }           // end while defrost
                
                T_target_reached = false;               //ready for new de frost
                
	    }
}