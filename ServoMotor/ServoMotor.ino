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
  int result = Serial.read();
  // 결과값이 0이면 can의 개폐칸 작동
  if(result==0){ 
    for(int ii=0; ii < 120; ii++)
    {
     servo.write(ii);
     servo2.write(ii);
     Serial.println(can);
      delay(5);
    }
   delay(3000);

  }
  // 결과값이 1이면 plastic의 개폐칸 작동
  else if(result==1){
    for(int i = 120; i >= 0; i--)
    {
      servo3.write(i);
      servo4.write(i);
      Serial.println(plastic);
      delay(5);
    }
    delay(3000);
  }  
}