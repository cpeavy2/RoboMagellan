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
//    2 -> 10
//    3 -> 11
//    4 -> 12
//    5 -> 13
 
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
TarLat = 30.513436; // Tallahassee
// TarLat = 30.513490; // Tallahassee
// TarLat = 40.706351; // New York
// TarLat = 19.492306; // Mexico City
 
// TarLong = Target Longitude
TarLong = -84.237159; // Tallahassee
// TarLong = -84.237190; // Tallahassee
// TarLong = -74.004550; // New York
// TarLong = -99.116716; // Mexico City
//delay(120000);
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
 
// ActLat = 30.513610;
// ActLong = -84.237266;
 
// ActLat = 30.513490;   // test coordinates
// ActLong = -84.237190;
 
// ActLat = 19.492306; // test coordinates
// ActLong = -99.116716;
 
// Actual bearing
Bearing = gps.course.deg();
// Bearing = 0; // test bearings
// Bearing = 135; // Stop
// Bearing = 180; // Stop
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
 
// Cone of travel (90%)
// North = 316-360 or 0-45  // (90°)
// NorthEast = 1-90         // (90°)
// East =  46-135           // (90°)
// SouthEast = 91-180       // (90°)
// South = 136-225          // (90°)
// SouthWest = 181-270      // (90°)
// West = 226-315           // (90°)
// NorthWest = 271-360      // (90°)
 
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
// Travel North 315-360 or 0-45 (0°)
{Serial.print("North "); 
  if (Bearing >= 315 || Bearing <= 45)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 46 && Bearing <= 180)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing < 316 && Bearing > 181)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat > ActLat && TarLong > ActLong)
// Travel North East 0-90 (45°)
{Serial.print("NorthEast ");
  if (Bearing >= 0 && Bearing <= 90)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 91 && Bearing <= 225)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 226 && Bearing <= 360)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat == ActLat && TarLong > ActLong)
// Travel East 45-135 (90°)
{Serial.print("East ");
  if (Bearing >= 45 && Bearing <= 135)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing < 46 || Bearing >= 270)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 136 && Bearing < 269)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat < ActLat && TarLong > ActLong)
// South East 90-180 (135°)
{Serial.print("SouthEast ");
  if (Bearing > 90 && Bearing < 180)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing < 89 || Bearing >= 315)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 181 && Bearing < 314)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
}
}
 
if (TarLat < ActLat && TarLong == ActLong)
// Travel South 135-225 (180°)
{Serial.print("South ");
  if (Bearing >= 135 && Bearing <= 225)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 226 && Bearing <= 359)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 0 && Bearing < 136)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}

if (TarLat < ActLat && TarLong < ActLong)
// Travel South West 180-270 (225°)
{Serial.print("SouthWest ");
  if (Bearing >= 180 && Bearing <= 270)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 271 || Bearing <= 45)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 46 && Bearing < 181)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat == ActLat && TarLong < ActLong)
// Travel West 225-315 (270°)
{Serial.print("West ");
  if (Bearing <= 315 && Bearing >= 225)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 316 || Bearing <= 90)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 91 && Bearing < 226)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat > ActLat && TarLong < ActLong)
// Travel North West 270-360 (315°)
{Serial.print("NorthWest ");
  if (Bearing <= 360 && Bearing >= 270)
// forward
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, HIGH);
 digitalWrite(5, LOW);
}
 
  if (Bearing > 0 && Bearing <= 135)
// veer_left
{digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
}
 
  if (Bearing > 136 && Bearing < 269)
// veer_right
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, HIGH);
}
}
 
if (TarLat == ActLat && TarLong == ActLong)
// Target found
{Serial.print("Goal! ");
// Halt!
{digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(5, LOW);
 digitalWrite(5, LOW);
}
}
}
