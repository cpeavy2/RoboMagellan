//Includes required to use Roboclaw library
#include <SoftwareSerial.h>
#include "RoboClaw.h"
 
//See limitations of Arduino SoftwareSerial
SoftwareSerial serial(3,2);  
RoboClaw roboclaw(&serial,10000);
 
#define address 0x80
 
int x = 0;  // Counter variable
 
int a;  // Motor Drive Code
int b;  // Motor Drive Code
int c;  // Motor Drive Code
int d;  // Motor Drive Code
 
int e;  // PixyCam Reading Left
int f;  // PixyCam Reading Right
 
int g;  // orange cone switch
 
const int pingPin6 = 6;
const int pingPin7 = 7;
const int pingPin8 = 8;
const int pingPin9 = 9;
 
long raw_distance;  // Ping readings
 
void setup() {
  Serial.begin(9600);                    // Setup serial monitor for debug
// Open roboclaw serial ports
  roboclaw.begin(38400);
 
// Input pins for GPS_Arduino
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
 
// PixyCam Pins
  pinMode(4, INPUT);
  pinMode(5, INPUT);  
}
 
// Arduino1 => Arduino2
// GPS         Motors
//       2 -> 10
//       3 -> 11
//       12 -> 12
//       5 -> 13
 
// Pins: GPS_Arduino1 => Motor_Sensor_Arduino2
// 0000 = halt
// 1000 = left forward
// 0100 = left reverse
// 1100 = right forward
// 0010 = forward
// 1010 = counterclockwise
// 0110 = right reverse
// 1001 = clockwise
// 0101 = reverse
// 1101 = veer_left
// 0011 = veer_right
 
void loop() {
 
g = analogRead(0);
e = digitalRead(4);
f = digitalRead(5);
 
  Serial.print("e: ");
  Serial.print("\t");
  Serial.print(e);
  Serial.println();
  Serial.print("f: ");
  Serial.print("\t");
  Serial.print(f);
  Serial.println();
  Serial.print("g: ");
  Serial.print("\t");
  Serial.print(g);
  Serial.println();
 
// Behavior if Orange detected or switch pressed.
 
  if (g == 0) {  // Orange_halt
  roboclaw.ForwardM1(address,0); // Motor1 stop
  roboclaw.ForwardM2(address,0); // Motor2 stop
  delay(2);
  loop();
  }
 
  if (e == 1 && f == 1) {  // Orange_forward
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
  loop();
  }
 
  if (e == 1) {  // Orange_veer_left
  roboclaw.ForwardM1(address,32); // Motor1 forward at quarter speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
  loop();
  }
 
  if (f == 1) {  // Orange_veer_right
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,32); // Motor2 forward at quarter speed
  delay(2);
  loop();
  }
 
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
    while (x <70) {
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
    while (x <80) {
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
    while (x <70) {
      counterclockwise();
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
    while (x <60) {
      counterclockwise();
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
 
void orange_forward() { // 00100 = forward
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
}
 
void orange_veer_left() {
  roboclaw.ForwardM1(address,32); // Motor1 forward at quarter speed
  roboclaw.ForwardM2(address,64); // Motor2 forward at half speed
  delay(2);
}
 
void orange_veer_right() {
  roboclaw.ForwardM1(address,64); // Motor1 forward at half speed
  roboclaw.ForwardM2(address,32); // Motor2 forward at quarter speed
  delay(2);
}
 
void orange_halt() {  // 00000 = halt
  roboclaw.ForwardM1(address,0); // Motor1 stop
  roboclaw.ForwardM2(address,0); // Motor2 stop
  delay(2);
}
