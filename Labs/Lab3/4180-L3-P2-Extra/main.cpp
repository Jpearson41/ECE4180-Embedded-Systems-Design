//Theremin style demo using HC-SR04 Sonar and a speaker
// moving a hand away/towards sonar changes audio frequency
#include "mbed.h"
#include "ultrasonic.h"
 
DigitalOut audio(p25); //output to speaker amp or audio jack
DigitalOut led(LED1); 
DigitalOut led2(LED2);
 
Timeout cycle;
 
volatile int half_cycle_time = 1;
 
//two calls to this interrupt routine generates a square wave
void toggle_interrupt()
{
    if (half_cycle_time>22000) audio=0; //mute if nothing in range
    else audio = !audio; //toggle to make half a square wave
    led = !led;
    cycle.detach();
    //update time for interrupt activation -change frequency of square wave
    cycle.attach_us(&toggle_interrupt, half_cycle_time);
}
void newdist(int distance)
{
    //update frequency based on new sonar data
    led2 = !led2;
    half_cycle_time = distance<<3;
}
//HC-SR04 Sonar module
ultrasonic mu(p6, p7, .07, 1, &newdist);    
//Set the trigger pin to p6 and the echo pin to p7
//have updates every .07 seconds and a timeout after 1
//second, and call newdist when the distance changes
 
int main()
{
    audio = 0;
    led = 0;
    cycle.attach(&toggle_interrupt, half_cycle_time);
    mu.startUpdates();//start measuring the distance with the sonar
    while(1) {
        //Do something else here
        mu.checkDistance();     
        //call checkDistance() as much as possible, as this is where
        //the class checks if dist needs to be called.
    }
}