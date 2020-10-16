#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

#define trigPin A4
#define echoPin A5
#define maxDistance 200
#define collDist 15

NewPing sonar(trigPin, echoPin, maxDistance);
Servo myServo;
AF_DCMotor rightBackMotor(1,MOTOR12_1KHZ);
AF_DCMotor rightFrontMotor(2, MOTOR12_1KHZ);
AF_DCMotor leftFrontMotor(3,MOTOR34_1KHZ);
AF_DCMotor leftBackMotor(4,MOTOR34_1KHZ);

int distance = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);
  myServo.attach(10);
  myServo.write(90);
  turnUpSpeed();
  moveStop();
  distance = readPing();
  delay(100);
}

void loop() {
  int distRight = 0;
  int distLeft = 0;
  delay(50);
  if(distance <= collDist){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distRight = lookRight();
    delay(200);
    distLeft = lookLeft();
    delay(200);
    if(distance >= distLeft){
      turnRight();
      moveStop();
    }
    else{
      turnLeft();
      moveStop();
    }
  }
  else{
    moveForward();
  }
  distance = readPing();
}

int readPing(){
  int dist_cm;
  dist_cm = sonar.ping_cm();
  return dist_cm;
}

void turnUpSpeed(){
  leftFrontMotor.setSpeed(200);
  leftBackMotor.setSpeed(200);
  rightBackMotor.setSpeed(200);
  rightFrontMotor.setSpeed(200);
}

void turnRight(){
  int distance = 0;
  for(int i = 0; i < 9; i++){
    leftFrontMotor.run(FORWARD);
    leftBackMotor.run(BACKWARD);
    rightBackMotor.run(BACKWARD);
    rightFrontMotor.run(FORWARD);
    delay(200);
    leftFrontMotor.run(FORWARD);
    leftBackMotor.run(BACKWARD);
    rightBackMotor.run(FORWARD);
    rightFrontMotor.run(BACKWARD);
    distance = readPing();
    if(distance > collDist)
    continue;
    else break;
  }
}

void turnLeft(){
  int distance = 0;
  for(int i = 0; i < 9; i++){
    leftFrontMotor.run(BACKWARD);
    leftBackMotor.run(FORWARD);
    rightBackMotor.run(FORWARD);
    rightFrontMotor.run(BACKWARD);
    delay(200);
    leftFrontMotor.run(FORWARD);
    leftBackMotor.run(BACKWARD);
    rightBackMotor.run(FORWARD);
    rightFrontMotor.run(BACKWARD);
    distance = readPing();
    if(distance > collDist)
    continue;
    else break;
  }
}

void moveStop(){
  leftFrontMotor.run(RELEASE);
  leftBackMotor.run(RELEASE);
  rightBackMotor.run(RELEASE);
  rightFrontMotor.run(RELEASE);
}

void moveForward(){
  leftFrontMotor.run(FORWARD);
  leftBackMotor.run(BACKWARD);
  rightBackMotor.run(FORWARD);
  rightFrontMotor.run(BACKWARD);
}

void moveBackward(){
  leftFrontMotor.run(BACKWARD);
  leftBackMotor.run(FORWARD);
  rightBackMotor.run(BACKWARD);
  rightFrontMotor.run(FORWARD);
}

int lookLeft(){
  myServo.write(180);
  delay(500);
  int distance = readPing();
  delay(100);
  myServo.write(90);
  return distance;
  delay(100);
}

int lookRight(){
  myServo.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  myServo.write(90);
  return distance;
  delay(100);
}
