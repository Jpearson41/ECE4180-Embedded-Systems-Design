#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn pb1(pin#);

int main() {
    pb1.mode(PullUp);
    while(1)
        myled = pb1;
}
