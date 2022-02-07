
/* 
 * File:   timer1.c
 * Author: Sjensi
 *
 * Created on February 4, 2022, 8:32 AM
 */

#include <xc.h>
#include "timer1.h"

void Timer1_Initialize(void){
    //TGGO done; TGSPM disabled; TGTM disabled; TGPOL low; TMRGE disabled; 
    T1GCON = 0x0;
    //TGSS T1G_pin; 
    T1GATE = 0x0;
    //TMRCS FOSC/4; 
    T1CLK = 0x1;
    //TMRH 255; 
    TMR1H = 0xFF;
    //TMRL 255; 
    TMR1L = 0xFF;
    
    //Clear interrupt flags
    PIR4bits.TMR1IF = 0;
    PIR5bits.TMR1GIF = 0;
    
    //TMRON disabled; TRD16 disabled; nTSYNC synchronize; TCKPS 1:1; 
    T1CON = 0x0;
}

void Timer1_Start(void){
    // Start the Timer by writing to TMR1ON bit
    T1CONbits.TMR1ON = 1;
}

void Timer1_Stop(void){
    // Stop the Timer by writing to TMR1ON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t Timer1_Read(void){
    uint16_t readVal;
    uint8_t readValHigh, readValLow;
	
    readValLow = TMR1L;     //We must first access lower byte for the high byte to load
    readValHigh = TMR1H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return readVal;
}

void Timer1_Write(size_t timerVal){
    if (T1CONbits.nT1SYNC == 1){
        
        T1CONbits.TMR1ON = 0;  // Stop the Timer 

        TMR1H = (uint8_t)(timerVal >> 8);   // Write to the Timer1 register, first higher which will be loaded when we write to lower
        TMR1L = (uint8_t)timerVal;

        T1CONbits.TMR1ON = 1; // Start the Timer after writing to the register
    }
    else{
        TMR1H = (uint8_t)(timerVal >> 8);    // Write to the Timer1 register
        TMR1L = (uint8_t)timerVal;
    }
}