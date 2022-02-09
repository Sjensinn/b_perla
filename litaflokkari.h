/* 
 * File:   litaflokkari.h
 * Author: Sjensi
 * 
 * Contains functions used by the color sorting machine
 * 
 * Created on February 8, 2022, 11:34 AM
 */

/* Example Main function
 * 
 * @code
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

       void main(void) {
           //Initiate sequence!
          system_init();                  //Initiate clock, pins, uart, i2c, timer1 and interrupts
          uart_init();
          PCA_Init(130, 0x80);          //Initiate PCA9685 module with i2c_address = 0x80 and prescalar = 130 for 50Hz
          LCD_init(0x4E);               // Initialize LCD module with i2c_address = 0x4E
          sensor_init();                //Initialize the TCS3200 sensor

          //Program runs here
          uint8_t curr_col = 0;
          print_welcome_message();

           while(1){                       //Embedded systems never stop having fun!
               LED_TOGGLE();               //And we have rave lights
               curr_col = find_color();               //Run sensor for each filter and compare results with bead color
               //Post what color we sensed: if we find green print GREEN to screen
               print_color_quantity();
               PCA_Servo_Pos(curr_col);
               __delay_ms(1000); 
           }
           return;
       }
 * @endcode
 *
 */

#ifndef LITAFLOKKARI_H
#define	LITAFLOKKARI_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef SERVOMIN   
#define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
#endif
#ifndef SERVOMAX
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#endif
    
//Yellow beat color ranges
#define YELLOW_RED_MAX 255
#define YELLOW_RED_MIN 1
#define YELLOW_GREEN_MAX 255
#define YELLOW_GREEN_MIN 1
#define YELLOW_BLUE_MAX 255
#define YELLOW_BLUE_MIN 1
#define YELLOW_CLEAR_MAX 255
#define YELLOW_CLEAR_MIN 1
//RED beat color ranges
#define RED_RED_MAX 255
#define RED_RED_MIN 1
#define RED_GREEN_MAX 255
#define RED_GREEN_MIN 1
#define RED_BLUE_MAX 255
#define RED_BLUE_MIN 1
#define RED_CLEAR_MAX 255
#define RED_CLEAR_MIN 1
//GREEN beat color ranges
#define GREEN_RED_MAX 255
#define GREEN_RED_MIN 1
#define GREEN_GREEN_MAX 255
#define GREEN_GREEN_MIN 1
#define GREEN_BLUE_MAX 255 
#define GREEN_BLUE_MIN 1
#define GREEN_CLEAR_MAX 255
#define GREEN_CLEAR_MIN 1
//BLUE beat color ranges 
#define BLUE_RED_MAX 255
#define BLUE_RED_MIN 1
#define BLUE_GREEN_MAX 255
#define BLUE_GREEN_MIN 1 
#define BLUE_BLUE_MAX 255 
#define BLUE_BLUE_MIN 1
#define BLUE_CLEAR_MAX 255
#define BLUE_CLEAR_MIN 1
//BLACK beat color ranges
#define BLACK_RED_MAX 255
#define BLACK_RED_MIN 1
#define BLACK_GREEN_MAX 255 
#define BLACK_GREEN_MIN 1
#define BLACK_BLUE_MAX 255
#define BLACK_BLUE_MIN 1
#define BLACK_CLEAR_MAX 255
#define BLACK_CLEAR_MIN 1
//WHITE beat color ranges
#define WHITE_RED_MAX 255
#define WHITE_RED_MIN 1
#define WHITE_GREEN_MAX 255
#define WHITE_GREEN_MIN 1 
#define WHITE_BLUE_MAX 255
#define WHITE_BLUE_MIN 1
#define WHITE_CLEAR_MAX 255 
#define WHITE_CLEAR_MIN 1
//BROWN beat color ranges
#define BROWN_RED_MAX 255
#define BROWN_RED_MIN 1
#define BROWN_GREEN_MAX 255
#define BROWN_GREEN_MIN 1
#define BROWN_BLUE_MAX 255 
#define BROWN_BLUE_MIN 1
#define BROWN_CLEAR_MAX 255
#define BROWN_CLEAR_MIN 1
    
uint8_t yellow_bead, red_bead, green_bead, blue_bead, black_bead, white_bead, brown_bead, unsort_bead = 0;
    
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

/**
 * @brief   This function prints a welcome message to the LCD screen
 *          Delays for 5 seconds
 * @param   void            
 * @return  void
 */
void print_welcome_message(void);

/**
 * @brief   This function samples each color filter on the sensor
 *          Then runs those values through color_compare_return() function
 *          and returns the color code from color_compare_return() function
 * @param   void            
 * @return  returns color code integer, ranging from 0-7 for given colors
 */
uint8_t find_color(void);

/**
 * @brief   This function prints a welcome message to the LCD screen
 * @param   red : 16 bit value from sensor
 *          green: 16 bit value from sensor
 *          blue: 16 bit value from sensor
 *          clear: 16 bit value from sensor           
 * @return  returns color code integer, ranging from 0-7 for given colors
 * 
 *          In order to use this function, user must first set the constants for each color combination
 */
uint8_t color_compare_return(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear);

/**
 * @brief   This function prints the current number of sorted beads
 *          We only have space for two decimal numbers for each color
 *          so if we reach 99 we must set the counter back to 0, indicating that 100 has reached
 * @param   void            
 * @return  void
 */
void print_color_quantity(void);

#endif