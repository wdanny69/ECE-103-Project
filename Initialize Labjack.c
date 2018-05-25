#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "LabJackUD.h"
#include "LJUD_DynamicLinking.h"

//initializes labjack
void Initialize_LJ (LJ_HANDLE *LJhandle)
{
    LJ_ERROR ljError;   //labjack error code

    LoadLabJackUD();

    //open first found labjack
    ljError = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, LJhandle);
    ErrorHandler(ljError, __LINE__);
    // Set all pin assignments to the factory default condition
    ljError = ePut(*LJhandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
    ErrorHandler(ljError, __LINE__);
    // Set the timer/counter pin offset to 4. This puts Timer0 on FIO4.
    ljError = ePut(*LJhandle,LJ_ioPUT_CONFIG,LJ_chTIMER_COUNTER_PIN_OFFSET,4,0);
    ErrorHandler(ljError, __LINE__);
    // Enable one timer. It will use FIO4
    ljError = ePut(*LJhandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1,0);
    ErrorHandler(ljError, __LINE__);
    // Configure Timer0 as Frequency Output (square wave)
    ljError = ePut(*LJhandle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmFREQOUT, 0);
    ErrorHandler(ljError, __LINE__);
}