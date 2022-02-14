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

#ifndef LFSMIN   //200 works
#define LFSMIN  130 // This is the 'minimum' pulse length count (out of 4096)
#endif
#ifndef LFSMAX    //500 works
#define LFSMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#endif
    
//Yellow beat color ranges
#define YELLOW_RED_MAX 4033
#define YELLOW_RED_MIN 1945
#define YELLOW_GREEN_MAX 7171
#define YELLOW_GREEN_MIN 3775
#define YELLOW_BLUE_MAX 7129
#define YELLOW_BLUE_MIN 4159
#define YELLOW_CLEAR_MAX 1969
#define YELLOW_CLEAR_MIN 1075
//RED beat color ranges
#define RED_RED_MAX 4507
#define RED_RED_MIN 2551
#define RED_GREEN_MAX 8923
#define RED_GREEN_MIN 5743
#define RED_BLUE_MAX 7177
#define RED_BLUE_MIN 4639
#define RED_CLEAR_MAX 2221
#define RED_CLEAR_MIN 1369
//GREEN beat color ranges
#define GREEN_RED_MAX 7033
#define GREEN_RED_MIN 4135
#define GREEN_GREEN_MAX 9985
#define GREEN_GREEN_MIN 6169
#define GREEN_BLUE_MAX 9343
#define GREEN_BLUE_MIN 5527
#define GREEN_CLEAR_MAX 2791
#define GREEN_CLEAR_MIN 1795
//BLUE beat color ranges 
#define BLUE_RED_MAX 6583
#define BLUE_RED_MIN 3409
#define BLUE_GREEN_MAX 9301
#define BLUE_GREEN_MIN 15323
#define BLUE_BLUE_MAX 7411
#define BLUE_BLUE_MIN 4453
#define BLUE_CLEAR_MAX 2569
#define BLUE_CLEAR_MIN 1429
//BLACK beat color ranges
#define BLACK_RED_MAX 5863
#define BLACK_RED_MIN 3271
#define BLACK_GREEN_MAX 9595 
#define BLACK_GREEN_MIN 5419
#define BLACK_BLUE_MAX 8521
#define BLACK_BLUE_MIN 4879
#define BLACK_CLEAR_MAX 2521
#define BLACK_CLEAR_MIN 1459
//WHITE beat color ranges
#define WHITE_RED_MAX 3181
#define WHITE_RED_MIN 2143
#define WHITE_GREEN_MAX 5047
#define WHITE_GREEN_MIN 3313
#define WHITE_BLUE_MAX 4550
#define WHITE_BLUE_MIN 3000
#define WHITE_CLEAR_MAX 967 
#define WHITE_CLEAR_MIN 1429
//ORANGE
#define ORANGE_RED_MAX 2725
#define ORANGE_RED_MIN 2137
#define ORANGE_GREEN_MAX 6901
#define ORANGE_GREEN_MIN 5143
#define ORANGE_BLUE_MAX 6070
#define ORANGE_BLUE_MIN 4690
#define ORANGE_CLEAR_MAX 1570
#define ORANGE_CLEAR_MIN 1220
//PINK
#define PINK_RED_MAX 2440
#define PINK_RED_MIN 1210
#define PINK_GREEN_MAX 255
#define PINK_GREEN_MIN 1
#define PINK_BLUE_MAX 255 
#define PINK_BLUE_MIN 1
#define PINK_CLEAR_MAX 255
#define PINK_CLEAR_MIN 1
//PURPLE
#define PURPLE_RED_MAX 4810
#define PURPLE_RED_MIN 2130
#define PURPLE_GREEN_MAX 7270
#define PURPLE_GREEN_MIN 4110
#define PURPLE_BLUE_MAX 5540
#define PURPLE_BLUE_MIN 3380
#define PURPLE_CLEAR_MAX 1990
#define PURPLE_CLEAR_MIN 1070
//NOTHING
#define NA_RED_MAX 8090
#define NA_RED_MIN 3180
#define NA_GREEN_MAX 13580
#define NA_GREEN_MIN 4300
#define NA_BLUE_MAX 12000
#define NA_BLUE_MIN 3860
#define NA_CLEAR_MAX 3320
#define NA_CLEAR_MIN 1190
uint8_t yellow_bead, red_bead, green_bead, blue_bead, black_bead, white_bead, brown_bead, unsort_bead = 0;
    
/**
 * @brief   This function turns one servo to position according to passed value 0/1
 *          Used by PCA_Servo_Pos();
 * @param   8 bit value n for servo positon
 *          8 bit value for position 0/1 for each of the three servos
 *          pos should be between 0-7              
 * @return  void
 */
void PCA_Servo_Command(uint8_t servo_nr, uint8_t servo_on_off);

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