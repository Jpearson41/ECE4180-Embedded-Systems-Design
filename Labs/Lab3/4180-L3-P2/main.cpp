#include "mbed.h"
#include "ultrasonic.h"
 
 void dist(int distance)
{
    //put code here to execute when the distance has changed
    printf("Distance %d mm\r\n", distance);
}
 
ultrasonic mu(p15, p16, .1, 1, &dist);    //Set the trigger pin to p5 and the echo pin to p6
                                        //have updates every .1 seconds and a timeout after 1
                                        //second, and call dist when the distance changes
 
int main()
{
    mu.startUpdates();//start measuring the distance
    while(1)
    {
        //Do something else here
        mu.checkDistance();     //call checkDistance() as much as possible, as this is where
                                //the class checks if dist needs to be called.
    }
}