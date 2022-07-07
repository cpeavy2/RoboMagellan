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
int x = 0;
 
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
 
  Serial.println();
 
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
  delay(10);
 
if (raw_distance < 2000) {
  x = 0;
    while (x <200) {
      reverse();
    x++;
 }
   x = 0;
    while (x <100) {
      clockwise();
    x++;
 }
   x = 0;
    while (x <150) {
      forward();
    x++;
 }
}
 
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
  delay(10);
 
if (raw_distance < 2000) {
  x = 0;
    while (x <200) {
      reverse();
    x++;
 }
   x = 0;
    while (x <100) {
      clockwise();
    x++;
 }
   x = 0;
    while (x <150) {
      forward();
    x++;
 }
}
 
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
  delay(10);
 
if (raw_distance < 2000) {
  x = 0;
    while (x <200) {
      reverse();
    x++;
 }
   x = 0;
    while (x <100) {
      clockwise();
    x++;
 }
   x = 0;
    while (x <150) {
      forward();
    x++;
 }
}
 
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
  delay(10);
 
if (raw_distance < 2000) {
  x = 0;
    while (x <200) {
      reverse();
    x++;
 }
   x = 0;
    while (x <100) {
      clockwise();
    x++;
 }
   x = 0;
    while (x <150) {
      forward();
    x++;
 }
}
 
  Serial.println();
 
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
 
if (a == 0 && b == 0 && c == 1 && d == 0) forward();

if (a == 1 && b == 1 && c == 0 && d == 1) veer_left();

if (a == 0 && b == 0 && c == 1 && d == 1) veer_right();

if (a == 0 && b == 0 && c == 0 && d == 0) halt();
}
 
void halt() {  // 00000 = halt
  roboclaw.ForwardM1(address,0); // Motor1 stop
  roboclaw.ForwardM2(address,0); // Motor2 stop
  delay(2);
}
 
void left_forward() { // 10000 = left forward
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,0); // Motor2 stop
  delay (2);
}
 
void left_reverse() { // 01000 = left reverse
  roboclaw.BackwardM1(address,64); // Motor1 backward at half speed
  roboclaw.ForwardM2(address,0); // Motor2 forward at half speed
  delay (2);
}
 
void right_forward() { // 11000 = right forward
  roboclaw.ForwardM1(address,0); // Motor1 stop
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
}
 
void forward() { // 00100 = forward
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
}
 
void counterclockwise() {
  roboclaw.BackwardM1(address,64); // Motor1 backward at half speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
}
 
void right_reverse() { // 01000 = left reverse
  roboclaw.ForwardM1(address,0); // Motor1 stop
  roboclaw.BackwardM2(address,64); // Motor2 backward at half speed
  delay (2);
}
 
void clockwise() {
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.BackwardM2(address,64); // Motor2 backward at half speed
  delay(2);
}
 
void reverse() {
  roboclaw.BackwardM1(address,64); // Motor1 backward at half speed
  roboclaw.BackwardM2(address,64); // Motor2 backward at half speed
  delay(2);
}

void veer_left() {
  roboclaw.ForwardM1(address,32); // Motor1 forward at quarter speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
}

void veer_right() {
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,32); // Motor2 forward at quarter speed
}
