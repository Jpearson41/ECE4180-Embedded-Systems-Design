#include "Dice.h"
#include "FarkleGame.h"
#include "MMA8452.h"
#include "PinDetect.h"
#include "Speaker.h"
#include "mbed.h"

#include <cstdlib>
#include <iostream>
#include <string>

//Defining Gamestates
#define HomeScreen 0
#define BCheck1 1
#define checkACC 2
#define RollDice 3
#define zeroCheck 4
#define DisplayDiceScore 5
#define DisplayDiceFarkle 6
#define CCheck 7
#define ACheck1 8
#define DisplayScore 9
#define ACheck2 10
#define Reset 11
#define GameOver 20

using namespace std;

//Instantiate this for Accelerometer
Serial pc(USBTX,USBRX);

int rollScore = 0, turnScore = 0, numDice = 6; 
int accValue = 0, pinPressA = 0, pinPressB = 0, pinPressC = 0, farkleCount = 0;
double x = 0, y = 0, z = 0;

uLCD_4DGL uLCD(p9, p10, p11); // create a global lcd object!

MMA8452 acc(p28, p27, 40000);  //instantiate an acc object!


PinDetect pb1(p21, PullUp); //create global Push button object for EndTurn (Inside Button)
PinDetect pb2(p22, PullUp); //create global Push button object for ReRoll  (Middle Button)
PinDetect pb3(p23, PullUp); //create global Push button object for Continue (Outer Button)

void keyPressedA( void ) {   //KeyPressed Function for Button A Press
    pinPressA = 1;
}
void keyPressedB( void ) {   //KeyPressed Function for Button B Press
    pinPressB = 1;
}
void keyPressedC( void ) {   //KeyPressed Function for Button C Press
    pinPressC = 1;
}
    


Speaker mySpeaker(p25); //create global speaker object!



int main()
{
    //srand(time(0));
    FarkleGame currentGame;                           //create game of farkle
    currentGame.initArray();                          //This creates array of Dice objects arrayDice = [DiceOBJ1,...]
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*for (int j = 0; j < 6; j++) {                     //Prints out dice array contents
        Dice & currentDice1 = currentGame.diceArray[j];
        int index = currentDice1.getIndex();
        int value = currentDice1.getValue();
        pc.printf(" Index: ");
        pc.printf(" %d ", index);
        wait(1);
        pc.printf(" Value: ");
        pc.printf(" %d ", value);
    }
    pc.printf("\n");
    for (int j = 0; j < 6; j++) {                     //Prints out dice Value contents
        int currentValue1 = currentGame.diceValue[j];
        pc.printf(" Value: ");
        pc.printf(" %d ", j+1);
        wait(1);
        pc.printf(" Amount of that Value: ");
        pc.printf(" %d ", currentValue1);
    }
        
    //wait(5);*/
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                          
 
    
    int currentState = HomeScreen;                                                 
    while (currentState != GameOver) {
        //pc.printf("      HERE2!\n");
        srand(time(0));
        switch(currentState) {
            case HomeScreen: 
                uLCD.cls();
                uLCD.display_control(PORTRAIT);
                uLCD.text_width(2);
                uLCD.text_height(2);
                uLCD.locate(0,1);
                //pc.printf("BOUT TO PRINT HOMESCREEN");
                uLCD.printf("Shake\n");
                uLCD.printf("Board\n");
                uLCD.printf("------\n");
                uLCD.printf("To\n");
                uLCD.printf("Roll\n");
                uLCD.printf("%d ", numDice);
                uLCD.printf("Dice");
                currentState = BCheck1;
                wait(1);
                break;
            case BCheck1:
                pc.printf("Here in the B button check 1!\n");
                pb2.attach_deasserted( &keyPressedB );
                pb2.setSampleFrequency();
                wait(5);
                if (pinPressB == 1) {
                    numDice = (numDice+1)%7;
                    currentState = HomeScreen;
                    pinPressB = 0;
                }else
                    currentState = checkACC;
                wait(1);
                break;
                
                
            case checkACC:
                pc.printf("Here in ACCcheck!\n");
                acc.setBitDepth(MMA8452::BIT_DEPTH_12);
                acc.setDynamicRange(MMA8452::DYNAMIC_RANGE_4G);
                acc.setDataRate(MMA8452::RATE_100);
                acc.readXYZGravity(&x,&y,&z);          //Check Accelerometer
                if (x >= .2 || y >= .2)                               //If 1 -> roll
                    currentState = RollDice;
                else
                    currentState = HomeScreen;                     //If not -> print home screen
                wait(1);
                break;
                
            case RollDice:
                pc.printf("Here in the rolling of the dice!\n");
                for (int i = 0; i < numDice; i++) {                     //Roll Dice 
                    Dice & currentDice2 = currentGame.diceArray[i];
                    mySpeaker.PlayNote(800.0,0.25,0.1);
                    currentDice2.rollDice();
                    
                    //currentGame.initArray();    
                    
                    int value = currentDice2.getValue();
                    switch(value) {                               //Fill valueArray
                        case 1:
                            currentGame.diceValue[0]+=1;
                            break;
                        case 2:
                            currentGame.diceValue[1]+=1;
                            break;
                        case 3:
                            currentGame.diceValue[2]+=1;
                            break;
                        case 4:
                            currentGame.diceValue[3]+=1;
                            break;
                        case 5:
                            currentGame.diceValue[4]+=1;
                            break;
                        case 6:
                            currentGame.diceValue[5]+=1;
                            break;
                    }
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////////////////////////////////////////////////////////////////////////////////////////
                /*for (int j = 0; j < 6; j++) {                     //Prints out dice array contents
                    Dice & currentDice3 = currentGame.diceArray[j];
                    int index = currentDice3.getIndex();
                    int value = currentDice3.getValue();
                    pc.printf(" Index: ");
                    pc.printf(" %d ", index);
                    wait(1);
                    pc.printf(" Value: ");
                    pc.printf(" %d ", value);
                }
                //wait(5);
                pc.printf("\n");
                for (int j = 0; j < 6; j++) {                     //Prints out dice Value contents
                    int currentValue2 = currentGame.diceValue[j];
                    
                    pc.printf(" Value: ");
                    pc.printf(" %d ", j+1);
                    wait(1);
                    pc.printf(" Amount of that Value: ");
                    pc.printf(" %d ", currentValue2);
                }
                //wait(5);*/
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////////////////////////////////////////////////////////////////////////////////////////////
                mySpeaker.PlayNote(600.0,0.25,0.1);
                rollScore = currentGame.calcRoll();             //Calculate rollScore
                turnScore += rollScore;                         //turnScore += rollScore
                currentState = zeroCheck;
                wait(1);
                break;
                
            case zeroCheck:
                pc.printf("Here in the checking of zero!\n");
                if (turnScore != 0) {                           //Score Not Zero -> DisplayDice and Score
                    currentState = DisplayDiceScore;
                }else {                                           //Score Zero -> DisplayDice and Farkle
                    currentState = DisplayDiceFarkle;
                    farkleCount += 1;
                }
                wait(1);
                break;
                
            case DisplayDiceScore:
                uLCD.cls();
                uLCD.display_control(PORTRAIT);
                uLCD.text_width(1);
                uLCD.text_height(1);
                pc.printf("Here in the display dice and score!\n");
                for (int i = 0; i < numDice; i++) {                                 
            
                    Dice & currentDice4 = currentGame.diceArray[i];
                    int currentIndex2 = currentDice4.getIndex();
                    int currentValue3 = currentDice4.getValue();
                    currentDice4.displayDice(currentValue3, currentIndex2); //DisplayDice    
                }
                uLCD.locate(1,11);                                      //Display rollScore
                uLCD.printf("This roll score:");
                uLCD.printf("  %d", rollScore);
                wait(1);
                uLCD.locate(1,13);                                     //Display turnScore
                uLCD.printf("This turn score:");
                uLCD.printf("  %d", turnScore);
                currentState = CCheck;
                wait(1);
                break;              
                
            case DisplayDiceFarkle:
                uLCD.cls();
                uLCD.text_width(3);
                uLCD.text_height(3);
                pc.printf("Here in the display dice and farkle!\n");
                for (int i = 0; i < numDice; i++) {                                  
    
                    Dice & currentDice5 = currentGame.diceArray[i];
                    int currentIndex3 = currentDice5.getIndex();
                    int currentValue4 = currentDice5.getValue();
                    currentDice5.displayDice(currentValue4, currentIndex3);  //DisplayDice
                }
                uLCD.locate(0,4);
                uLCD.printf("FARKLE");                                   //DisplayFARKLE
                turnScore = 0;
                currentState = ACheck1;
                wait(5);
                break;
            case CCheck:
                pc.printf("Here in the C button check!\n");
                pb3.attach_asserted( &keyPressedC );
                pb3.setSampleFrequency();
                wait(5);
                if (pinPressC == 1) { 
                    int temp = numDice;  //Number of Dice Thrown
                    numDice = 6 - temp;  //Subtract amount of dice thrown
                    for (int i = 0; i < 6; i++) {
                        currentGame.diceValue[i] = 0;
                    }
                    currentState = HomeScreen;
                    pinPressC = 0;
                }else
                    currentState = ACheck1;
                wait(1);
                break;
            case ACheck1:                                                 //A Button Check
                pc.printf("Here in the A button check 1!\n");
                pb1.attach_asserted( &keyPressedA );
                pb1.setSampleFrequency();
                wait(5);
                if (pinPressA == 1) {
                    currentState = DisplayScore;
                    pinPressA = 0;
                }else
                    currentState = zeroCheck;
                wait(1);
                break;
                
            case DisplayScore:
                uLCD.cls();
                pc.printf("Here in the display of turn score!\n");
                uLCD.display_control(PORTRAIT);
                uLCD.text_width(2);
                uLCD.text_height(2);
                uLCD.locate(0,1);
                
                uLCD.printf("Your Turn\n");
                uLCD.printf("Score\n");
                uLCD.printf("------\n");
                uLCD.printf("%d", turnScore);
                currentState = ACheck2;
                wait(1);
                break;
                
            case ACheck2:                                               //Second Button Check
                pc.printf("Here in the A button check 2!\n");
                pb1.attach_asserted( &keyPressedA );
                pb1.setSampleFrequency();
                wait(5);
                if (pinPressA == 1) {
                    currentState = Reset;
                    pinPressA = 0;
                }else
                    currentState = DisplayScore;
                wait(1);
                break;
                
            case Reset:
                pc.printf("Here in the Reset!\n");
                for (int i = 0; i < 6; i++) {                           //Reset Dice Value array
                    currentGame.diceValue[i] = 0;
                }
                rollScore = 0;                                          //Reset rollScore
                turnScore = 0;                                          //Reset turnScore
                numDice = 6;                                            //Set numDice to 6
                currentState = HomeScreen;                          
                wait(1);
                break;    
        }//End Switch Statement
    }//End While Loop
}//End Main   