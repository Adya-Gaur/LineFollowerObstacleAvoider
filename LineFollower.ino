/*An autonomous robot that follows a black line using. It uses two infrared sensors to identify black and white surfaces.
Debugging - Open Serial Monitor. Move robot manually over: Black line, White surface, Observe behavior.*/

int IR_L = 12, IR_R = 4; 
int L_IN1 = 7, L_IN2 = 8, R_IN1 = 9, R_IN2 = 10, ENA = 6, ENB = 11;
int leftSensor, rightSensor;

void setup() 
{
  Serial.begin(9600);
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() 
{
  leftSensor = digitalRead(IR_L);
  rightSensor = digitalRead(IR_R);
  Serial.print("L: ");
  Serial.print(leftSensor);
  Serial.print("  R: ");
  Serial.println(rightSensor);

  if (leftSensor == HIGH && rightSensor == HIGH) // BOTH SENSORS ON BLACK → MOVE FORWARD
    forward();

  else if (leftSensor == HIGH && rightSensor == LOW) // LEFT SENSOR ON BLACK → TURN LEFT
    turnLeft();
  
  else if (leftSensor == LOW && rightSensor == HIGH) // RIGHT SENSOR ON BLACK → TURN RIGHT
    turnRight();

  else  // BOTH ON WHITE → STOP
    stopRobot();
}

    //Motor functions
void forward() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
}

void turnLeft() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 70);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(EN, 150);
}

void turnRight() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 150);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENB, 70);
}

void stopRobot() 
{
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
}

