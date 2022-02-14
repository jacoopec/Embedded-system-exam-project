void init_PORTS(void);      
void init_interrupts(void); 
void init_Timers(void);  
void init_ADC(void);
void init_ADC2(void);



#define left      0x10  //(-90)
#define right     0x01  //(+90)


//TIMER0
#define TMR0H_set 0xB2   //MSB0xF8
#define TMR0L_set 0x04  //LSB 0x6E //


//TIMER1
//1 msec posizione a sinistra
#define TMR1H_L90 0xFC //0xFC   //F830
#define TMR1L_L90 0x5B //0x41

// 2 msec posizione a destra
#define TMR1H_L09 0xB2 //0xF8  //FC18
#define TMR1L_L09 0x04 //0x59