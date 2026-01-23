int sensorPins[7] = {A0, A1, A2, A3, A4, A5, 3};
int weight[7] = {-3, -2, -1, 0, 1, 2, 3};

int sensorMin[7];
int sensorMax[7];
int sensorValNor[7];
int normalized[7];

int nr, dr, correction;
float error, integral, derivative;
int kp = 20;
float ki = 0;
int kd = 20;
int baseSpeed = 130;
int IN1 = , IN2 = , IN3 = , IN4 = , ENA = , ENB = ;

void setup() 
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(3, INPUT);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  for(int i=0;i<7;i++)
  {
    sensorMin[i] = 1023;
    sensorMax[i] = 0;
  }
  
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
  for(int i = 1; i < 7; i++)
    {
      sensorValNor[i] = realNormalize(i);
      nr = nr + weight[i]*sensorValNor[i];
      dr = dr + sensorValNor[i];
    }
  error = nr/dr;

  correction = kp*error + ki*integral + kd*derivative
  move(correction);

  if(error < threshold)
    lineLost();
}

void move(int cor)
{
  int leftSpeed = baseSpeed + cor;
  int rightSpeed = baseSpeed - cor;
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);  
}

void lineLost()





