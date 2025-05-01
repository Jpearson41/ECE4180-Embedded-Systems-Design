#include "mbed.h"
#include "uLCD_4DGL.h"

Serial pc(USBTX, USBRX);
uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;

int main() 
{
    uLCD.baudrate(3000000);
    while (1) {
        uLCD.putc(pc.getc());
        //pc.putc(pc.getc());
    }
}