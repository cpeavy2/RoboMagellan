//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"
 
//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(3,2);  
RoboClaw roboclaw(&serial,10000);
 
#define address 0x80
 
int a;
int b;
int c;
int d;
const int pingPin6 = 6;
const int pingPin7 = 7;
const int pingPin8 = 8;
const int pingPin9 = 9;
 
void setup() {
  Serial.begin(9600);                    // Setup serial monitor for debug
  //Open roboclaw serial ports
  roboclaw.begin(38400);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}
 
// Arduino1 => Arduino2
// GPS         Motors
//       2 -> 10
//       3 -> 11
//       4 -> 12
//       5 -> 13
 
void loop() {
 
   long raw_distance;
 
  pinMode(pingPin6, OUTPUT);
  digitalWrite(pingPin6, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin6, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin6, LOW);
 
  pinMode(pingPin6, INPUT);
  raw_distance = pulseIn(pingPin6, HIGH);
 
  Serial.print(raw_distance);
  Serial.println();
  delay(100);

 
  pinMode(pingPin7, OUTPUT);
  digitalWrite(pingPin7, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin7, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin7, LOW);
 
  pinMode(pingPin7, INPUT);
  raw_distance = pulseIn(pingPin7, HIGH);
 
  Serial.print(raw_distance);
  Serial.println();
  delay(100);

 
  pinMode(pingPin8, OUTPUT);
  digitalWrite(pingPin8, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin8, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin8, LOW);
 
  pinMode(pingPin8, INPUT);
  raw_distance = pulseIn(pingPin8, HIGH);
 
  Serial.print(raw_distance);
  Serial.println();
  delay(100);

 
  pinMode(pingPin9, OUTPUT);
  digitalWrite(pingPin9, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin9, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin9, LOW);
 
  pinMode(pingPin9, INPUT);
  raw_distance = pulseIn(pingPin9, HIGH);
 
  Serial.print(raw_distance);
  Serial.println();
  delay(100);
 
 a = digitalRead(10);
 b = digitalRead(11);
 c = digitalRead(12);
 d = digitalRead(13);

  Serial.println();
  Serial.print("a: ");
  Serial.print("\t");
  Serial.print(a);
  Serial.println();
  Serial.print("b: ");
  Serial.print("\t");
  Serial.print(b);
  Serial.println();
  Serial.print("c: ");
  Serial.print("\t");
  Serial.print(c);
  Serial.println();
  Serial.print("d: ");
  Serial.print("\t");
  Serial.print(d);
  Serial.println();
 
if (a == 1) forward();
if (b == 1) right_forward();
if (c == 1) left_forward();
if (d == 1) halt();
}
 
void forward() {
  roboclaw.ForwardM1(address,64); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,64); //start Motor2 backward at half speed
  delay(2);
}
 
void right_forward() {    // formally "left"
  roboclaw.ForwardM1(address,32); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,64); //start Motor2 backward at half speed
  delay(2);
}
 
void left_forward() {   // formally "right"
  roboclaw.ForwardM1(address,64); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,32); //start Motor2 backward at half speed
  delay(2);
}
 
void halt() {
  roboclaw.ForwardM1(address,0); //start Motor1 forward at half speed
  roboclaw.ForwardM2(address,0); //start Motor2 backward at half speed
  delay(2);
}
 
// right_reverse
// left_reverse
// clockwise
// counterclockwise
// reverse
