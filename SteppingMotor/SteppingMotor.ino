#include <AFMotor.h>

AF_Stepper motor(20,2);
void setup() {
  Serial.begin(9600);
  Serial.println("Stepper test");

  motor.setSpeed(200);
}

void loop() {
  Serial.println("Single coil steps");
  motor.step(200, FORWARD, SINGLE);
  motor.step(200, BACKWARD, SINGLE);

  Serial.println("Double coil steps");
  motor.step(200, FORWARD, DOUBLE);
  motor.step(200, BACKWARD, DOUBLE);

  Serial.println("Interleave coil steps");
  motor.step(200, FORWARD, INTERLEAVE);
  motor.step(200, BACKWARD, INTERLEAVE);

  Serial.println("Micrsostep steps");
  motor.step(200, FORWARD, MICROSTEP);
  motor.step(200, BACKWARD, MICROSTEP);

}
