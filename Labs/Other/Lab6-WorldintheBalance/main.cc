#include "SpaceShipEarth.h"
#include "ConcreteAsteroid1.h"
#include "ConcreteAsteroid2.h"
#include "ConcreteAsteroid3.h"
#include "ConcreteAsteroid4.h"

#include "Speaker.h"
#include "global.h"

//Initialize uLCD var
uLCD_4DGL uLCD(p9,p10,p11);
//Initialize this for Accerlerometer
Serial pc(USBTX,USBRX);
//Initialize Accerlerometer var
MMA8452 acc(p28, p27, 100000);
//Initialize Speaker var
Speaker mySpeaker(p25);


double x,y,z;
double soundEffects[10] = {100.0,200.0,300.0,400.0,500.0,600.0,700.0,800.0,900.0,1000.0};

//Array for the pointers for all asteroids
ScreenObject * ActiveAsteroids[NUM_ASTEROIDS];

//Check if the 2 Screen Objects overlap
bool overlap(ScreenObject & objectA, ScreenObject & objectB) {

    //Object A's X & Y position
    int oneXLeftTop = objectA.x_pos;
    int oneYLeftTop = objectA.y_pos;

    //Object B's X & Y position
    int twoXLeftTop = objectB.x_pos;
    int twoYLeftTop = objectB.y_pos;

    //if the x_pos is inside the other
    if(oneXLeftTop >= twoXLeftTop && oneXLeftTop <= twoXLeftTop+ASTEROID_WIDTH){
        if(oneYLeftTop >= twoYLeftTop && oneYLeftTop <= twoYLeftTop+ASTEROID_HEIGHT){
            return true;
        }
    }
    //If y_pos is inside the other
    if(twoXLeftTop >= oneXLeftTop && twoXLeftTop <= oneXLeftTop+EARTH_WIDTH){
        if(twoYLeftTop >= oneYLeftTop && twoYLeftTop <= oneYLeftTop+EARTH_HEIGHT){
            return true;
        }
    }
    //Else return false
    return false;
}

//Main Function
int main()
{
    pc.printf("Here in main");
    //ULCD Baudrate
    uLCD.baudrate(3000000);
    wait(0.2);

    //Setting up the pc baudrate
    pc.baud(115200);

    //Setting up srand
    srand(time(0));

    //Fill out ActiveAsteroids array
    ActiveAsteroids[0] = new ConcreteAsteroid1();
    ActiveAsteroids[1] = new ConcreteAsteroid2();
    ActiveAsteroids[2] = new ConcreteAsteroid3();
    ActiveAsteroids[3] = new ConcreteAsteroid4();
    pc.printf("Here printing asteroids");
    //Drawing all the Asteroids
    for(int i = 0; i< NUM_ASTEROIDS; i++){
        ActiveAsteroids[i]->x_pos = 0;
        ActiveAsteroids[i]->y_pos = (rand() % (127-ASTEROID_HEIGHT) + 7);
        ActiveAsteroids[i]->draw();
    }

    //Initializing the Earth
    SpaceShipEarth ship;
    pc.printf("Here printing earth");
    //Setting up the Earth's position
    ship.x_pos = 64;
    ship.y_pos = 64;
    ship.newY = 64;
    ship.newX = 64;

    //Drawing the earth
    ship.draw();

    //Setting overlapping to false
    bool overlapping = false;

    //Start timer
    Timer overall;
    overall.start();

    //Timer progress bar
    uLCD.filled_rectangle(0,     0, 127,  7, GREEN);

    while(1)
    {
        pc.printf("Here in infinite while loop");
        Timer t; t.start();

        //Check for collision, if so break to ending screens
        for(int i = 0; i < NUM_ASTEROIDS; i++){
            overlapping = overlap(ship, *ActiveAsteroids[i]);
            if(overlapping) break;
        }
        if(overlapping) break;

        pc.printf("Here bout to update positions");
        //Update Asteroids
        for(int i = 0; i< NUM_ASTEROIDS; i++){
            ActiveAsteroids[i]->update();
        }
        pc.printf("Here readings accvalues again");
        //Re-read Accerlerometer values
        acc.readXYZGravity(&x,&y,&z);
        pc.printf("Here about to update earths positions");
        //Updating the Earth's position based on the Accelerometer's reading
        if(y > 0.2){ ship.newX += 10;}
        else if(y < -0.2){ ship.newX -= 10;}
        if(x > 0.2){ ship.newY += 10;}
        else if(x < -0.2){ship.newY -= 10;}
        pc.printf("Here updating earth position");
        //UPDATE EARTH POSITION
        ship.update();

        //Slight Program delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 400) wait_ms(400 - dt);

        //Check timer
        int dOverall = overall.read_ms();
        if(dOverall >= 30000){ break; }

        //Setting the progress bar position based on the timer
        double percent = (127.0-((dOverall/30000.0)*127.0));
        uLCD.filled_rectangle(0, 0, 127,  7, _);
        uLCD.filled_rectangle(0, 0, percent,  7, GREEN);

    }

    //Ending Screens: GAME OVER or YOU WIN
    if(overlapping){
        ship.explosion();
        //Losing Tune
        for(int i = 9; i >= 0; i--){
            mySpeaker.PlayNote(soundEffects[i],0.2,1);
        }
        wait_ms(700);
        //GAME OVER
        uLCD.cls();
        uLCD.filled_rectangle(0,     0, 127,  127, _);
        uLCD.locate(5,2);
        uLCD.color(TEXTCOLOR);
        uLCD.textbackground_color(_);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.printf("GAME");
        uLCD.printf("OVER!!");
        uLCD.printf("Try");
        uLCD.printf("Again!!");
    }else{
        //Winning Tune
        for(int i = 0; i < 10; i++){
            mySpeaker.PlayNote(soundEffects[i],0.2,1);
        }
        //YOU WIN!!!
        uLCD.cls();
        uLCD.filled_rectangle(0,     0, 127,  127, _);
        uLCD.locate(5,2);
        uLCD.color(TEXTCOLOR);
        uLCD.textbackground_color(_);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.printf("YOU ");
        uLCD.printf("WIN!!");
        uLCD.printf("WELL ");
        uLCD.printf("DONE!");
    }

}
