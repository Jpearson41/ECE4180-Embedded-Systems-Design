#include "mbed.h"
#include "Motor.h"
#include "uLCD_4DGL.h"
//#include "SDFileSystem.h"
//#include "wave_player.h"
#include "ultrasonic.h"      //ultrasonic sensor

//Machine States & Other

#define INTERACT 0
#define CALCULATE 1
#define FREEMODE 2
#define FALSE 0
#define TRUE 1

//Function Prototypes
//Bluetooth related Funcs
void metricCalc();
void waitButtonHit();
//Movement related Funcs  
void moveForward();
void moveBackward();
void turnLeft();
void turnAround();
//void returnHome(int vertNorth, int vertSouth, int horiRight, int horiLeft);
//Area related Func
double calcArea();
void distanceAttach(int sonarDist);                                 
//End of Function Prototypes

//IO Devies and such 
Serial pc(USBTX,USBRX);     //serial debugging
Serial bluemod(p13,p14);    //bluetooth controller

//SDFileSystem sd(p5, p6, p7, p8, "sd"); //SD card
//AnalogOut DACout(p18);     //speaker setup
//wave_player waver(&DACout);

uLCD_4DGL uLCD(p9,p10,p11); // serial tx, serial rx, reset pin;
ultrasonic ourSonar(p15, p16, .1, 1, &distanceAttach);    //ultrasonic sensor, trigger-echo-update-timeout

PwmOut left_led(LED3);      // PWM output for left robot direction signal
PwmOut right_led(LED4);     // PWM output for right robot direction signal
PwmOut forward_led(LED1);   // PWM output for forward robot direction signal
PwmOut reverse_led(LED2);   // PWM output for reverse robot direction signal
                                        

Motor left(p21, p29, p30); //left motor
Motor right(p22,p23,p24);  //right motor

int gameState = 0;           //state of program
int forwardDistance = 366;   //Distance robot moves when going forward
int lengthRobot = 200;       //length of robot(mm)
int currentDistance = 0;
int metricFlag = 0;         //flag for metric: 2->mm, 3->cm, 4->ft



//Main Loop                                        
int main() {
    double areaCalc; //area calculation
    //FILE *wave_file; //wave file for speaker
    bool calculated = FALSE; //Calculated flag
    uLCD.cls();
    //Turn on SonarSensor
    ourSonar.startUpdates();
    while (1) {
        switch (gameState) {
            case INTERACT:
                if (calculated) {
                    //Play audio file 
                    //pc.printf("Inside of INTERACT state after calculation\n");
                    uLCD.cls();
                    uLCD.locate (1,1);
                    uLCD.text_width(2); 
                    uLCD.text_height(2);
                    uLCD.printf("Entering\nFree mode\n Control\n through\n BT!");
                    //Play audio file 
                    /*wave_file=fopen("/sd/enterFree.wav","r");
                    waver.play(wave_file);
                    fclose(wave_file);*/
                    gameState = FREEMODE;
                    //pc.printf("Leaving INTERACT state after calculation\n");
                }else {
                    //pc.printf("Inside of INTERACT state hello\n");
                    //Play audio file 
                    /*wave_file=fopen("/sd/HelloFile.wav","r");
                    waver.play(wave_file);
                    fclose(wave_file);*/
                    //Choose which metric to compute Area in
                    uLCD.locate(1,1);
                    uLCD.text_height(2);
                    uLCD.text_width(2);
                    uLCD.printf("Metric:\n Button2-mm^2\n Button3-cm^2\n Button4-ft^2\n");
                    metricCalc();
                    //Wait for bluetooth button 1 hit to enter CALCULATE
                    //Only leave once b1 is hit, changes gameState to CALCULATE
                    uLCD.cls();
                    uLCD.locate(1,1);
                    uLCD.text_height(2);
                    uLCD.text_width(2);
                    uLCD.printf("Click\nbutton 1\n to \ncalculate\n");
                    //Play audio file 
                    //wave_file=fopen("/sd/calcFile.wav","r");
                    //waver.play(wave_file);
                    //fclose(wave_file);
                    waitButtonHit();
                    //gameState = CALCULATE;
                    //pc.printf("Leaving INTERACT state hello\n");
                    
                }
                break;
                
            case CALCULATE:
                uLCD.cls();
                uLCD.text_width(2);
                uLCD.text_height(2);
                uLCD.printf("   Calcu \n  lating\n");
                areaCalc = calcArea();
                uLCD.cls();
                calculated = TRUE;
                //Play audio file 
                //wave_file=fopen("/sd/calcComp.wav","r");
                //waver.play(wave_file);
                //fclose(wave_file);
                //Print out area
                //pc.printf("Here is the calculated area: %.2f\n", areaCalc);
                if (metricFlag == 2) { //Area in MM
                    uLCD.locate(1,1);
                    uLCD.text_width(1); 
                    uLCD.text_height(1);
                    uLCD.color(RED);
                    uLCD.printf("Calculated Area: %5.2f mm^2\n", areaCalc);
                } else if (metricFlag == 3) { //Area in CM
                    uLCD.locate(1,1);
                    uLCD.text_width(1);
                    uLCD.text_height(1);
                    uLCD.color(RED);
                    uLCD.printf("Calculated Area: %.2f cm^2\n", areaCalc);
                } else if (metricFlag == 4) { //Area in ft
                    uLCD.locate(1,1);
                    uLCD.text_width(1);
                    uLCD.text_height(1);
                    uLCD.color(RED);
                    uLCD.printf("Calculated Area: %.2f ft^2\n", areaCalc);
                }
                //Switch gameState
                wait(15);
                gameState = INTERACT;
                pc.printf("Leaving CALCULATE mode\n");
                pc.printf("areacalc %d\n", areaCalc);
                break;
                
            case FREEMODE:
                //pc.printf("In FREEMODE via bluetooth\n");
                char bnum, bhit; //Button char holders
                while (1) {
                   if (bluemod.getc() == '!') {
                       if (bluemod.getc() == 'B') {
                            bnum = bluemod.getc(); //button number
                            bhit = bluemod.getc(); //1=hit, 0=release
                            switch (bnum) {
                                case '6': //button 6 up arrow
                                    if (bhit=='1') {
                                        //forward                            
                                        //hit button
                                        forward_led=1;  //Set forward LED on MBED
                                        left.speed(1.0);
                                        right.speed(1.0);
                                    } else {
                                        //Let go of button
                                        forward_led = 0;    //Turn off forward LED
                                        left.speed(0.0);
                                        right.speed(0.0);
                                    }
                                    break;
                                case '5': //button 5 down arrow
                                    if (bhit=='1') {
                                        //reverse
                                        //hit button
                                        reverse_led=1;  //Turn reverse LED on
                                        left.speed(-1.0);
                                        right.speed(-1.0);        
                                    } else {
                                        //let go of button
                                        reverse_led=0;  //Turn reverse LED off
                                        left.speed(0.0);
                                        right.speed(0.0);
                                    }
                                    break;
                                case '7': //button 7 left arrow
                                    if (bhit=='1') {
                                        //ccw
                                        //hit button
                                        left_led=1;      //Turn left LED on
                                        left.speed(1.0);
                                        right.speed(-1.0);
                                    } else {
                                        //let go of button
                                        left_led=0;     //Turn left LED off
                                        left.speed(0.0);
                                        right.speed(0.0);
                                    }
                                    break;
                                case '8': //button 8 right arrow
                                    if (bhit=='1') {
                                        //cw
                                        //hit button
                                        right_led=1;    //Turn right LED on
                                        left.speed(-1.0);
                                        right.speed(1.0);
                                    } else {
                                        //let go of button
                                        right_led=0;    //Turn right LED off
                                        left.speed(0.0);
                                        right.speed(0.0);
                                    }
                                    break;
                            }//end first switch
                        }//end B if
                    } //end ! if
                } //end while    
        }//end switch
    }//end while
}//end func

//Calculate Area function
double calcArea() {
    double area;
    int leftDistance, rightDistance;
    int northDistance, southDistance;
    int vertCalc, horiCalc;
    int vertNorthTimesForward = 0;
    int vertSouthTimesForward = 0;
    int horiRightTimesForward = 0;
    int horiLeftTimesForward = 0;
    
    
    //Calculate Vertical Measurement
    while (1) {   
        for (int i = 0; i < 100; i++) {
            ourSonar.checkDistance();
        }
        pc.printf("currentDistance1: %d\n", currentDistance);
        //If out of range(20ft), move till in range
        if (currentDistance > 6100) {
            moveForward();
            vertNorthTimesForward ++;
            wait(2);
            continue;
        } else {
            northDistance = currentDistance;
            break;
        }    
    }
    ////Turn Robot around for South Measurement
    pc.printf("northdistance: %d\n", northDistance);
    wait(5);
    turnAround();
    ///////////////////////
    
    while (1) {
        for (int i = 0; i < 100; i++) {
            ourSonar.checkDistance();
        }
        pc.printf("currentDistance2: %d\n", currentDistance);
        //If out of range(20ft), move till in range
        if (currentDistance > 6100) {
            moveForward();
            vertSouthTimesForward++;
            wait(2);
            continue;
        } else {
            southDistance = currentDistance + (vertSouthTimesForward * forwardDistance);
            break;
        }
    }  
    
    pc.printf("southdistance: %d\n", southDistance);
    //Calculate vertDistance!!
    vertCalc = northDistance + southDistance + lengthRobot;
    pc.printf("vertCalc %d\n", vertCalc);
    //return to initial spot
    int differenceVert = vertNorthTimesForward - vertSouthTimesForward;
    if (differenceVert < 0) {
        for (int i = differenceVert; i < 0; i++) {
            moveBackward();
            wait(1);
        }
    }else {
        for (int i = 0; i < differenceVert; i++) {
            moveForward();
            wait(1);
        }
    }
    
    //Turn Robot for Horizontal Measurement
    wait(5);
    turnLeft();
    ///////////////////////
    //Calculate Horizontal Measurement;
     while (1) {   
        for (int i = 0; i < 100; i++) {
            ourSonar.checkDistance();
        }
        pc.printf("currentDistance3: %d\n", currentDistance);
        //If out of range(20ft), move till in range
        if (currentDistance > 6100) {
            moveForward();
            horiRightTimesForward ++;
            wait(2);
            continue;
        } else {
            rightDistance = currentDistance;
            break;
        }    
    }
    ////Turn Robot around for left Measurement
    pc.printf("rightdistance: %d\n", rightDistance);
    wait(5);
    turnAround();
    ///////////////////////
    
    while (1) {
        for (int i = 0; i < 100; i++) {
            ourSonar.checkDistance();
        }
        pc.printf("currentDistance4: %d\n", currentDistance);
        //If out of range(20ft), move till in range
        if (currentDistance > 6100) {
            moveForward();
            wait(2);
            horiLeftTimesForward++;
            continue;
        } else {
            leftDistance = currentDistance + (horiLeftTimesForward * forwardDistance);
            break;
        }
    }  
    
    //Calculate horiDistance!!
    pc.printf("leftDistance: %d\n", leftDistance);
    horiCalc = leftDistance + rightDistance + lengthRobot;   
    pc.printf("Horicalc %d\n", horiCalc);
    
    //return to home position
    int differenceHori = horiRightTimesForward - horiLeftTimesForward;
    if (differenceHori < 0) {
        for (int i = differenceHori; i < 0; i++) {
            moveBackward();
            wait(1);
        }
    } else {
        for (int i = 0; i < differenceHori; i++) {
            moveForward();
            wait(1);
        }
    }
    //Turn off sensor
    ourSonar.pauseUpdates();
    
    //return calculated Area in correct metric
    if (metricFlag == 2) //area in MM
        area = vertCalc * horiCalc;
    else if (metricFlag == 3) //area in CM
        area = (vertCalc/10) * (horiCalc/10);
    else if (metricFlag == 4) //area in FT
        area = (vertCalc/304.8) * (horiCalc/304.8);
    return area;                 
}                

void distanceAttach(int sonarDist) {
    //pc.printf("Inside of distanceAttach\n\n\n");
    currentDistance = sonarDist;  
    //pc.printf("Inside of distanceAttach\n\n\n");
}         
//End of Area Functions

//Movement Functions
void moveForward() {
    left.speed(-0.5);
    right.speed(-0.56);
    wait_ms(1150);
    left.speed(0.0);
    right.speed(0.0);
}

void moveBackward() {
    left.speed(0.5);
    right.speed(0.56);
    wait_ms(1150);
    left.speed(0.0);
    right.speed(0.0);
}

void turnLeft() {
    left.speed(0.4);
    right.speed(-0.4);
    wait_ms(1100);
    left.speed(0.0);
    right.speed(0.0);
}

void turnAround() {
    turnLeft();
    wait(2);
    turnLeft();                     
                                        
}
//End of Movement Functions

//Bluetooth Functions
void metricCalc(void) {
    char bnum, bhit; //Button char holders
    pc.printf("Inside of metricCalcFunc");
    while (metricFlag == 0) {
        if (bluemod.getc() == '!') {
            if (bluemod.getc() == 'B') {
                bnum = bluemod.getc();
                bhit = bluemod.getc();
                switch (bnum) {
                    case '2':  //Button 2 -> mm
                        if (bhit)
                            metricFlag = 2;
                            break;
                    case '3':  //Button 3 -> cm
                        if (bhit)
                            metricFlag = 3;
                            break;
                    case '4':  //Button 4-> in
                        if (bhit)
                            metricFlag = 4;
                            break;
                }
            }
        }
    }
    pc.printf("Leaving metricCalcFunc");  
}

void waitButtonHit(void) {
    pc.printf("Inside of waitButtonHitFunc");
    while (gameState != CALCULATE) {
        if (bluemod.getc() == '!') {
            if (bluemod.getc() == 'B') {
                if (bluemod.getc() == '1') {
                    if (bluemod.getc() == '1') {
                        gameState = CALCULATE;
                    }
                }
            }
        }
    }
    pc.printf("Leaving waitButtonHitFunc");
}



