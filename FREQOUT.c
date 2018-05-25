#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "LabJackUD.h"
#include "LJUD_DynamicLinking.h"

// ErrorHandler code was written by the LabJack company
void ErrorHandler (LJ_ERROR ljError, long lngLineNumber)
{
    char err[255];
    if (ljError != LJE_NOERROR) {
        ErrorToString(ljError, err);
        printf("Error # %ld: %s\n", ljError, err);
        printf("Source line number = %ld\n", lngLineNumber);
        if(ljError > LJE_MIN_GROUP_ERROR){
            getchar();
            exit(0); // Quit if serious error
        }
    }
}

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

//provides the labjack an output frequency and plays for a certain duration
void FREQOUT (LJ_HANDLE ljHandle, int Clock_Divisor, int Timer_Value, int duration)
{
    LJ_ERROR ljError;   //labjack error code

    ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc4MHZ_DIV, 0);
    ErrorHandler(ljError, __LINE__);
    ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, Clock_Divisor, 0);
    ErrorHandler(ljError, __LINE__);
    ljError = ePut(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, Timer_Value, 0);
    ErrorHandler(ljError, __LINE__);

    //Sleep(1000 * duration) : duration = duration of music note , * 1000 = Sleep works in milliseconds thus multiply by 1000
    Sleep(1000*duration);

    //note buffer (if a note needs to be played multiple times, this allows it to have multiple occurrences rather than being a continuous sound)
    ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc4MHZ_DIV, 0);
    ErrorHandler(ljError, __LINE__);
    ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 1, 0);
    ErrorHandler(ljError, __LINE__);
    ljError = ePut(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 1, 0);
    ErrorHandler(ljError, __LINE__);
    Sleep(100);
}

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

int main (void)
{
    LJ_HANDLE ljHandle=0; // ID# assigned to the opened LabJack
    LJ_ERROR ljError;   //labjack error code

    Initialize_LJ(&ljHandle);

    printf("Press any key to stop the square wave output and reset the LabJack.\n");
    while (!_kbhit()) { // Repeat until user presses a key
        FREQOUT(ljHandle, 45, 101, 1);
    }
    _getch(); // Clear key buffer

    End_Program(ljHandle);

    return 0;
}
