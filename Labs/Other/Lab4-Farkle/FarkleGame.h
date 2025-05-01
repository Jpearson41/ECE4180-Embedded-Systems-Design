#ifndef FARKLEGAME_H
#define FARKLEGAME_H
#include "Dice.h"

using namespace std;

class FarkleGame
{
    public:
        int calcRoll();
        void initArray();
        
        Dice diceArray[6];
        int diceValue[6];
        //Dice diceToRoll[6];
        int player1score;
        int player2score;
};

#endif