#include 'mbed.h'
#include "PinDetect.h"


//RGB Class
class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
private:
    PwmOut _redpin;
    PwmOut _greenpin;
    PwmOut _bluepin;
};
RGBLed myRGBled(p#,p#,p#); //RGB PWM pins

//Pushbuttons and DIP switches

PinDetect pb1(pin#);
PinDetect pb2(pin#);

DigitalIn sw1(pin#);
DigitalIn sw2(pin#);
DigitalIn sw3(pin#);


//Functions

void pb1_hit_callback() {
    //Increase Brightness to the color that is on
    if (myRGBled._redpin > 0.0 && myRBG._greenpin == 0.0 && myRBG._bluepin == 0.0) 
        myRGBled.write(_redpin + 0.1, 0.0, 0.0);
    else if (myRGBled._redpin == 0.0 && myRBG._greenpin > 0.0 && myRBG._bluepin == 0.0) 
        myRGBled.write(0.0, _greenpin + 0.1, 0.0);
    else if (myRGBled._redpin == 0.0 && myRBG._greenpin == 0.0 && myRBG._bluepin > 0.0) 
        myRGBled.write(0.0, 0.0, _bluepin + 0.1);
}

void pb2_hit_callback() {
    //Decrease Brightness to the color that is on 
    if (myRGBled._redpin > 0.0 && myRBG._greenpin == 0.0 && myRBG._bluepin == 0.0) 
        myRGBled.write(_redpin - 0.1, 0.0, 0.0);
    else if (myRGBled._redpin == 0.0 && myRBG._greenpin > 0.0 && myRBG._bluepin == 0.0) 
        myRGBled.write(0.0, _greenpin - 0.1, 0.0);
    else if (myRGBled._redpin == 0.0 && myRBG._greenpin == 0.0 && myRBG._bluepin > 0.0) 
        myRGBled.write(0.0, 0.0, _bluepin - 0.1);
}

void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}


int main() {
    
    pb1.mode(PullUp);
    pb2.mode(PullUp);
    
    wait(0.01);
    
    pb1.attach_deasserted(&pb1_hit_callback());
    pb2.attach_deasserted(&pb2_hit_callback());
    
    
    pb1.setSampleFrequency();
    pb1.setSampleFrequency();
    
    while(1) {
        //myled = !myled;
        wait(.5);
        
        if (sw1) {
            myRGBled.write(0.5, 0.0, 0.0);
            wait(0.01);
        }
        else if (sw2) {
            myRGBled.write(0.0, 0.5, 0.0);
            wait(0.01);
        }
        else if (sw3) {
            myRGBled.write(0.0, 0.0, 0.5);
            wait(0.01);
        }
            
            
    }
    
}