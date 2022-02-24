/* 
 * File:   litaflokkari.c
 * Author: Sjensi
 * 
 * Contains functions used by the color sorting machine
 * 
 * Created on February 8, 2022, 11:34 AM
 */

#include <xc.h>
#include <stdio.h>
#include "I2C_MSSP1_driver.h"
#include "PCA9685_driver.h"
#include "litaflokkari.h"
#include "tcs3200.h"
#include "LCD.h"
#include "uart.h"

void PCA_Servo_Command(uint8_t servo_nr, uint8_t servo_on_off){
    uint8_t stateTest = servo_on_off;
    if(stateTest == 0){
        PCA_Write(servo_nr, 0x0, LFSMIN);
    }
    
    if(stateTest == 1){
        PCA_Write(servo_nr, 0x0, LFSMAX);
    }
    
    else{
        LATBbits.LATB2 = ~LATBbits.LATB2;
        __delay_ms(50);
    }

    return;
}

void PCA_Servo_Pos(uint8_t pos){
    switch(pos){
        case 1:     //001
        //Yellow
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 1);
        break;

        case 2:     //010
        //Red
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 0);
        break;

        case 3:     //011
        //Green
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 1);
        break;
    
        case 4:     //100
        //Blue
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 0);
        break;

        case 5:     //101
        //Black
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 1);
        break;

        case 6:     //110
        //White
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 0);
        break;

        case 7:     //111
        //Brown
        PCA_Servo_Command(0, 1);
        PCA_Servo_Command(1, 1);
        PCA_Servo_Command(2, 1);        
        break;
        
        default:  //000
        //Unsorted
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 0);
        break;
    }
}

void print_welcome_message(void){
    
    LCD_Set_Cursor(1,1);
    LCD_write_string("Beads Color Sorter 2^3");
    LCD_Set_Cursor(2,1);
    LCD_write_string("Group : B");
    __delay_ms(5000);
}

//For tcs3200
void find_raw_color(uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *clear){
    /*Sample the red filter*/
    filter_red();
    __delay_ms(10);
    *red = sample_reading();
    
    /*Sample the green filter*/
    filter_green();
    __delay_ms(10);
    *green = sample_reading();
    
    /*Sample the blue filter*/
    filter_blue();
    __delay_ms(10);
    *blue = sample_reading();
    
    /*Sample the clear filter*/
    filter_clear();
    __delay_ms(10);
    *clear = sample_reading();
}

uint8_t find_color(){
    //Variables to store value from sensor for each filter
    uint16_t red, green, blue, clear;
    
    /*Sample the red filter*/
    filter_red();
    __delay_ms(10);
    red = sample_reading();
    
    /*Sample the green filter*/
    filter_green();
    __delay_ms(10);
    green = sample_reading();
    
    /*Sample the blue filter*/
    filter_blue();
    __delay_ms(10);
    blue = sample_reading();
    
    /*Sample the clear filter*/
    filter_clear();
    __delay_ms(10);
    clear = sample_reading();
    
    //Return the correct color code 0 - 1
    return (color_compare_return(red, green, blue, clear));
}

uint8_t color_compare_return(uint16_t red, uint16_t green, uint16_t blue, uint16_t clear){
    //cVal is used to determine what catagory the pearl falls into
    uint8_t cVal = 0;
    uint16_t a, b, c, d;
    
    //if color samples match value range for yellow bead 
    a = (red-YELLOW_RED_MIN)*(red-YELLOW_RED_MAX);
    b = (green-YELLOW_GREEN_MIN)*(green-YELLOW_GREEN_MAX);
    c = (blue-YELLOW_BLUE_MIN)*(blue-YELLOW_BLUE_MAX);
    d = (clear-YELLOW_CLEAR_MIN)*(blue-YELLOW_CLEAR_MAX); 
    if(a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 1;    
        yellow_bead++;
        return cVal;
    }
    
    //If color samples match value range for red bead
    a = (red-RED_RED_MIN)*(red-RED_RED_MAX);
    b = (green-RED_GREEN_MIN)*(green-RED_GREEN_MAX);
    c = (blue-RED_BLUE_MIN)*(blue-RED_BLUE_MAX);
    d = (clear-RED_CLEAR_MIN)*(blue-RED_CLEAR_MAX);
    if( a <= 0 && b <= 0 && c <= 0 &&  d <= 0){
        cVal = 2;     
        red_bead++;
        return cVal;
    }
    
    //If color samples match value range for green bead
    a = (red-GREEN_RED_MIN)*(red-GREEN_RED_MAX);
    b = (green-GREEN_GREEN_MIN)*(green-GREEN_GREEN_MAX);
    c = (blue-GREEN_BLUE_MIN)*(blue-GREEN_BLUE_MAX) ;
    d = (clear-GREEN_CLEAR_MIN)*(blue-GREEN_CLEAR_MAX);
    if(a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 3;   
        green_bead++;
        return cVal;
    }
    
    //If color samples match value range for blue bead
    a =(red-BLUE_RED_MIN)*(red-BLUE_RED_MAX);
    b =(green-BLUE_GREEN_MIN)*(green-BLUE_GREEN_MAX);
    c =(blue-BLUE_BLUE_MIN)*(blue-BLUE_BLUE_MAX);
    d =(clear-BLUE_CLEAR_MIN)*(blue-BLUE_CLEAR_MAX) ;
    if( a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 4;    
        blue_bead++;
        return cVal;
    }
    
    //If color samples match value range for black bead
    a =(red-BLACK_RED_MIN)*(red-BLACK_RED_MAX);
    b =(green-BLACK_GREEN_MIN)*(green-BLACK_GREEN_MAX);
    c =(blue-BLACK_BLUE_MIN)*(blue-BLACK_BLUE_MAX);
    d =(clear-BLACK_CLEAR_MIN)*(blue-BLACK_CLEAR_MAX);
    if( a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 5;       
        black_bead++;
        return cVal;
    }
    
    //If color samples match value range for ORANGE bead
    a =(red-ORANGE_RED_MIN)*(red-ORANGE_RED_MAX);
    b =(green-ORANGE_GREEN_MIN)*(green-ORANGE_GREEN_MAX);
    c = (blue-ORANGE_GREEN_MIN)*(blue-ORANGE_BLUE_MAX) ;
    d =(clear-ORANGE_CLEAR_MIN)*(blue-ORANGE_CLEAR_MAX);
    if(a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 6;      
        white_bead++;
        return cVal;
    }
    
    //If color samples match value range for ORANGE bead
    a =(red-PURPLE_RED_MIN)*(red-PURPLE_RED_MAX) ;
    b =(green-PURPLE_GREEN_MIN)*(green-PURPLE_GREEN_MAX) ;
    c =(blue-PURPLE_BLUE_MIN)*(blue-PURPLE_BLUE_MAX);
    d =(clear-PURPLE_CLEAR_MIN)*(blue-PURPLE_CLEAR_MAX);
    if(a <= 0 && b <= 0 && c <= 0 && d <= 0){
        cVal = 7;      
        brown_bead++;
        return cVal;
    }
    else{
        cVal = 0;
        unsort_bead++;
        return cVal;
    }
}

void print_color_quantity(){
    char strbuff[40];
    LCD_Set_Cursor(1,1);
    sprintf(strbuff, "Y%d R%d G%d BE%d", yellow_bead, red_bead, green_bead, blue_bead);
    LCD_write_string(strbuff);
    LCD_Set_Cursor(2,1);
    sprintf(strbuff, "BK%d W%d BN%d U%d", black_bead, white_bead, brown_bead, unsort_bead);
    LCD_write_string(strbuff);
}

void calibrate_bead_values(void){
    //Yellow
    uart_Write_String("Measure 10 pieces Yellow Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    
    //Red
    uart_Write_String("Measure 10 pieces Red Bead now: \n\r");
    for(int i = 0; i < 10; i++){

    }
    //Green
    uart_Write_String("Measure 10 pieces Green Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //Blue
    uart_Write_String("Measure 10 pieces Blue Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //Black
    uart_Write_String("Measure 10 pieces Black Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //White
    uart_Write_String("Measure 10 pieces White Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //Purple
    uart_Write_String("Measure 10 pieces Purple Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //Pink
    uart_Write_String("Measure 10 pieces Pink Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();
    }
    //Orange
    uart_Write_String("Measure 10 pieces Orange Bead now: \n\r");
    for(int i = 0; i < 10; i++){
        find_print();   
    }
    
}

void find_print(void){
    //Values for colors
    uint16_t red, green, blue, clear;
    //Buffer for printing to uart
    char buffer[50];
    
        find_raw_color(&red, &green, &blue, &clear);
        sprintf(buffer, "%d\t", red);
        uart_Write_String(buffer);
        sprintf(buffer, "%d\t", green);
        uart_Write_String(buffer);
        sprintf(buffer, "%d\t", blue);
        uart_Write_String(buffer);
        sprintf(buffer, "%d\n\r", clear);
        uart_Write_String(buffer);
}

void slide_to_mid(void){
    uint16_t shake1 = RAILMID + 10;
    uint16_t shake2 = RAILMID - 10;
    
    PCA_Write(0, 0, RAILMID); //Go to center
    __delay_ms(100);
    
    PCA_Write(0, 0, shake1); //Do some shake
    __delay_ms(100);
    PCA_Write(0, 0, shake2); 
    __delay_ms(100);
    
    PCA_Write(0, 0, RAILMID);
    __delay_ms(100);
}


