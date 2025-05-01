#include 'mbed.h'

PwmOut myMotor(p23);

int main() {
    myMotor = 0.0;
    
    while(1) {
        if (myMotor < 1) {
            myMotor += 0.05;
            wait(.5);
        }
    }
    
}