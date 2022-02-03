/*
 * File:   newmain.c
 * Author: Sjensi
 *
 * Created on February 2, 2022, 3:35 PM
 */

//Pin macros
#define LED_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include "config_bits.h"
#include <xc.h>
#include <stdio.h>
#include "I2C_MSSP1_driver.h"
#include "PCA9685_driver.h"
#include "tcs3200.h"

void clock_init(void);
void pin_init(void);
void uart_init(void);
void putch(uint8_t txData);

void main(void) {
    clock_init();
    pin_init();
    uart_init();
    I2C_init();
    
    INTCONbits.GIE = 1;         //Enable Global interrupts
    INTCONbits.PEIE = 1;        //Enable Pheripheral Interrupts
    
    PCA_Init(130 ,0x80);     //Initiate PCA driver with the address(0x80) and prescalar (decimal 130)
    
    while(1){     
        LATBbits.LATB2 = 0;             //Min range
        PCA_write(0, 4000, 95);         //4095 is max resolution, On for 4000/4095, off for 95/4095  
        __delay_ms(5000);   
        
        LATBbits.LATB2 = 1;             //Max range
        PCA_write(0, 3595, 500);        //4095 is max resolution, On for 500/4095, Off for 3595/4095
        __delay_ms(5000);   
    }
    return;
}

void clock_init(){
        // Set the CLOCK CONTROL module to the options selected in the user interface.
    // NDIV 2; NOSC HFINTOSC; 
    OSCCON1 = 0x61;
    OSCCON2 = 0x70;
    // SOSCPWR Low power; CSWHOLD may proceed; 
    OSCCON3 = 0x0;
    // EXTOEN disabled; HFOEN enabled; MFOEN disabled; LFOEN disabled; SOSCEN disabled; ADOEN disabled; 
    OSCEN = 0x40;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x6;
    // 
    OSCSTAT = 0x0;
    // TUN undefined; 
    OSCTUNE = 0x0;
}

void pin_init(){
       /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x18;
    LATD = 0x0;
    LATE = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x30;
    TRISB = 0xF1;
    TRISC = 0xBF;
    TRISD = 0x0;
    TRISE = 0x7;

    /**
    ANSELx registers
    */
    ANSELA = 0x30;
    ANSELB = 0xF0;
    ANSELC = 0x67;
    ANSELD = 0x0;
    ANSELE = 0x7;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;
    WPUD = 0x0;
    WPUE = 0x0;
  

    /**
    APFCONx registers
    */

    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    ODCOND = 0x0;
    ODCONE = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x7;
    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xF;

    /**
    PPS registers
    */
    RXPPS = 0x17; //RC7->EUSART:RX;
    T1CKIPPS = 0x10; //RC0->TMR1:T1CKI;
    T1GPPS = 0xD; //RB5->TMR1:T1G;
    RC6PPS = 0x10;  //RC6->EUSART:TX;
    SSP1CLKPPS = 0x13;  //RC3->MSSP1:SCL1;
    RC3PPS = 0x14;  //RC3->MSSP1:SCL1;
    SSP1DATPPS = 0x14;  //RC4->MSSP1:SDA1;
    RC4PPS = 0x15;  //RC4->MSSP1:SDA1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;
}

void uart_init(void){
        // Set the EUSART module to the options selected in the user interface.

    // ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; ABDOVF no_overflow; 
    BAUD1CON = 0x48;

    // ADDEN disabled; CREN enabled; SREN disabled; RX9 8-bit; SPEN enabled; 
    RC1STA = 0x90;

    // TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
    TX1STA = 0x26;

    // SPBRGL 159; 
    SP1BRGL = 0x9F;

    // SPBRGH 1; 
    SP1BRGH = 0x1;
    
    ANSELCbits.ANSC3 = 0;   //Set to digital
    ANSELCbits.ANSC4 = 0;   //Set to digital
    TRISCbits.TRISC3 = 1;   //Set as input
    TRISCbits.TRISC4 = 1;   //Set as input
}

void putch(uint8_t data){
    while(0 == PIR3bits.TXIF){
        continue;
    }
    TX1REG = data;    // Write the data byte to the USART.
}