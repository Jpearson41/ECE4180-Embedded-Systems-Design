#include "PinDetect.h"
#include "mbed.h"
#include "MCP23S17.h"
// Create SPI bus
SPI spi(p5, p6, p7);
char Opcode = 0x40;

// Next create a MCP23S17
// mbed p20 is connected to ~chipSelect on the MCP23S17
MCP23S17 chip = MCP23S17(spi, p20, Opcode);
DigitalOut led1(LED1); // mbed LED1 is used for test status display
DigitalOut led2(LED2);
PinDetect pb1(p13); //pushbutton pin

void pb1_hit_callback() {
    
    chip.write(PORT_A, 0xAA);
    led2 = 1;
    led1 = chip.read(PORT_B)& 0x01;
    //chip.write(PORT_A, 0x00);
    //led1 = chip.read(PORT_B)& 0x01;
}

int main() {
    
//  Set all 8 Port A bits to output direction
    chip.direction(PORT_A, 0x00);
//  Set all 8 Port B bits to input direction
    chip.direction(PORT_B, 0xFF);
    led1=0;
    
    pb1.mode(PullUp);
    wait(0.01);
    pb1.attach_deasserted(&pb1_hit_callback);
    pb1.setSampleFrequency();
    
    while (1) {
        wait(0.5);
        //chip.write(PORT_A, 0x00);
        //led1 = chip.read(PORT_B)& 0x01;
    }
}
