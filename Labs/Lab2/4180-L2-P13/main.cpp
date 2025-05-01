#include "mbed.h"
#include "SDFileSystem.h"
#include "uLCD_4DGL.h"
#include <string>
 
SDFileSystem sd(p5, p6, p7, p8, "sd"); // the pinout on the mbed Cool Components workshop board
uLCD_4DGL uLCD(p9, p10, p11); // serial tx, serial rx, reset pin;
 
int main() {
    string inputString;
    
    printf("Hello World making file!\n");   
    //Create dir
    mkdir("/sd/mydir", 0777);
    //Create file for directory
    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
    if(fp == NULL) {
        error("Could not open file for write\n");
    }
    //Write to file
    fprintf(fp, "Hello fun SD Card World!");
    fclose(fp); 

    printf("Hello World closing file!\n"); 

    //Read contents of file
    uLCD.printf("Content of sdtest.txt is: \n");
    FILE *fp1 = fopen("/sd/mydir/sdtest.txt", "r");
    if(fp1 == NULL) {
        uLCD.printf("Error Open \n");
    }
    else
    {
        while (fscanf(fp1,"%s", inputString)!= EOF) //reads in a string delineated by white space
        {
            uLCD.printf("%s ", inputString.c_str());
        }
    }
    fclose(fp);
}

