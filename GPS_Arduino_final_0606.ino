#include <TinyGPS++.h>
#include <SoftwareSerial.h>
 
static const int RXPin = 8, TXPin = 7;
static const uint32_t GPSBaud = 9600;
 
// The TinyGPS++ object
TinyGPSPlus gps;
 
// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
 
// For stats that happen every 5 seconds
unsigned long last = 0UL;
 
float TarLat;       // Target Latitude
float TarLong;      // Target Longitude
float ActLat;       // Actual Latitude
float ActLong;      // Actual Longitude
float Bearing;      // gps.course.deg
float DiffLat;      // Difference between TarLat and ActLat
float DiffLong;     // Difference between TarLong and ActLong
 
// Connection between GPS and Motor Arduino
// Arduino1 => Arduino2
// GPS         Motors
//        2 -> 10
//        3 -> 11
//        4 -> 12
//        5 -> 13
 
void setup()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(2, OUTPUT);    // sets the digital pin as output
  pinMode(3, OUTPUT);    // sets the digital pin as output
  pinMode(4, OUTPUT);    // sets the digital pin as output
  pinMode(5, OUTPUT);    // sets the digital pin as output
 
// Input Target coordinates
 
// TarLat = Target Latitude
TarLat = 30.513465; // Tallahassee
// TarLat = 30.513490; // Tallahassee
// TarLat = 40.706351; // New York
// TarLat = 19.492306; // Mexico City
 
// TarLong = Target Longitude
TarLong = -84.237213; // Tallahassee
// TarLong = -84.237190; // Tallahassee
// TarLong = -74.004550; // New York
// TarLong = -99.116716; // Mexico City
}
 
void loop()
{
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());
 
  if (gps.course.isUpdated())
  {
//    Serial.print(F(" Deg="));
//    Serial.println(gps.course.deg());
  }
 
// Actual Latitude and Longitude
ActLat = gps.location.lat();
ActLong = gps.location.lng();
 
// ActLat = 30.513490;   // test coordinates
// ActLong = -84.237190;

// ActLat = 19.492306; // test coordinates
// ActLong = -99.116716;
 
// Actual bearing
Bearing = gps.course.deg();
// Bearing = 0; // test bearing
// Bearing = 90;
// Bearing = 180;
// Bearing = 270;
 
Serial.println();
Serial.print (" ");
Serial.println (ActLat, 6);
Serial.println (ActLong, 6);
Serial.println (Bearing);
Serial.println();
 
//DiffLat = TarLat - ActLat;
//DiffLong = TarLong - ActLong;
 
//Serial.println(DiffLat, 6);
//Serial.print (" ");
//Serial.println(DiffLong, 6);
//Serial.println();
// delay(300);
 
// Cones of travel (~45%)
// North = 338-359 or 0-22  // (45°)
// NorthEast = 23-67        // (45°)
// East = 68-112            // (45°)
// SouthEast = 113-157      // (45°)
// South = 158-202          // (45°)
// SouthWest = 203-247      // (45°)
// West = 248-292           // (45°)
// NorthWest = 293-337      // (45°)
 
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
 
if (TarLat > ActLat && TarLong == ActLong)
// Travel North
{Serial.print("North "); 
  if (Bearing <= 22 || Bearing >= 338)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 23 && Bearing <= 180)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 181 && Bearing <=337)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat < ActLat && TarLong == ActLong)
// Travel South
{Serial.print("South ");
  if (Bearing <= 202 && Bearing >= 158)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 203 && Bearing <= 359)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 0 && Bearing <= 157)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat == ActLat && TarLong > ActLong)
{// Travel East
Serial.print("East ");
  if (Bearing <= 112 && Bearing >= 68)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 270 || Bearing <= 67)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 113 || Bearing <= 269)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
}

if (TarLat == ActLat && TarLong < ActLong)
{// Travel West
Serial.print("West ");
  if (Bearing <= 292 && Bearing >= 248)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 293 || Bearing <= 90)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 91 || Bearing <= 249)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat > ActLat && TarLong > ActLong)
{// Travel North East 24-69
Serial.print("NorthEast ");
  if (Bearing <= 67 && Bearing >= 23)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 68 || Bearing <= 225)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 226 || Bearing <= 22)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat < ActLat && TarLong < ActLong)
{// Travel South West 207- 254
Serial.print("SouthWest ");
  if (Bearing <= 203 && Bearing >= 247)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 248 || Bearing <= 45)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 46 || Bearing <= 202)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat > ActLat && TarLong < ActLong)
{// Travel North West 299- 335
Serial.print("NorthWest ");
  if (Bearing <= 337 && Bearing >= 293)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 338 || Bearing <= 135)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 136 || Bearing <= 292)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat < ActLat && TarLong > ActLong)
{// South East 116-161
Serial.print("SouthEast ");
  if (Bearing <= 157 && Bearing >= 113)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 113 || Bearing <= 315)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 316 || Bearing <= 156)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat == ActLat && TarLong == ActLong)
{// Target found
Serial.print("Goal! ");
// Stop!
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, LOW);
 digitalWrite(5, LOW);
}
}

if (TarLat == 0.000000 && TarLong == 0.000000)
// No GPS!
    {Serial.print("No GPS! ");
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, LOW);
 digitalWrite(5, LOW);
}
}
}
