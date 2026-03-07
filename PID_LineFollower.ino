int sensorPins[7] = {A0, A1, A2, A3, A4, A5, 3};
int weight[7] = {-3, -2, -1, 0, 1, 2, 3};
int buzzer = 2;

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
int IN1 =9, IN2 =8, IN3 =7, IN4 =6, ENA =11, ENB =10;


void setup() 
{
  startupMelody();
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(3, INPUT);
  pinMode(2, OUTPUT);

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
  while(millis() - startTime < 10000)  // 10 seconds calibration
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

  calibrationDoneMelody();
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
  nr=0;
  dr=0;
  for(int i = 1; i < 7; i++)
    {
      sensorValNor[i] = readNormalize(i);
      nr = nr + weight[i]*sensorValNor[i];
      dr = dr + sensorValNor[i];
    }
  if(dr == 0) return;
  
  error = (float)nr/dr;

  integral = integral + error;
  derivative = error - lastError;
  lastError = error;

  correction = kp*error + ki*integral + kd*derivative;
  move(correction);

  if(error < threshold)
    lineLost();
}


void move(int cor)
{
  int leftSpeed = baseSpeed + cor;
  int rightSpeed = baseSpeed - cor;
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);  
}


void lineLost()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}


void startupMelody() 
{
  tone(buzzer, 262); delay(150);
  tone(buzzer, 330); delay(150);
  tone(buzzer, 392); delay(150);
  tone(buzzer, 523); delay(250);
  noTone(buzzer);
}


void calibrationDoneMelody() 
{
  tone(buzzer, 392); delay(150);
  tone(buzzer, 330); delay(150);
  tone(buzzer, 262); delay(200);
  delay(100);
  tone(buzzer, 262); delay(300);
  noTone(buzzer);
}

