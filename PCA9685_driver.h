/* 
 * File:   PCA9685_driver.h
 * Author: Sjensi
 *
 * --Information: Read before use!
 *      *Measured Clock frequency is 26.763.265 Hz
 *      *Calculated prescalar for given frequency to get 50Hz output is 130
 *      *PCA9685 address: 0x80
 *      *I2c Frequency should be 100kHz
 *      
 * Created on February 3, 2022, 8:27 AM
 */

#ifndef PCA9685_DRIVER_H
#define	PCA9685_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
    
#define PCA_OE_ENABLE() LATBbits.LATB3 = 0;
#define PCA_OE_DISABLE() LATBbits.LATB3 = 1;

#ifndef    
#define SERVOMIN  95 // This is the 'minimum' pulse length count (out of 4096)
#endif
#ifndef
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#endif

    uint8_t pca_address;

/**
 * @brief This function initializes the PCA9685 unit
 *        This routine must be called before any other PCA9685 routines.
 * @param   8 bit value for PCA9685 prescalar 
 *          8 bit value for PCA9685 I2C address
 * @return void.
 *
 * @code
 * void main(void)
 * {
 *     PCA_Init();
 *     
 *     while(1)
 *     {   
 *         PCA_Tasks();
 *     }
 * }
 * @endcode
 */
void PCA_Init(uint8_t prescalar, uint8_t pca_addr);


/**
 * @brief This function writes values on/off to led channel ChannelN of PCA9685
 * @param ChannelN : The number of the channel of PCA9685 to be written to
 *              on : The on value for given channel
 *             off : The off value for given channel              
 * @return void.
 *
 * @code
 * void main(void){
 *     PCA_Init();
 *     
 *     while(1){   
 *         PCA_Write(0, SERVOMIN, 4095-SERVOMIN);
 *          __delay_ms(500);
 *          PCA_Write(0, SERVOMAX, 4095-SERVOMAX);
 *     }
 * }
 * @endcode
 */
void PCA_write(uint8_t ChannelN, uint16_t on, uint16_t off);


#ifdef	__cplusplus
}
#endif

#endif	/* PCA9685_DRIVER_H */

