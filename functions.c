


unsigned char display7s(unsigned char v)
{
  switch(v)
  {
    case 0:
      return 0x3F;
    case 1:
      return 0x06;
    case 2:
      return 0x5B;
    case 3:
      return 0x4F;
    case 4:
      return 0x66;
    case 5:
      return 0x6D;
    case 6:
      return 0x7D;
    case 7:
      return 0x07;
    case 8:
      return 0x7F;
    case 9:
      return 0x6F;
    case 10:
      return 0x77;
    case 11:
      return 0x7c;
    case 12:
      return 0x58;
    case 13:
      return 0x5E;
    case 14:
      return 0x79;
    case 15:
      return 0x71;
    default:
      return 0;
  }
}

uint8_t getMaxForce(void)
{
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);
   return ((((uint8_t)ADRESH)<<2)|(ADRESL>>6));
}



void itoa(uint8_t val, char* str )
{
  str[0]=(val/10000)+0x30;  
  str[1]=((val%10000)/1000)+0x30;  
  str[2]=((val%1000)/100)+0x30;  
  str[3]=((val%100)/10)+0x30;
  str[4]=(val%10)+0x30;
  str[5]=0;
}


void horn(void)
{
	LATEbits.LE1 = 1;
	_delay(200000);
	LATEbits.LE1 = 0;
}


void ledColour(unsigned char v)
{
  switch(v)
  {
    case 'r':  //red
    {
	LATAbits.LA2 = 1;
	LATAbits.LA3 = 0;
	LATAbits.LA4 = 0;  
    }
    case 'g':   //green
    {
	LATAbits.LA2 = 0;
	LATAbits.LA3 = 1;
	LATAbits.LA4 = 0;   
    }
    case 'b':  //blu
    {
	LATAbits.LA2 = 0;
	LATAbits.LA3 = 0;
	LATAbits.LA4 = 1;    
    }
    case 'p':    //pink
    {
	LATAbits.LA2 = 0;
	LATAbits.LA3 = 0;
	LATAbits.LA4 = 1;    
    }
    case 'y':     //yellow
    {
	LATAbits.LA2 = 0;
	LATAbits.LA3 = 0;
	LATAbits.LA4 = 1;    
    }
     case 'w':     //white
    {
	LATAbits.LA2 = 1;
	LATAbits.LA3 = 1;
	LATAbits.LA4 = 1;    
    }
      case 'k':     //white
    {
	LATAbits.LA2 = 0;
	LATAbits.LA3 = 0;
	LATAbits.LA4 = 0;    
    }
      return;
  }
}





