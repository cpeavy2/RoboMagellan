//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with 
// Pixy and Arduino.  This program simply prints the detected object blocks 
// (including color codes) through the serial console.  It uses the Arduino's 
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//
 
#include <Pixy2.h>
 
// This is the main Pixy object 
Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
//  pixy.setLamp(1,1);

  pinMode(2, OUTPUT);  // Set pin 2 to output
  pinMode(3, OUTPUT);  // Set pin 3 to output
}

void loop()
{ 
 
  digitalWrite(2, LOW);   // sets the digital pin 2 off
  digitalWrite(3, LOW);  // sets the digital pin 3 off
 
  int i; 
  // grab blocks!
  pixy.ccc.getBlocks();
  
  // If there are detect blocks, print them!

// pixy.ccc.blocks[i].m_x The x location of the center of the detected object (0 to 316)
  
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
  
    Serial.println(pixy.ccc.blocks[i].m_x);

    if (pixy.ccc.blocks[i].m_x < 200 && pixy.ccc.blocks[i].m_x > 100) {
    forward();
     }

    if (pixy.ccc.blocks[i].m_x > 200) {
    right_forward();
    }

    if (pixy.ccc.blocks[i].m_x < 100) {
    left_forward();
  }
  }
}
 
void left_forward() {
  digitalWrite(2, HIGH);    // sets the digital pin 2 on
  digitalWrite(3, LOW);     // sets the digital pin 3 off
  delay(20);
}

void right_forward() {
  digitalWrite(2, LOW);     // sets the digital pin 2 off
  digitalWrite(3, HIGH);    // sets the digital pin 3 on
  delay(20);
}

void forward() {
  digitalWrite(2, HIGH);    // sets the digital pin 2 on
  digitalWrite(3, HIGH);    // sets the digital pin 3 on
  delay(20);
}
