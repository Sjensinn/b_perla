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

/**
 * @brief   This function turns one servo to position according to passed value 0/1
 *          Used by PCA_Servo_Pos();
 * @param   8 bit value n for servo positon
 *          8 bit value for position 0/1 for each of the three servos
 *          pos should be between 0-7              
 * @return  void
 */
void PCA_Servo_Command(uint8_t n, uint8_t pos);

/**
 * @brief   This function turn the servos 1, 2, 3 to position according to 0-8 from passed variable pos
 * @param   8 bit value pos for position            
 * @return  void
 *
 * @code
 * void main(void){
 *     PCA_Init(prescalar, address);
 * 
 *     while(1){   
 *          PCA_Servo_Pos(0);
 *          __delay_ms(1000);
 *          PCA_Servo_Pos(8);
 *          __delay_ms(1000);  
 *     }
 * }
 * @endcode
 */
void PCA_Servo_Pos(uint8_t pos);


#endif