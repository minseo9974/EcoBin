#include<Servo.h>
#include <AFMotor.h>

Servo servo;
Servo servo2;
Servo servo3;
Servo servo4;

AF_Stepper motor(20,2);

int motor1 = 9;
int motor2 = 10;
int motor3 = 11;
int motor4 = 8;

const int buffersize = 64;
char buffer[buffersize];
int bytesRead = 0;

void setup(){
  Serial.begin(9600);
  motor.setSpeed(200);
  servo.attach(motor1);
  servo2.attach(motor2);
  servo3.attach(motor3);
  servo4.attach(motor4);
  servo.write(180);
  servo2.write(0);
  servo3.write(180);
  servo4.write(0);
}

void loop(){

  if (Serial.available()){
      bytesRead = Serial.readBytesUntil('\n', buffer, buffersize);
      buffer[bytesRead]= '\0';
  }

  if(Serial.available() > 0)
  {
    // 결과값이 0이면 can의 개폐칸 작동
    if(buffer[0]=='a'){ 
      Serial.println("can");
      for(int ii=0; ii <= 90; ii++)
      {
        servo.write(180 - ii);
        servo2.write(ii);
        delay(5);
      }
      delay(3000);
      motor.step(360, FORWARD, SINGLE);
      for(int ii=90; ii <= 180; ii++)
      {
        servo.write(ii);
        servo2.write(180 - ii);
        delay(5);
      }
      while (Serial.read() == 'a');
    }
    // 결과값이 1이면 plastic의 개폐칸 작동
    else if(buffer[0]=='b'){
      Serial.println("plastic");
      for(int ii=0; ii <= 90; ii++)
      {
        servo3.write(180 - ii);
        servo4.write(ii);
        delay(5);
      }
      delay(3000);
      motor.step(360,BACKWARD,SINGLE);
      for(int ii=90; ii <= 180; ii++)
      {
        servo3.write(ii);
        servo4.write(180 - ii);
        delay(5);
      }
      while (Serial.read() == 'b');
    }
  }  
}