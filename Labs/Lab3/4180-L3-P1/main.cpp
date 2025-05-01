#include "mbed.h"
#include "Servo.h"
PwmOut ledf(LED1); //throttle up test led with PWM dimming
PwmOut ledr(LED2); //throttle down test led with PWM dimming
 
Servo myservo(p21);
 
int main()
{
    myservo = 0.0;
    ledf = ledr = 1;
    wait(0.5); //detects signal
//Required ESC Calibration/Arming sequence  
//sends longest and shortest PWM pulse to learn and arm at power on
    myservo = 1.0; //send longest PWM
    ledf = ledr = 0;
    wait(8);
    myservo = 0.0; //send shortest PWM
    wait(8);
//ESC now operational using standard servo PWM signals
    while (1) {
        for (float p=0.0; p<=0.3; p += 0.025) { //throttle up slowly to full throttle
            myservo = p;
            ledf = p;
            wait(1.0);
        }
        myservo = 0.0; //Motor off
        ledf = ledr = 0;
        wait(4.0);
        for (float p=0.3; p>=0.0; p -= 0.025) { //Throttle down slowly from full throttle
            myservo = p;
            ledr = p;
            wait(1.0);
        }
        myservo = 0.0; //Motor off
        ledf = ledr = 0;
        wait(4.0);
    }
}