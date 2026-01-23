int sensorPins[7] = {A0, A1, A2, A3, A4, A5, 3};
int sensorValues[7];

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i = 0; i < 7; i++) 
  {
    sensorValues[i] = analogRead(sensorPins[i]);
    Serial.print(sensorValues[i]);
    Serial.print("\t");   // tab space
  }
  Serial.println();      // new line
  delay(100);
}
