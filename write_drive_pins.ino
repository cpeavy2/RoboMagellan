// Write Drive Pins

// The code makes the digital pin 13 an OUTPUT and toggles it by alternating between HIGH and LOW at one second pace.
 
void setup() {
  pinMode(5, OUTPUT);    // sets the digital pin as output
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}
 
void loop() {
  digitalWrite(5, HIGH); // sets the digital pin on
  digitalWrite(4, HIGH);  // sets the digital pin off
  digitalWrite(3, HIGH); // sets the digital pin on
  digitalWrite(2, HIGH);  // sets the digital pin off
}
