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

#ifndef    
#define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
#endif
#ifndef
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#endif

//Turns one servo to position according to passed value 0/1
void PCA_Servo_Command(uint8_t n, uint8_t pos);
//Turn the servos to position according to 0-8 from passed variable pos
void PCA_Servo_Pos(uint8_t pos);


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

void PCA_Servo_Command(uint8_t n, uint8_t pos){
    uint8_t offval, onval;
    offval = (4095 - SERVOMIN) - pos(SERVOMAX-SERVOMIN);  //for the off value
    onval = SERVOMIN + pos(SERVOMAX - SERVOMIN);   //For the on value 

    PCA_Write(n, onval, offval);
    return;
}

void PCA_Servo_Pos(uint8_t pos){
    switch(pos){
        case 0:     //000
        //Unsorted
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 0);
        break;

        case 1:     //001
        //Yellow
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 1);
        break;

        case 2:     //010
        //Red
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 0);
        break;

        case 3:     //011
        //Green
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 1);
        break;
    
        case 4:     //100
        //Blue
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 0);
        break;

        case 5:     //101
        //Black
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 1);
        break;

        case 6:     //110
        //White
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 0);
        break;

        case 7:     //111
        //Brown
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 1);        
        break;
    }
}
