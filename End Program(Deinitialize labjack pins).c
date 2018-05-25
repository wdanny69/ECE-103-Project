#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "LabJackUD.h"
#include "LJUD_DynamicLinking.h"

//resets labjack to default conditions
void End_Program(LJ_HANDLE ljHandle)
{
    LJ_ERROR ljError;   //labjack error code

    // Disable timer */
    ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 0,0);
    ErrorHandler(ljError, __LINE__);

    // Reset all pin assignments to factory default condition
    ljError = ePut(ljHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
    ErrorHandler(ljError, __LINE__);
}