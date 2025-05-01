#include 'mbed.h'
#include "PinDetect.h"

PwmOut myled(LED1);

PinDetect pb1();
PinDetect pb2();


void pb1_hit_callback() {
    //Increase Brightness
    if (myled < 1.0) 
        myled += 0.1;
}

void pb2_hit_callback() {
    //Decrease Brightness
    if (myled > 0)
        myled -= 0.1;
    
}

int main() {
    
    myled =  0.5;
    
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    
    wait(0.01);
    
    pb1.attach_deasserted(&pb1_hit_callback());
    pb2.attach_deasserted(&pb2_hit_callback());
    
    pb1.setSampleFrequency();
    pb1.setSampleFrequency();
    
    while(1) {
        wait(.5);
    }
    
}