/* 
 * File:   tcs3472.c
 * Author: Sjensi
 * 
 * Part of Bead Color Sorter
 * 
 * Created on February 16, 2022, 9:46 AM
 */

#include <xc.h>
#include <stdio.h>
#include "tcs3472.h"
#include "uart.h"
#include "I2C_MSSP1_driver.h"


void TCS3472_Init(uint8_t addr, uint8_t troubleshoot){
    tcs_addr = addr << 1;       //Save address shifted

    //Turn on auto increment
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_COMMAND);
    I2C_Write(0b10100110); //Command Reg-> Auto increment -> clear int
    I2C_Stop();

    //Control the power and ints
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_ENABLE | TCS3472_COMMAND);
    //I2C_Write(0b000XX011); //000 | AIEN int | WEN wait | 0 | AEN RGBC Enable| PON Power On 
    I2C_Write(0b00000011); //No ints
    I2C_Stop();
    
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_ATIME | TCS3472_COMMAND);
    I2C_Write(0x00); //Atime, time: 614ms and Max count 65535
    I2C_Stop();

    //Set Wait time
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_CONFIG | TCS3472_COMMAND);
    I2C_Write(0x00); //Set WLONG = 0;
    I2C_Stop();    
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_WTIME | TCS3472_COMMAND);
    I2C_Write(0x00); //Set wait time to 614ms
    I2C_Stop();

    //Set Gain 4x
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_CONTROL | TCS3472_COMMAND);
    I2C_Write(0x01); 
    I2C_Stop();
}

void TCS3472_Write(uint8_t reg, uint8_t data){
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(reg | TCS3472_COMMAND);
    I2C_Write(data);
    I2C_Stop();
}

void TCS3472_Read(uint8_t reg, uint8_t *data){
    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(reg | TCS3472_COMMAND);
    I2C_Stop();

    I2C_Start();
    I2C_Write(tcs_addr + 0x01);
    *data = I2C_Read(1);
    I2C_Stop();
}

void TCS3472_Colors(int16_t *red, int16_t *green, int16_t *blue, int16_t *clear){
    uint8_t rh, rl, gh, gl, bh, bl, ch, cl;

    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_CDATAL | TCS3472_COMMAND);

    I2C_Start();
    I2C_Write(tcs_addr + 0x01);
    cl = I2C_Read(0);
    ch = I2C_Read(0);
    rl = I2C_Read(0);
    rh = I2C_Read(0);
    gl = I2C_Read(0);
    gh = I2C_Read(0);
    bl = I2C_Read(0);
    bh = I2C_Read(1);
    I2C_Stop();

    *red = (rh << 8) | rl;
    *green = (gh << 8) | gl;
    *blue = (bh << 8) | bl;
    *clear = (ch << 8)| cl;
}

void TCS3472_getId(void){
    uint8_t read_id;
    char buff[40];

    I2C_Start();
    I2C_Write(tcs_addr);
    I2C_Write(TCS3472_ID | TCS3472_COMMAND);

    I2C_Start(); //Restart
    I2C_Write((tcs_addr | 0x01));
    read_id = I2C_Read(1);
    I2C_Stop();

    sprintf(buff, "TCS3472 address read from ID register: %d\n\r", read_id);
    uart_Write_String(buff);
}