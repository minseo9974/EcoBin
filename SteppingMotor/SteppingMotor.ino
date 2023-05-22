#include <AFMotor.h>

AF_Stepper motor(20,2);

void setup() {
  Serial.begin(9600);
  motor.setSpeed(200);
}

void loop() {

  if(Serial.available()>0)
  {
    char CoP = Serial.read();
    if (CoP == 'c')
    {
      Serial.println("Can");
      motor.step(360, FORWARD, SINGLE);
      while (Serial.read() == 'c');
    }
    else if (CoP == 'p')
    {
      Serial.println("Plastic");
      motor.step(360,BACKWARD,SINGLE);
      while (Serial.read() == 'p');
    }
  }
}