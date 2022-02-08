/*
 * File:   newmain.c
 * Author: Sjensi
 *
 * Created on February 2, 2022, 3:35 PM
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include <xc.h>
#include <stdio.h>
#include "config_bits.h"
#include "system_init.h"
#include "uart.h"
#include "LCD.h"
#include "litaflokkari.h"


void main(void) {
   system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
   PCA_Init(130, 0x80);          //Initiate PCA9685 module with i2c_address = 0x80 and prescalar = 130 for 50Hz
   LCD_init(0x4E);               // Initialize LCD module with i2c_address = 0x4E
   sensor_init();                //Initialize the TCS3200 sensor
   
    while(1){                       //Embedded systems never stop having fun!
        LED_TOGGLE();               //And we have rave lights
        __delay_ms(1000); 
    }
    return;
}


