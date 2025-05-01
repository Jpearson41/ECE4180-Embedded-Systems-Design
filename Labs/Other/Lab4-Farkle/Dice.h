#ifndef DICE_H
#define DICE_H
#include "uLCD_4DGL.h"


using namespace std;

class Dice
{
    public:
        void rollDice();
        //Display Funcs
        void displayDice(int value,int position);
        void displayOne(int ind);
        void displayTwo(int ind);
        void displayThree(int ind);
        void displayFour(int ind);
        void displayFive(int ind);
        void displaySix(int ind);
        //Getters/Setters
        int getIndex();
        int getValue();
        void setValue(int val);
        void setIndex(int ind);
        
    private:
        int index;
        int value;
        
};

#endif
        