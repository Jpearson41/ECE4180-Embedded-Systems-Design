
#include "mbed.h"
#include "Servo.h"

Servo myServo(p21);
AnalogIn myPot(p20);

int main() {
    while (1) {
        myServo = myPot;
        wait(0.1);
    }
}