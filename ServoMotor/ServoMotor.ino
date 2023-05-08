#include<Servo.h>

Servo servo;
Servo servo2;
Servo servo3;
Servo servo4;

int motor1 = 9;
int motor2 = 10;
int motor3 = 11;
int motor4 = 8;

void setup(){
  Serial.begin(9600);
  servo.attach(motor1);
  servo2.attach(motor2);
  servo3.attach(motor3);
  servo4.attach(motor4);
}

void loop(){
  for(int ii=0; ii < 120; ii++)
  {
    servo.write(ii);
    servo2.write(ii);
    servo3.write(ii);
    servo4.write(ii);
    Serial.println(ii);
    delay(5);
  }
  delay(500);
  for(int i = 120; i >= 0; i--)
  {
    servo.write(i);
    servo2.write(i);
    servo3.write(i);
    servo4.write(i);
    Serial.println(i);
    delay(5);
  }
  delay(500);
}