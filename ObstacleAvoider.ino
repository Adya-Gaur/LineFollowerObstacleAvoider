#include <Servo.h>

int trigPin = 5, echoPin = 6;
int L_IN1 = 7, L_IN2 = 8, R_IN1 = 9, R_IN2 = 10, servoPin = 3, ENA = 6, ENB = 11;
Servo scanServo;

void setup() 
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(L_IN1, OUTPUT);
  pinMode(L_IN2, OUTPUT);
  pinMode(R_IN1, OUTPUT);
  pinMode(R_IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  scanServo.attach(servoPin);
  scanServo.write(90); // face forward
}

void loop() 
{
  int frontDist = getDistance();
  if (frontDist > safeDistance)
    forward();
  else 
  {
    stopRobot();
    delay(200);

    scanServo.write(150); // Look left
    delay(400);
    int leftDist = getDistance();
    scanServo.write(30); // Look right
    delay(400);
    int rightDist = getDistance();
    scanServo.write(90); // Return to center

    if (leftDist > rightDist) // turn in the direction where obstacles are farther away
    {
      turnLeft();
      delay(400);
    } 
    else 
    {
      turnRight();
      delay(400);
    }
  }
}

// FUNCTIONS -
int getDistance() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  return distance;
}

void forward() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 150);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENA, 150);
}

void turnLeft() 
{
  digitalWrite(L_IN1, LOW);
  digitalWrite(L_IN2, LOW);
  digitalWrite(R_IN1, HIGH);
  digitalWrite(R_IN2, LOW);
  analogWrite(ENB, 150);
}

void turnRight() 
{
  digitalWrite(L_IN1, HIGH);
  digitalWrite(L_IN2, LOW);
  analogWrite(ENA, 150);
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
