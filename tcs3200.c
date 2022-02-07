
#include "tcs3200.h"
#include "timer1.h"

void sensor_init(){
    // TCS3200 Frequency Scale (12KHz)
    //2%
    //LATAbits.LATA0 = 0; //S0
    //LATAbits.LATA1 = 1; //S1
    //20%
    LATAbits.LATA0 = 1; //S0
    LATAbits.LATA1 = 0; //S1
    //Enable the module
    LATBbits.LATB1 = 0;
       __delay_ms(3000);
}

void filter_red(void)
{
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 0;
}

void filter_blue(void)
{
    LATAbits.LATA2 = 0;
    LATAbits.LATA3 = 1;    
}

void filter_green(void)
{
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 1;    
}

void filter_clear(void)
{
    LATAbits.LATA2 = 1;
    LATAbits.LATA3 = 0;
}

uint16_t sample_reading(void)
{
    // Wait for the falling edge
    while(!PORTBbits.RB0);

    // Wait for the rising edge
    while(PORTBbits.RB0);

    // Now wait for the falling edge
    while(!PORTBbits.RB0);

    // Now that we are sure of where we are, start counting!
    Timer1_Write(0x0000);
    Timer1_Start();

    // Wait for the rising edge
    while(PORTBbits.RB0);
    Timer1_Stop();
    return Timer1_Read();
}
