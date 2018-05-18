/* ------------------------------------------------------------------------
 This program demonstrates frequency output (440 Hz square wave) by using
 a timer. The output on FIO4 can be viewed on an oscilloscope.
 ------------------------------------------------------------------------ */
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
if (ljError != LJE_NOERROR)
 {
 ErrorToString(ljError, err);
 printf("Error # %ld: %s\n", ljError, err);
 printf("Source line number = %ld\n", lngLineNumber);
 if(ljError > LJE_MIN_GROUP_ERROR)
 {
 getchar();
 exit(0); // Quit if serious error
 }
 }
}
int main (void)
{
 LJ_ERROR ljError; // LabJack error code
 LJ_HANDLE ljHandle=0; // ID# assigned to the opened LabJack
LoadLabJackUD(); // Load the LabJack DLL
// Open the first found LabJack U3
 ljError = OpenLabJack(LJ_dtU3, LJ_ctUSB, "1", 1, &ljHandle);
 ErrorHandler(ljError, __LINE__);
// Set all pin assignments to the factory default condition
 ljError = ePut(ljHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
 ErrorHandler(ljError, __LINE__);
// Set the timer/counter pin offset to 4. This puts Timer0 on FIO4.
 ljError = ePut(ljHandle,LJ_ioPUT_CONFIG,LJ_chTIMER_COUNTER_PIN_OFFSET,4,0);
 ErrorHandler(ljError, __LINE__);
// Enable one timer. It will use FIO4
 ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 1,0);
 ErrorHandler(ljError, __LINE__);

// Configure Timer0 as Frequency Output (square wave)
 ljError = ePut(ljHandle, LJ_ioPUT_TIMER_MODE, 0, LJ_tmFREQOUT, 0);
 ErrorHandler(ljError, __LINE__);

/* -----------------------------------------------------------------
 Desired output frequency = 440 Hz
 From the LabJack frequency table, the closest matching frequency
 is 440.044006 Hz, and there are four combinations that will work:
 Freq (Hz) Clock (Hz) Clock_Divisor Timer_Value
 440.044006, 4000000.000000, 45.000000, 101.000000
 440.044006, 4000000.000000, 101.000000, 45.000000
 440.044006, 12000000.000000, 101.000000, 135.000000
 440.044006, 12000000.000000, 135.000000, 101.000000
 Choosing the first one, these are the required settings:
 Clock = 4000000.000000 (i.e., 4 MHz)
 Clock_Divisor = 45.000000
 Timer_Value = 101.000000
 -------------------------------------------------------------- */
// Set the timer clock base to 4 MHz with divisor
 ljError =
 ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_BASE, LJ_tc4MHZ_DIV, 0);
 ErrorHandler(ljError, __LINE__);
// Set the timer clock divisor to 45
 ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chTIMER_CLOCK_DIVISOR, 45, 0);
 ErrorHandler(ljError, __LINE__);
// Set the timer value to 101
 ljError = ePut(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 101, 0);
 ErrorHandler(ljError, __LINE__);
 printf("Press any key to stop the square wave output and reset the LabJack.\n");
while (!_kbhit()) // Repeat until user presses a key
{
 ; // Do nothing
 }
 _getch(); // Clear key buffer
// Disable timer */
 ljError = ePut(ljHandle, LJ_ioPUT_CONFIG, LJ_chNUMBER_TIMERS_ENABLED, 0,0);
 ErrorHandler(ljError, __LINE__);

// Reset all pin assignments to factory default condition
 ljError = ePut(ljHandle, LJ_ioPIN_CONFIGURATION_RESET, 0, 0, 0);
 ErrorHandler(ljError, __LINE__);
return 0;
}
