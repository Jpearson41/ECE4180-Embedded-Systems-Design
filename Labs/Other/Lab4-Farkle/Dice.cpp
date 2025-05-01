#include "Dice.h"
//#include "uLCD_4DGL.h"
#include <cstdlib>

using namespace std;

extern uLCD_4DGL uLCD;

//RollDice Func
void Dice::rollDice()
{
    srand(time(0));
    int randNum = (rand()%6)+1;
    setValue(randNum);
}
//DisplayDice Functions
void Dice::displayDice(int value, int index)
{
    switch(value)
    {
        case 1:
            displayOne(index);
            
            //uLCD.printf("Done displaying one");
            break;
            
        case 2:
            displayTwo(index);
            
            //uLCD.printf("Done displaying Two");
            break;
            
        case 3:
            displayThree(index);
            
            //uLCD.printf("Done displaying Three");
            break;
            
        case 4:
            displayFour(index);
            
            //uLCD.printf("Done displaying Four");
            break;
            
        case 5:
            displayFive(index);
            
            //uLCD.printf("Done displaying Five");
            break;
            
        case 6:
            displaySix(index);
            
            //uLCD.printf("Done displaying Six");
            break;     
    }
    //uLCD.printf("Heading back to main loop");
}
//Beginning displayOne()
void Dice::displayOne(int index)
{
    //uLCD.printf("                          HERE 1");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(23,23,3,BLUE);
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(64,23,3,BLUE);
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(105,23,3,BLUE);
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(23,64,3,BLUE);
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(64,64,3,BLUE);
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(105,64,3,BLUE);
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }
    //uLCD.printf("        Leaving 1");
}
//End displayOne()


//Beginning displayTwo()
void Dice::displayTwo(int index) 
{
    //uLCD.printf("                     HERE 2");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(13,35,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(35,13,3,BLUE);         //Top Right Dot
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(51,35,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,13,3,BLUE);         //Top Right Dot
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(95,35,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,13,3,BLUE);         //Top Right Dot
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(13,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(32,54,3,BLUE);         //Top Right Dot
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(54,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,54,3,BLUE);         //Top Right Dot
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(95,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,54,3,BLUE);         //Top Right Dot
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }   
    //uLCD.printf("        Leaving 2");
}
//End displayTwo()


//Beginning displayTHree()
void Dice::displayThree(int index) 
{
    //uLCD.printf("            HERE 3");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(23,23,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(13,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,32,3,BLUE);                  //Bottom Right Dot
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(64,23,3,BLUE);                 //Middle Dot
            uLCD.filled_circle(54,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,32,3,BLUE);                  //Bottom Right Dot
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(105,23,3,BLUE);                //Middle Dot
            uLCD.filled_circle(95,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,32,3,BLUE);                  //Bottom Right Dot
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(23,64,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(13,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,73,3,BLUE);                  //Bottom Right Dot
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(64,64,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(54,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,73,3,BLUE);                  //Bottom Right Dot
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(105,64,3,BLUE);                 //Middle Dot
            uLCD.filled_circle(95,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,73,3,BLUE);                  //Bottom Right Dot
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }
    //uLCD.printf("         Leaving 3");
}
//End displayThree()


//Beginning displayFour()
void Dice::displayFour(int index) 
{
    //uLCD.printf("                   HERE 4");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(13,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,32,3,BLUE);               //Bottom left Dot
            uLCD.filled_circle(32,13,3,BLUE);               //Top Right Dot
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(54,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,13,3,BLUE);         //Top Right Dot
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(95,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,13,3,BLUE);         //Top Right Dot
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(13,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(32,54,3,BLUE);         //Top Right Dot
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(54,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,54,3,BLUE);         //Top Right Dot
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(95,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,54,3,BLUE);         //Top Right Dot
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }
    //uLCD.printf("         Leaving 4");
}
//End fisplayFour()



//Beginning displayFive()
void Dice::displayFive(int index) {
    //uLCD.printf("                       HERE 5");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(23,23,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(13,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,32,3,BLUE);               //Bottom left Dot
            uLCD.filled_circle(32,13,3,BLUE);               //Top Right Dot
        
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(64,23,3,BLUE);                 //Middle Dot
            uLCD.filled_circle(54,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,13,3,BLUE);         //Top Right Dot
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(105,23,3,BLUE);                //Middle Dot
            uLCD.filled_circle(95,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,13,3,BLUE);         //Top Right Dot
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(23,64,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(13,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(32,54,3,BLUE);         //Top Right Dot
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(64,64,3,BLUE);                  //Middle Dot
            uLCD.filled_circle(54,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,54,3,BLUE);         //Top Right Dot
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(105,64,3,BLUE);                 //Middle Dot
            uLCD.filled_circle(95,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,54,3,BLUE);         //Top Right Dot
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }
    //uLCD.printf("         Leaving 5");
}
//End displayFive()


//Beginning displaySix()
void Dice::displaySix(int index) 
{
    //uLCD.printf("                   HERE 6");
    switch(index)
    {
        //First Row
        case 1:
            uLCD.filled_rectangle(3,3,42,42,WHITE);
            uLCD.rectangle(3,3,42,42,BLUE);
            uLCD.filled_circle(13,23,3,BLUE);                //Left Middle Dot
            uLCD.filled_circle(13,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,32,3,BLUE);               //Bottom left Dot
            uLCD.filled_circle(32,13,3,BLUE);               //Top Right Dot
            uLCD.filled_circle(32,23,3,BLUE);                //Right Middle Dot
            break;
        case 2:
            uLCD.filled_rectangle(44,3,83,42,WHITE);
            uLCD.rectangle(44,3,83,42,BLUE);
            uLCD.filled_circle(54,23,3, BLUE);                 //Left Middle Dot
            uLCD.filled_circle(54,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,13,3,BLUE);         //Top Right Dot
            uLCD.filled_circle(73,23,3,BLUE);                //Right MIddle Dot
            break;
        case 3:
            uLCD.filled_rectangle(85,3,124,42,WHITE);
            uLCD.rectangle(85,3,124,42,BLUE);
            uLCD.filled_circle(95,23,3,BLUE);                //Left Middle Dot
            uLCD.filled_circle(95,13,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,32,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,32,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,13,3,BLUE);         //Top Right Dot
            uLCD.filled_circle(114,23,3,BLUE);                //Right MIddle Dot
            break;
        //Second row
        case 4:
            uLCD.filled_rectangle(3,44,42,83,WHITE);
            uLCD.rectangle(3,44,42,83,BLUE);
            uLCD.filled_circle(13,64,3,BLUE);                //Left Middle Dot
            uLCD.filled_circle(13,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(32,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(13,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(32,54,3,BLUE);         //Top Right Dot
            uLCD.filled_circle(32,64,3,BLUE);                //Right MIddle Dot
            break;
        case 5:
            uLCD.filled_rectangle(44,44,83,83,WHITE);
            uLCD.rectangle(44,44,83,83,BLUE);
            uLCD.filled_circle(54,64,3,BLUE);                //Left Middle Dot
            uLCD.filled_circle(54,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(73,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(54,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(73,54,3,BLUE);         //Top Right Dot
            uLCD.filled_circle(73,64,3,BLUE);                //Right MIddle Dot
            break;
        case 6:
            uLCD.filled_rectangle(85,44,124,83,WHITE);
            uLCD.rectangle(85,44,124,83,BLUE);
            uLCD.filled_circle(95,64,3,BLUE);                //Left Middle Dot
            uLCD.filled_circle(95,54,3,BLUE);                  // Top Left Dot
            uLCD.filled_circle(114,73,3,BLUE);                  //Bottom Right Dot
            uLCD.filled_circle(95,73,3,BLUE);          //Bottom left Dot
            uLCD.filled_circle(114,54,3,BLUE);         //Top Right Dot
            uLCD.filled_circle(114,64,3,BLUE);                //Right MIddle Dot
            break;
        default:
            uLCD.printf("Something is happening");
            break;
    }
    //uLCD.printf("         Leaving 6");
}
//End displaySix()
    
//Getters/Setters
int Dice::getIndex() {
    return index;
}
int Dice::getValue() {
    return value;
}
void Dice::setValue(int num) {
    value = num;
}
void Dice::setIndex(int num) {
    index = num;
}