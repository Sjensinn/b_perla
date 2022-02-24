/*
 * File:   newmain.c
 * Author: Sjensi
 *
 *  Part of b_perla
 * 
 * Created on February 2, 2022, 3:35 PM
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#include <xc.h>
#include <stdio.h>
#include "litaflokkari.h"
#include "PCA9685_driver.h"
#include "config_bits.h"
#include "system_init.h"
#include "tcs3200.h"
#include "uart.h"
#include "LCD.h"
#include "timer1.h"
#include "tcs3472.h"

//Main main function
/*
void main(void) {
    //Initiate sequence!
   system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
   uart_init();
   I2C_init();
   Timer1_Initialize();
   PCA_Init(130, 0x80);          //Initiate PCA9685 module with i2c_address = 0x80 and prescalar = 130 for 50Hz
   LCD_init(0x4E);               // Initialize LCD module with i2c_address = 0x4E
   sensor_init();                //Initialize the TCS3200 sensor
   
   //Program runs here
   print_welcome_message();
   
    while(1){                       //Embedded systems never stop having fun!
        for(int i = 0; i < 8; i++){
        LED_TOGGLE();               //And we have rave lights
        //curr_col = find_color();               //Run sensor for each filter and compare results with bead color
        //Post what color we sensed: if we find green print GREEN to screen
        print_color_quantity();
        PCA_Servo_Pos(i);
        __delay_ms(2000);
        }

    }
    return;
}
*/

//Testing TCS3200
/*
void main(void){

    system_init();
    uart_init();
    sensor_init();
    Timer1_Initialize();
    
    while(1){
        calibrate_bead_values();
    }
}
*/

//Test TCS3472
/*
void main(void){
    system_init();
    I2C_init();
    uart_init();
    TCS3472_Init(0x29, 1);
    
    
    //__delay_ms(1000);
    while(1){
        TCS3472_getId();
        TCS3472_sample_beads();
    }
}
 * */


//Main function to find min max mid values for servos

void main(void){
    system_init();
    uart_init();
    Timer1_Initialize();
    I2C_init();
    PCA_Init(130, 0x80);
    sensor_init();
    
    while(1){
        
        for(int i = 0; i < 8; i++){
            slide_to_mid();
            find_print(); //take measurements of the pearl
            PCA_Servo_Pos(i);
        }
    }
   
}


