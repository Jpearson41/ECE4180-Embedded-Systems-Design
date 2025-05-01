#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalOut myled(LED1);

int main() 
{
    myled = 0;

    while (1) {
        pc.putc(pc.getc());
        myled = !myled;
    }
}