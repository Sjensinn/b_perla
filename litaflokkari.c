/* 
 * File:   litaflokkari.c
 * Author: Sjensi
 * 
 * Contains functions used by the color sorting machine
 * 
 * Created on February 8, 2022, 11:34 AM
 */

#include "litaflokkari.h"


void PCA_Servo_Command(uint8_t n, uint8_t pos){
    uint8_t offval, onval;
    offval = (4095 - SERVOMIN) - pos(SERVOMAX-SERVOMIN);  //for the off value
    onval = SERVOMIN + pos(SERVOMAX - SERVOMIN);   //For the on value 

    PCA_Write(n, onval, offval);
    return;
}

void PCA_Servo_Pos(uint8_t pos){
    switch(pos){
        case 0:     //000
        //Unsorted
        PCA_Servo_Command(0, 0);
        PCA_Servo_Command(1, 0);
        PCA_Servo_Command(2, 0);
        break;

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
    }
}