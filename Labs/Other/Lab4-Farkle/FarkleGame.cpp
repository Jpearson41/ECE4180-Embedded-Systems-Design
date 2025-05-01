#include  "FarkleGame.h"
#include <cstdlib>

using namespace std;

void FarkleGame::initArray() {
    int i =0;
    while(i < 6) {
        int ind = i+1;
        diceArray[i].setIndex(ind); //Set DiceArray index
        int num =(rand()%6)+1;
        diceArray[i].setValue(num); //Set DiceArray Random Value
        diceValue[i] = 0;           //Fill diceValue Array with 0's
        i+=1;
    }
    
}//End of initArray()

int FarkleGame::calcRoll() {
    int rollScore = 0, numTrips = 0, numPairs = 0, numOnes = 0;
    
    //Check for 6 of a kind
    for (int i = 0; i < 6; i++) {
        if (diceValue[i] == 6) {
            rollScore = 3000;
            if (diceValue[0] == 6) {              //Is the 6 of a kind all 1's?
                rollScore += 600;                   //If so add 600
            }else if (diceValue[4] == 6) {        //Is the 6 of a kind all 5's?
                rollScore += 300;                   //If so add 300
            }
            return rollScore;
        }
    }//No Six of a Kind/End Loop
    
    //Check for 5 of a kind
    for (int i = 0; i < 6; i++) {
        if (diceValue[i] == 5) {      
            rollScore = 2000;
            if (diceValue[0] == 1) {            //Is last die a 1?
                rollScore += 100;               //If so, add 100
            }else if (diceValue[4] == 1) {     //If last die a 5?
                rollScore += 50;                //If so, add 50
                //return rollScore;
            }else if (diceValue[0] == 5) {    //Is the 5 of a kind all 1's?
                rollScore += 500;               //If so add 500
            }else if (diceValue[4] == 5) {    //Is the 5 of a kind all 5's
                rollScore += 250;               //If so add 250
            }
            return rollScore;
        }
    }//No Five of a Kind/End Loop
    
    
    //Check for 4 of a kind
    for (int i = 0; i < 6; i++) {
        if (diceValue[i] == 4) {
            rollScore = 1000;
            if (diceValue[0] == 1 && diceValue[4] == 1) {       //Are last dice a 1 and 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                      //Is one of last dice a 1?
                rollScore += 100;
            }else if (diceValue[0] == 2) {                      //Are both last dies a 1?
                rollScore += 200;
            }else if (diceValue[4] == 1) {                      //Is one of last dice a 5?
                rollScore += 50;
            }else if (diceValue[4] == 2) {                      //Are both last dies a 5?
                rollScore += 100;
            }else if (diceValue[0] == 4) {    //Is the 4 of a kind all 1's?
                rollScore += 400;               //If so add 400
            }else if (diceValue[4] == 4) {    //Is the 4 of a kind all 5's
                rollScore += 200;               //If so add 200
            }
            return rollScore;
        }
    }//No Four of a Kind/End Loop
    
    //Check for 2 triplets
    for (int i = 0; i < 6; i++) {
        
        if (diceValue[i] == 3)             //Identify a triple
            numTrips += 1;
        if (numTrips == 2) {               //if theres 2, rollScore = 2500
            rollScore = 2500;
            if (diceValue[0] == 3 && diceValue[4] == 3) {           //Is there a triplet of 5's and 1's?
                rollScore += 450;                                       //If so add 450
            }else if (diceValue[4] == 3) {                          //Is one of the triplets all 5's?
                rollScore += 650;                                       //If so add 650    
            }else if (diceValue[0] == 3) {                          //Is one of the triplets all 1's?
                rollScore += 1300;                                      //If so add 1300
            }
            return rollScore;
        }
    }//No pair of Trips/End Loop
    
    
    //Check for 3 pairs
    for (int i = 0; i < 6; i++) {
        if (diceValue[i] == 2)
            numPairs += 1;
        if (numPairs == 3) {
            rollScore = 1500;
            if ( diceValue[0] == 2 && diceValue[4] == 2) {       //Is there a pair of 5's and 1's?
                rollScore += 300;                                   //If so add 300
            }else if (diceValue[4] == 2) {                       //Is there a pair of 5's?
                rollScore +=100;                                    //If so add 100
            }else if (diceValue[0] == 2) {                      //Is ther a pair of 1's?
                rollScore += 200;                                   //If so add 200
            }
            return rollScore;
        }
    }//No 3 Pairs/End Loop
    
    //Check for Full Row!
    for (int i = 0; i < 6; i++) {
        if (diceValue[i] == 1)
            numOnes +=1;
    }
    if (numOnes == 6) {
        rollScore = 1500;
        rollScore += 150;            //Add 150 for the 1 and 5
        return rollScore;
    }//No Full Row/End Loop
    
    //Check for Triplet of 6's
    if (diceValue[5] == 3) {   //3 Sixes
            rollScore = 600;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[0] == 3) {                  //Is there 3 1's?
                rollScore += 1300;
            }else if (diceValue[4] == 3) {                  //Is there 3 5's?
                rollScore += 650;
            }
            return rollScore;   
    }//No Triplet of 6's
    
    //Check for Triplet of 5's
     if (diceValue[4] == 3) {   //3 Fives
            rollScore = 650;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[0] == 3) {                  //Is there 3 1's?
                rollScore += 1300;
            }
            return rollScore;   
    }//No Triplet of 5's
    
    //Check for triplet of 4's
    if (diceValue[3] == 3) {   //3 Sixes
            rollScore = 400;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[0] == 3) {                  //Is there 3 1's?
                rollScore += 1300;
            }else if (diceValue[4] == 3) {                  //Is there 3 5's?
                rollScore += 650;
            }
            return rollScore;   
    }//No Triplet of 4's
    
    //Check for triplet of 3's
    if (diceValue[2] == 3) {   //3 Sixes
            rollScore = 300;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[0] == 3) {                  //Is there 3 1's?
                rollScore += 1300;
            }else if (diceValue[4] == 3) {                  //Is there 3 5's?
                rollScore += 650;
            }
            return rollScore;   
    }//No Triplet of 3's
    
    //Check for triplet of 2's
    if (diceValue[1] == 3) {   //3 Sixes
            rollScore = 200;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[0] == 3) {                  //Is there 3 1's?
                rollScore += 1300;
            }else if (diceValue[4] == 3) {                  //Is there 3 5's?
                rollScore += 650;
            }
            return rollScore;   
    }//No Triplet of 2's
    
    //Check for triplet of 1's
    if (diceValue[0] == 3) {   //3 Sixes
            rollScore = 1300;
            if (diceValue[0] == 1 && diceValue[4] == 1) {    //Is there a 1 & 5?
                rollScore += 150;
            }else if (diceValue[0] == 1) {                   //Is there just a one?
                rollScore += 100;
            }else if (diceValue[4] == 1) {                   //Is there just a five?
                rollScore += 50;
            }else if (diceValue[0] == 2 && diceValue[4] == 1) {                  //Is there 2 1's & a 5?
                rollScore +=250;
            }else if (diceValue[4] == 2 && diceValue[0] == 1) {                  //Is there 2 5's & a 1?
                rollScore +=200; 
            }else if (diceValue[0] == 2) {                  //Is there 2 1's 
                rollScore +=200;
            }else if (diceValue[0] == 2) {                  //Is there 2 5's 
                rollScore +=100;
            }else if (diceValue[4] == 3) {                  //Is there 3 5's?
                rollScore += 650;
            }
            return rollScore;    
    }//No Triplet of 1's
    
    //Check for a 1 & 5
    if (diceValue[0] == 1 && diceValue[4] == 1) {
        rollScore = 150;
        return rollScore;
    }//No singular 1 and singular 5
    
    //Check for singular 1
    if (diceValue[0] == 1) {     //Singular 1
        rollScore = 100;
        return rollScore;
    }//No singular 1
    //Check for 2 1's
    if (diceValue[0] == 2) {     //Double 1
        rollScore = 200;
        return rollScore;
    }//No 2 1's
    
    //Check for singular 5
    if (diceValue[4] == 1) {    //Singular 5
        rollScore = 50;
        return rollScore;
    }//No singular 5
    
    //Check for singular 5
    if (diceValue[4] == 2) {    //Singular 5
        rollScore = 100;
        return rollScore;
    }//No singular 5
    
    //If no scoring die, rollScore = 0;
    return rollScore;   
}//End of CalcRoll
        