/* 
 * File:   tcs3472.h
 * Author: Sjensi
 *
 * Created on February 16, 2022, 9:46 AM
 */

#include <xc.h>

#ifndef TCS3472_H
#define	TCS3472_H

#ifdef	__cplusplus
extern "C" {
#endif

//Register Map
#define TCS3472_COMMAND 0x80
#define TCS3472_ENABLE 0x00
#define TCS3472_ATIME 0x01
#define TCS3472_WTIME 0x03
#define TCS3472_AILTL 0x04
#define TCS3472_AILTH 0x05
#define TCS3472_AIHTL 0x06
#define TCS3472_AIHTH 0x07
#define TCS3472_PERS 0x0C
#define TCS3472_CONFIG 0x0D
#define TCS3472_CONTROL 0x0F
#define TCS3472_ID 0x12
#define TCS3472_STATUS 0x13
#define TCS3472_CDATAL 0x14
#define TCS3472_CDATAH 0x15
#define TCS3472_RDATAL 0x16
#define TCS3472_RDATAH 0x17
#define TCS3472_GDATAL 0x18
#define TCS3472_GDATAH 0x19
#define TCS3472_BDATAL 0x1A
#define TCS3472_BDATAH 0x1B

//Address
#define TCS3472_BASE_ADDR 0x29 //Eða 0x39

uint8_t tcs_addr;

/**         ***Initiate function for TCS3472***
 * @brief   This function initiates the sensor with given address
*           Sets to default settings
 * @param   addr: I2C Address of the sensor      
 * @return  void
 */
void TCS3472_Init(uint8_t addr, uint8_t troubleshoot);


/**         ***Write Function for TCS3472***
 * @brief   This function writes one byte specified register to our TCS3472 sensor
 *          
 * @param   reg: register to write to
 *          data: data to write to register           
 * @return  void
 */
void TCS3472_Write(uint8_t reg, uint8_t data);

/**         ***Read Function for TCS3472***
 * @brief   This function reads one byte from specified register of our TCS3472 sensor
 *          
 * @param   reg: Register to read from
 *          *data: pointer which data read will be moved to
 * @return  void
 */
void TCS3472_Read(uint8_t reg, uint8_t *data);

void TCS3472_Colors(int16_t *red, int16_t *green, int16_t *blue, int16_t *clear);

void TCS3472_getId(void);

void TCS3472_sample_beads(void);

void TCS3472_sample_once_print(void);




#ifdef	__cplusplus
}
#endif

#endif	/* TCS3472_H */

