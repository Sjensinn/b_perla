/* 
 * File:   tcs3200.h
 * Author: Sjensi
 *  Used with PIC16F18877 and TCS3200
 * 
 * Pins as follows:
 * S0 - RA0 - output
 * S1 - RA1 - output
 * S2 - RA2 - output
 * S3 - RA3 - output
 * OE - RB1 - output
 * OUT - RB0 - input
 * 
 * Uses Timer1 to measure the pulse width.
 * Filter_x filters each color
 * More color = smaller pulse width
 * 
 *        
            filter_red();
            printf("R: %u\t", sample_reading());
            filter_green();
            printf("G: %u\t", sample_reading());
            filter_blue();
            printf("B: %u\r\n", sample_reading());
       
 * 
 * Created on February 1, 2022, 8:36 AM
 */

#ifndef TCS3200_H
#define	TCS3200_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
    
#include <xc.h>
#include <stdio.h>

    //Initializes the frequency
void sensor_init(void);
//Sets to red filter
void filter_red(void);
//sets to blue filter
void filter_blue(void);
//Sets to green filter
void filter_green(void);
//Sets to clear filter
void filter_clear(void);
//samples the sensor and returns timer1 16 bit value
uint16_t sample_reading(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TCS3200_H */

