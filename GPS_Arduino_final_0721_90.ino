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
float ActLat;       // gps.location.lat
float ActLong;      // gps.location.lat
float Bearing;      // gps.course.deg
float DiffLat;      // Difference between TarLat and ActLat
float DiffLong;     // Difference between TarLong and ActLong
 
// Connection between GPS and Motor Arduino
// Arduino1 => Arduino2
// GPS         Motors
//    2 -> 10
//    3 -> 11
//    12 -> 12
//    5 -> 13
 
void setup()
{
  Serial.begin(9600);
 
  ss.begin(GPSBaud);
 
  pinMode(2, OUTPUT);    // sets the digital pin as output
  pinMode(3, OUTPUT);    // sets the digital pin as output
  pinMode(12, OUTPUT);    // sets the digital pin as output
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
 
// ActLat = 30.513465;   // test coordinates
// ActLong = -84.237213;
 
// ActLat = 19.492306; // test coordinates
// ActLong = -99.116716;
 
// Actual bearing
 Bearing = gps.course.deg();
// Bearing = 0; // test bearings
// Bearing = 300;
// Bearing = 180;
// Bearing = 270;
// Bearing = 45;
 
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
 
if (TarLat > ActLat && TarLong == ActLong)
// Travel North 316-360 or 0-45 (0°)
    {Serial.print("North ");
 
if (Bearing >= 316 || Bearing <= 45)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
 
if (Bearing > 45 && Bearing <= 180)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
 
if (Bearing < 316 && Bearing > 180)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
}
 
if (TarLat > ActLat && TarLong > ActLong)
// Travel North East 0-90 (45°)
{Serial.print("NorthEast ");

if (Bearing >= 0 && Bearing <= 90)
// forward
{Serial.print("forward ");
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
 
if (Bearing > 90 && Bearing <= 225)
// veer_left
{Serial.print("veer_left ");
     digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
 
if (Bearing < 360 && Bearing > 225)
// veer_right
{Serial.print("veer_right ");
     digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
}
 
if (TarLat == ActLat && TarLong > ActLong)
// Travel East 46-135 (90°)
{Serial.print("East ");

if (Bearing >= 46 && Bearing <= 135)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
 
if (Bearing < 46 || Bearing >= 270)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
 
if (Bearing > 135 && Bearing < 270)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
}
 
if (TarLat < ActLat && TarLong > ActLong)
// South East 90-180 (135°)
{Serial.print("SouthEast ");

if (Bearing >= 91 && Bearing <= 180)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
    
if (Bearing < 91 || Bearing >= 315)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }

if (Bearing > 180 && Bearing < 315)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
}
 
if (TarLat < ActLat && TarLong == ActLong)
// Travel South 135-225 (180°)
{Serial.print("South ");

if (Bearing >= 136 && Bearing <= 225)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }

if (Bearing < 136 && Bearing >= 0)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
 
if (Bearing > 225 && Bearing <= 359)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
 }
 
if (TarLat < ActLat && TarLong < ActLong)
// Travel South West 181-270 (225°)
{Serial.print("SouthWest ");

if (Bearing >= 181 && Bearing <= 270)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }

if (Bearing < 181 && Bearing >= 45)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
 
if (Bearing > 270 || Bearing < 45)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
} 
 
if (TarLat == ActLat && TarLong < ActLong)
// Travel West 226-315 (270°)
{Serial.print("West ");

if (Bearing >= 226 && Bearing <= 315)
// forward
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
 
if (Bearing < 226 && Bearing >= 90)
// veer_right
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, HIGH);
    }
 
if (Bearing > 315 || Bearing < 90)
// veer_left
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
}
 
if (TarLat > ActLat && TarLong < ActLong)
// Travel North West 271-360 (315°)
{Serial.print("NorthWest ");
 
if (Bearing >= 271 && Bearing <= 360)
// forward
Serial.print("forward ");
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
     digitalWrite(5, LOW);
    }
 
if (Bearing > 0 && Bearing <= 135)
// veer_left
Serial.print("veer_left ");
    {digitalWrite(2, HIGH);
     digitalWrite(3, HIGH);
     digitalWrite(12, LOW);
     digitalWrite(5, HIGH);
    }
 
if (Bearing < 271 && Bearing > 135)
// veer_right
Serial.print("veer_right ");
    {digitalWrite(2, LOW);
     digitalWrite(3, LOW);
     digitalWrite(12, HIGH);
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
