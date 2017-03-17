/*
****************************************************************************************************
*       INCLUDE FILES
****************************************************************************************************
*/

#ifdef ARDUINO_ARCH_AVR
#include <TimerOne.h>
#endif

#ifdef ARDUINO_ARCH_SAM
#include <DueTimer.h>
#endif

#include <Arduino.h>
#include "timer.h"


/*
****************************************************************************************************
*       INTERNAL MACROS
****************************************************************************************************
*/


/*
****************************************************************************************************
*       INTERNAL CONSTANTS
****************************************************************************************************
*/


/*
****************************************************************************************************
*       INTERNAL DATA TYPES
****************************************************************************************************
*/


/*
****************************************************************************************************
*       INTERNAL GLOBAL VARIABLES
****************************************************************************************************
*/

void (*g_callback)(void);


/*
****************************************************************************************************
*       INTERNAL FUNCTIONS
****************************************************************************************************
*/

static void timer1_callback(void)
{
    Timer1.stop();
    g_callback();
}


/*
****************************************************************************************************
*       GLOBAL FUNCTIONS
****************************************************************************************************
*/

void timer_init(void (*callback)(void))
{
#ifdef ARDUINO_ARCH_AVR
    Timer1.initialize();
#endif

    Timer1.attachInterrupt(timer1_callback);
    Timer1.stop();
    g_callback = callback;
}

void timer_set(uint32_t time_ms)
{
    Timer1.setPeriod(time_ms*1000);
    Timer1.start();
}

void delay_us(uint32_t time_us)
{
    delayMicroseconds(time_us);
}
