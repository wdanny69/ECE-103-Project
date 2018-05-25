#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 100
#include <Windows.h>
#include <conio.h>
#include "LabJackUD.h"
#include "LJUD_DynamicLinking.h"

// This function read the files containing the music notes
void fileRead (char fileName[], char songName[], char arrangedBy[], char musicNote[][MAXLENGTH], int* numNotes) {
    printf("Please enter the name of the music file (e.g. song.txt): ");
    scanf("%s", fileName);

    FILE* inFile = NULL;
    inFile = fopen(fileName, "r");
    if (inFile == NULL) {
        printf("ERROR: File opened unsuccessfully.\n");
        exit(0);
    }
    char blankLine[MAXLENGTH];
    fgets(songName, MAXLENGTH, inFile);
    songName[strlen(songName) - 1] = '\0';
    fgets(arrangedBy, MAXLENGTH, inFile);
    fgets(blankLine, MAXLENGTH, inFile);

    *numNotes = 0;
    for (int i = 0; i < MAXLENGTH; ++i) {
        if (fscanf(inFile, "%s", musicNote[i]) == EOF) {
            break;
        }
        *numNotes += 1;
    }

    // Close file
    if (fclose(inFile) == EOF) {
        // An error occur
        printf("File close not successful.\n");
        exit(0);
    }
}

void noteDecode (char musicNote[][MAXLENGTH], int numNotes, char key[][MAXLENGTH], int duration[]) {
    for (int i = 0; i < numNotes; ++i) {
        int parenIndex;
        parenIndex = strcspn(musicNote[i], "(");
        for (int j = 0; j < parenIndex; ++j) {
            key[i][j] = musicNote[i][j];
        }
        key[i][parenIndex] = '\0';
        char durationChar;
        durationChar = musicNote[i][parenIndex + 1];
        duration[i] = durationChar - '0';
    }
}

void noteTranslate (char key[][MAXLENGTH], int numNotes, int clockDivisor[], int timerVal[]) {
    for (int i = 0; i < numNotes; ++i) {
        if (strcmp(key[i], "C3") == 0) {
            clockDivisor[i] = 78;
            timerVal[i] = 196;
        }
        else if ((strcmp(key[i], "C#3") == 0) || (strcmp(key[i], "Db3") == 0)) {
            clockDivisor[i] = 176;
            timerVal[i] = 82;
        }
        else if (strcmp(key[i], "D3") == 0) {
            clockDivisor[i] = 60;
            timerVal[i] = 227;
        }
        else if ((strcmp(key[i], "D#3") == 0) || (strcmp(key[i], "Eb3") == 0)) {
            clockDivisor[i] = 167;
            timerVal[i] = 77;
        }
        else if (strcmp(key[i], "E3") == 0) {
            clockDivisor[i] = 164;
            timerVal[i] = 74;
        }
        else if (strcmp(key[i], "F3") == 0) {
            clockDivisor[i] = 46;
            timerVal[i] = 249;
        }
        else if ((strcmp(key[i], "F#3") == 0) || (strcmp(key[i], "Gb3") == 0)) {
            clockDivisor[i] = 46;
            timerVal[i] = 235;
        }
        else if (strcmp(key[i], "G3") == 0) {
            clockDivisor[i] = 57;
            timerVal[i] = 179;
        }
        else if ((strcmp(key[i], "G#3") == 0) || (strcmp(key[i], "Ab3") == 0)) {
            clockDivisor[i] = 43;
            timerVal[i] = 224;
        }
        else if (strcmp(key[i], "A3") == 0) {
            clockDivisor[i] = 45;
            timerVal[i] = 202;
        }
        else if ((strcmp(key[i], "A#3") == 0) || (strcmp(key[i], "Bb3") == 0)) {
            clockDivisor[i] = 39;
            timerVal[i] = 220;
        }
        else if (strcmp(key[i], "B3") == 0) {
            clockDivisor[i] = 89;
            timerVal[i] = 91;
        }
        else if (strcmp(key[i], "C4") == 0) {
            clockDivisor[i] = 39;
            timerVal[i] = 196;
        }
        else if ((strcmp(key[i], "C#4") == 0) || (strcmp(key[i], "Db4") == 0)) {
            clockDivisor[i] = 41;
            timerVal[i] = 176;
        }
        else if (strcmp(key[i], "D4") == 0) {
            clockDivisor[i] = 49;
            timerVal[i] = 139;
        }
        else if ((strcmp(key[i], "D#4") == 0) || (strcmp(key[i], "Eb4") == 0)) {
            clockDivisor[i] = 27;
            timerVal[i] = 238;
        }
        else if (strcmp(key[i], "E4") == 0) {
            clockDivisor[i] = 164;
            timerVal[i] = 37;
        }
        else if (strcmp(key[i], "F4") == 0) {
            clockDivisor[i] = 23;
            timerVal[i] = 249;
        }
        else if ((strcmp(key[i], "F#4") == 0) || (strcmp(key[i], "Gb4") == 0)) {
            clockDivisor[i] = 23;
            timerVal[i] = 235;
        }
        else if (strcmp(key[i], "G4") == 0) {
            clockDivisor[i] = 243;
            timerVal[i] = 21;
        }
        else if ((strcmp(key[i], "G#4") == 0) || (strcmp(key[i], "Ab4") == 0)) {
            clockDivisor[i] = 172;
            timerVal[i] = 28;
        }
        else if (strcmp(key[i], "A4") == 0) {
            clockDivisor[i] = 45;
            timerVal[i] = 101;
        }
        else if ((strcmp(key[i], "A#4") == 0) || (strcmp(key[i], "Bb4") == 0)) {
            clockDivisor[i] = 22;
            timerVal[i] = 195;
        }
        else if (strcmp(key[i], "B4") == 0) {
            clockDivisor[i] = 225;
            timerVal[i] = 18;
        }
        else if (strcmp(key[i], "C5") == 0) {
            clockDivisor[i] = 21;
            timerVal[i] = 182;
        }
        else if ((strcmp(key[i], "C#5") == 0) || (strcmp(key[i], "Db5") == 0)) {
            clockDivisor[i] = 164;
            timerVal[i] = 22;
        }
        else if (strcmp(key[i], "D5") == 0) {
            clockDivisor[i] = 15;
            timerVal[i] = 227;
        }
        else if ((strcmp(key[i], "D#5") == 0) || (strcmp(key[i], "Eb5") == 0)) {
            clockDivisor[i] = 17;
            timerVal[i] = 189;
        }
        else if (strcmp(key[i], "E5") == 0) {
            clockDivisor[i] = 74;
            timerVal[i] = 41;
        }
        else if (strcmp(key[i], "F5") == 0) {
            clockDivisor[i] = 179;
            timerVal[i] = 16;
        }
        else if ((strcmp(key[i], "F#5") == 0) || (strcmp(key[i], "Gb5") == 0)) {
            clockDivisor[i] = 159;
            timerVal[i] = 17;
        }
        else if (strcmp(key[i], "G5") == 0) {
            clockDivisor[i] = 23;
            timerVal[i] = 111;
        }
        else if ((strcmp(key[i], "G#5") == 0) || (strcmp(key[i], "Ab5") == 0)) {
            clockDivisor[i] = 172;
            timerVal[i] = 14;
        }
        else if (strcmp(key[i], "A5") == 0) {
            clockDivisor[i] = 16;
            timerVal[i] = 142;
        }
        else if ((strcmp(key[i], "A#5") == 0) || (strcmp(key[i], "Bb5") == 0)) {
            clockDivisor[i] = 11;
            timerVal[i] = 195;
        }
        else if (strcmp(key[i], "B5") == 0) {
            clockDivisor[i] = 225;
            timerVal[i] = 9;
        }
    }
}

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
    ljError = ePut(ljHandle, LJ_ioPUT_TIMER_VALUE, 0, 101, 0);
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
    char fileName[MAXLENGTH];
    char songName[MAXLENGTH];
    char arrangedBy[MAXLENGTH];
    char musicNote[MAXLENGTH][MAXLENGTH]; // char strName [numStr] [maxCharInOneStr]
    int numNotes;

    // Invoke function to read the song file
    fileRead (fileName, songName, arrangedBy, musicNote, &numNotes);
    LJ_HANDLE ljHandle=0; // ID# assigned to the opened LabJack
    LJ_ERROR ljError;   //labjack error code

    char key[numNotes][MAXLENGTH];
    int duration[numNotes];

    // Invoke function to decode the note arrays into the music key array and the duration array
    noteDecode (musicNote, numNotes, key, duration);

    int clockDivisor[numNotes];
    int timerVal[numNotes];

    noteTranslate (key, numNotes, clockDivisor, timerVal);
    Initialize_LJ(&ljHandle);

    printf("Press any key to stop the square wave output and reset the LabJack.\n");
    for (int i = 0; i < numNotes; i++) { // Repeat until user presses a key
        FREQOUT(ljHandle, clockDivisor[i], timerVal[i], duration[i]);
        if (_kbhit()) {//stop music at any time
            break;
        }
    }
    _getch(); //clear key buffer

    End_Program(ljHandle);

    return 0;
}
