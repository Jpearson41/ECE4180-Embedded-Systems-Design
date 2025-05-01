#include "mbed.h"


//Sin wave created on this pin
AnalogOut aout(p18);
PwmOut myled(LED1);

int main() {
    const double pi = 3.141592653589793238462;
    const double amplitude = 0.572f;
    const double offset = 65535/2;
    double rads = 0.0;
    double sample = 0.0;
    
    while(1) {
        // sinewave output
        for (int i = 0; i < 360; i+=18) {
            rads = (pi * i) / 180.0f;
            sample = (amplitude * (offset * (cos(rads + pi))) + offset);
            myled = sample;
            aout.write_u16(sample);
            
        }
    }
}
