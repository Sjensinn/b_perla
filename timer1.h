/* 
 * File:   timer1.h
 * Author: Sjensi
 *
 * Created on February 4, 2022, 8:32 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief This API initializes the Timer module.
 *        This routine must be called before any other Timer routines.
 * @param void.
 * @return void.
 *
 * @code
 * void main(void)
 * {
 *     Timer1_Initialize();
 *     
 *     while(1)
 *     {   
 *         Timer1_Tasks();
 *     }
 * }
 * @endcode
 */
void Timer1_Initialize(void);

/**
 * @brief This function starts Timer
 *        Timer-0 should be initialized with Timer1_Initialize() before calling this API.
 * @param void.
 * @return void.
 *
 * @code
 * void main(void)
 * {
 *     Timer1_Initialize();
 *     
 *     //Start timer if it is not already started
 *     Timer1_Start();
 *     
 *     while(1)
 *     {
 *         Timer1_Tasks();
 *     }
 * }
 * @endcode
 */
void Timer1_Start(void);

/**
 * @brief This function stops Timer
 *        Timer-0 should be initialized with Timer1_Initialize() before calling this API.
 * @param void.
 * @return void.
 *
 * @code
 * void customAppCallback(void)
 * {
 *     static uint8_t counter;
 *     if(counter++ == 10)
 *     {
 *         counter = 0;
 *         //Stop timer after 10 timeouts
 *         Timer1_Stop();
 *     }
 * }
 * void main(void)
 * {
 *     Timer1_Initialize();
 *     //Start timer if it is not already started
 *     Timer1_Start();
 *     
 *     while(1)
 *     {
 *         Timer1_Tasks();
 *     }
 * }
 * @endcode
 */
void Timer1_Stop(void);

/**
 * @brief This function reads the 16-bits from TMR1 register.
 *        Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param void.
 * @return 16-bit data from TMR1 register.
 *
 * @code
 * void main(void)
 * {
 *     Timer1_Initialize();
 *     
 *     //Start timer if it is not already started
 *     Timer1_Start();
 *     
 *     while(1)
 *     {
 *         if(Timer1_Read() == 0x8000)
 *         {
 *             //do something
 *         }
 *     }
 * }
 * @endcode
 */
uint16_t Timer1_Read(void);

/**
 * @brief This function writes 16-bit value to TMR1 register.
 *        Timer should be initialized with Timer1_Initialize() before calling this API.
 * @param 16-bit value to be written to TMR1 register.
 * @return void.
 *
 * @code
 * void main(void)
 * {
 *     Timer1_Initialize();
 *     //Start timer if it is not already started
 *     Timer1_Start();
 *     
 *     while(1)
 *     {
 *         if(Timer1_Read() == 0x0)
 *         {
 *             Timer1_Write(0x8000)
 *         }
 *     }
 * }
 * @endcode
 */
void Timer1_Write(size_t timerVal);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

