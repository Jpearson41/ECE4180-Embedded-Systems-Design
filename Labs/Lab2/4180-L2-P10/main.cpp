// Sweep the motor speed from full-speed reverse (-1.0) to full speed forwards (1.0)

#include "mbed.h"
#include "Motor.h"

Motor m(p22, p6, p5); // pwm, fwd, rev
AnalogIn myPot(p20);

int main() {
    float scale;
    while (1) {
         //Forward
        if (myPot > 0.5) {
            scale = myPot;
            m.speed(scale); 
            wait(0.02);
        //Reverse
        } else if (myPot < 0.5) {
            scale = myPot - 1.0;
            m.speed(scale); 
            wait(0.02);
        //Off
        } else {
            scale = 0;
            m.speed(scale);
            wait(0.02);
        }
        /*m.speed(1.0);
        wait(.5);
        m.speed(0.0);
        wait(.5);
        m.speed(-1.0);
        wait(.5);*/
    }
}
