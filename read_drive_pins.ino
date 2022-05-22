// Read drive pins

int a;
int b;
int c;
int d;
 
void setup() {
  Serial.begin(9600);                    // Setup serial monitor for debug
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}
 
void loop() {
 a = digitalRead(13);
 b = digitalRead(12);
 c = digitalRead(11);
 d = digitalRead(10);

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
delay(100);
}
