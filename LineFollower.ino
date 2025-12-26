/*An autonomous robot that follows a black line using. It uses two infrared sensors to identify black and white surfaces.
Debugging - Open Serial Monitor. Move robot manually over: Black line, White surface, Observe behavior.*/

int IR_L = 2, IR_R = 3; 
int L_IN1 = 8, L_IN2 = 9, R_IN1 = 10, R_IN2 = 11;
int leftSensor, rightSensor;

void setup() 
{
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(R_IN1, OUTPUT);
  pinMode(R_IN2, OUTPUT);
}

void loop() 
{
  leftSensor = digitalRead(IR_L);
  rightSensor = digitalRead(IR_R);

  if (leftSensor == LOW && rightSensor == LOW) // BOTH SENSORS ON BLACK → MOVE FORWARD
    forward();

  else if (leftSensor == LOW && rightSensor == HIGH) // LEFT SENSOR ON BLACK → TURN LEFT
    turnLeft();
  
  else if (leftSensor == HIGH && rightSensor == LOW) // RIGHT SENSOR ON BLACK → TURN RIGHT
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
}

void turnLeft() 
{
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
}

void turnRight() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
}

void stopRobot() 
{
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, LOW);
  digitalWrite(R_IN2, LOW);
}
