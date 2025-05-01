#include "mbed.h"
#include "MMA8452.h"
 #include "uLCD_4DGL.h"
 #include "PinDetect.h"
 #include "Speaker.h"
 
 
 uLCD_4DGL uLCD(p9, p10, p11); // create a global uLCD object
 
Serial pc(USBTX,USBRX); //not used in this program

Speaker mySpeaker(p25);

PinDetect pb1(p21);
PinDetect pb2(p22);

int main() {
   
   // you can play around with the parameters to see the response
   int radius = 10;
   int offsetx = 63;
   int offsety = 63;
   double factor = 50;
   double music_factor = 200;
   bool MusicOn = false;
   
   //set the push buttons that control sounds
   pb1.mode(PullUp);
   pb2.mode(PullUp);
   //I will not use interupts like in jazzy tunes
 
   
   double x = 0, y = 0, z = 0;
 
   MMA8452 acc(p28, p27, 40000);  //instantiate an acc object! 
   
   //set parameters -- use these and don't change
   acc.setBitDepth(MMA8452::BIT_DEPTH_12);
   acc.setDynamicRange(MMA8452::DYNAMIC_RANGE_4G);
   acc.setDataRate(MMA8452::RATE_100);
   
   
   while(1) {
      
      uLCD.circle(-1*y*factor+offsety, -1*x*factor+offsetx, radius, BLACK);
       
      if(!acc.isXYZReady()) 
      {
         wait(0.01);
      }
      else
      { 
      
      acc.readXYZGravity(&x,&y,&z); //notice this is passed by reference use pointers
      
      uLCD.circle(-1*y*factor+offsety, -1*x*factor+offsetx, radius, WHITE);
      
      if (MusicOn)
           mySpeaker.PlayNote(440.0+x*music_factor,0.25+0.2*y,0.05);
      
      if (pb1 == false)
           MusicOn = true;
           
      if (pb2 == false)
            MusicOn = false;
                 
                 
      // You can uncomment this line to see the values coming off the MMA8452           
      //uLCD.printf("\n(%.2f,%.2f,%.2f)  \n", x,y,z);
      
      } //end else
      
   } //end infinite while loop
} // end main