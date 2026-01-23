int sensorPins[7] = {A0, A1, A2, A3, A4, A5, 3};

int sensorMin[7];
int sensorMax[7];
int sensorVal[7];
int normalized[7];

void setup() 
{
  Serial.begin(9600);
  for(int i=0;i<7;i++)
  {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }

  Serial.println("Calibrating... Move sensors over black and white");
  
  unsigned long startTime = millis();
  while(millis() - startTime < 6000)  // 6 seconds calibration
  {  
    for(int i=0;i<7;i++)
    {
      int val = analogRead(sensorPins[i]);
      if(val < sensorMin[i]) 
        sensorMin[i] = val;
      if(val > sensorMax[i]) 
        sensorMax[i] = val;
    }
  }

  Serial.println("Calibration done.");
  Serial.println("Min   Max");

  for(int i=0;i<7;i++)
  {
    Serial.print(sensorMin[i]);
    Serial.print("   ");
    Serial.println(sensorMax[i]);
  }
}

int readNormalize(int i)
{
  int val = analogRead(sensorPins[i]);
  val = constrain(val, sensorMin[i], sensorMax[i]);
  val = map(val, sensorMin[i], sensorMax[i], 0, 1000);
  return val;
}

void loop() 
{
}













