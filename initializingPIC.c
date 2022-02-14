#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "initializingPIC.h"

void init_PORTS(void)          //PORTS configurations
{
    //PORTA
    LATA = 0;
    PORTA = 0;
    TRISA = 0xC3;      //1100 0011
    
	
    // PORTB
           //All pins off
     LATB    = 0;  
    PORTB   = 0;
    TRISB   = 0xF3;     //1111 0011     
                    //RB1, RB2, RB3 as output
    
    // PORTC
         //All pins off
    PORTC   = 0;
    TRISC   = 0x40;       //0100 0001
    LATC    = 0;  
    
    
    // PORTD
           //All pins off
    LATD    = 0; 
    PORTD   = 0;
    TRISD   = 0x00;     //All pins as output
    
    
    //PORTE
   LATE  = 0;
    PORTE = 0;
    TRISE = 0x00;
    
    return;
}
//--------------------------------------------------

void init_Timers(void)          //Timers configuration
{
    //Timer 0
    T0CONbits.T08BIT = 0;   //16-bit
    T0CONbits.T0CS   = 0;	//internal instruction cycle clock (timer)
    T0CONbits.PSA    = 1;	//No prescaler
    T0CONbits.TMR0ON = 0;	//Timer 0 disabled
	
//	PWM period = 20 msec => 20000 Tcyc =>
//	 => overflow after 20000 Tcyc 
//	 => Set initial value of (TMR0H:TMR0L) = 65.536-20.000 = 45.536 = 0xB1E0
//	TMR0H = 0xB1
//	TMR0L = 0xE0
	
	TMR0H = TMR0H_set;       //set TMR0H
	TMR0L =	TMR0L_set;       //set TMR0L
	
    //Timer 1
    T1CONbits.RD16	  = 1;  //16-bit
    T1CONbits.T1CKPS1 = 0;  //No prescaler
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1OSCEN = 0;  //Timer 1 ext oscillator disabled
    T1CONbits.TMR1CS  = 0;  //Internal clock (Fosc/4)
    T1CONbits.TMR1ON  = 0;  //Timer 1 disabled
	
    //set intitial position = left
    TMR1H = TMR1H_L90;
    TMR1L = TMR1L_L90;
       
    return;
}


void init_interrupts(void)       // Interrupts configuration 
{
    PIR1bits.RCIF       = 0;          //Clear RCIF Interrupt Flag
    PIE1bits.RCIE       = 1;          //Set RCIE Interrupt Enable (USART RX)
    INTCONbits.PEIE	= 1;        //Enable peripheral interrupts
    INTCONbits.RBIE     = 1;
    INTCONbits.INT0E    = 1;	    // enable external interrupt from RB0
    INTCON2bits.INTEDG0 = 0; 
    INTCONbits.TMR0IE   = 1; 
    PIE1bits.TMR1IE     = 1;        // enable interrupt on Timer1 overflow

                                //Global Interrupt enabled in main ( ei(); )
    return;
}


void init_ADC(void)             // ADC configuration 
{
    ADCON0 = 0x09;      //Ch0 & module ON
    ADCON1 = 041;      //All Analog channel
    
    return;
}

 
void init_ADC2(void)             // ADC configuration 
{
    ADCON0 = 0x01;      //Ch0 & module ON
    ADCON1 = 0x00;     //All Analog channel
    
    return;
}