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
   system_init(); 

    uint8_t curr_col;
    print_welcome_message();
   
    while(1){               
       slide_to_mid();
       __delay_ms(50);
        curr_col = find_color();    
        PCA_Servo_Pos(curr_col);
        print_color_quantity();
        __delay_ms(100);
    }
    
    return;
}
 * */


void main(void){
    system_init();
    while(1){
        calibrate_bead_values();
        
    }
    return;
}


