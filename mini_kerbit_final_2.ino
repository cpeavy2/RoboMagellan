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

  #include <Servo.h>               // Load "Servo" library
  Servo servoLeft;                 // Left drive servo
  Servo servoRight;                // Right drive servo

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  
  pixy.init();
//  pixy.setLamp(1,1);

  servoLeft.attach(2);                  // Set left servo to pin 2
  servoRight.attach(3);                 // Set right servo to pin 3
}

void loop()
{ 
 
  servoLeft.write(90);
  servoRight.write(90);
  delay(2);
 
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
 
void stop() {
  servoLeft.write(90);
  servoRight.write(90);
  delay (2);
}

void left_forward() {
  servoLeft.write(135);
  servoRight.write(90);
  delay (8);
}

void left_reverse() {
  servoLeft.write(0);
  servoRight.write(90);
  delay (2);
}

void right_forward() {
  servoLeft.write(90);
  servoRight.write(45);
  delay (8);
}

void forward() {
  servoLeft.write(180);
  servoRight.write(0);
  delay(8);
}

void counterclockwise() {
  servoLeft.write(0);
  servoRight.write(0);
  delay(20);
}

void right_reverse() {
  servoLeft.write(90);
  servoRight.write(180);
  delay (2);
}

void clockwise() {
  servoLeft.write(180);
  servoRight.write(180);
  delay(20);
}

void reverse() {
  servoLeft.write(0);
  servoRight.write(180);
  delay(2);
}
