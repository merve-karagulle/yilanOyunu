int joyX = A0;
int joyY = A1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  Serial.print(xValue);
  Serial.print(",");
  Serial.println(yValue);
  delay(100);
}

