/* 
 * File:   litaflokkari.h
 * Author: Sjensi
 * 
 * Contains functions used by the color sorting machine
 * 
 * Created on February 8, 2022, 11:34 AM
 */

#ifndef LITAFLOKKARI_H
#define	LITAFLOKKARI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdio.h>
#include "I2C_MSSP1_driver.h"
#include "LCD.h"
#include "PCA9685_driver.h"
#include "tcs3200.h"
#include "uart.h"

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


#endif