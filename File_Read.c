#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//read files and get music notes

int main()
{
    FILE* inputFile;
    char note[100][100];
    
    //opens a file and reads from that file *file must be in the same directory
    inputFile = fopen("Song_Twinkle.txt","r"); 
    if (inputFile == NULL) {
        //error check for opening file
        printf("could not open file");
        return 0;
    }

    char check;
    int j = 0;
    while (!feof(inputFile)) {
        //reads first character of the line
        check = fgetc(inputFile);
        if (check == '%')
            //skips reading the entire line
            fscanf(inputFile, "%*[^\n]");
        if (check != '%')
            //reapplies the first character to be available to read
            ungetc(check, inputFile);
        //reads the entire line and stores it in array note of element j
        fgets(note[j], 100, inputFile);
        printf("%s", note[j]);
        j++;
    }
    printf("\n");
    for (int i = 0; i < j; i++) {
        printf("%s", note[i]);
    }
    //error check for closing the file
    if (fclose(inputFile) == EOF)
        printf("File could not close");
    return 0;
}
