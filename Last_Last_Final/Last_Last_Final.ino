#include <Servo.h>
#include <AFMotor.h>

Servo servo;
Servo servo2;
Servo servo3;
Servo servo4;

AF_Stepper motor(60, 2);
int currentPosition;
const int stepsPerRevolution = 200;
const int targetPosition = 400;

const int trigPin1 = 2;
const int echoPin1 = 3;

const int trigPin2 = 4;
const int echoPin2 = 5;

int motor1 = 9;
int motor2 = 10;
int motor3 = 11;
int motor4 = 7;

const int buffersize = 64;
char buffer[buffersize];
int bytesRead = 0;

const int notifyDistance = 20;

void setup() {
  Serial.begin(115200);

  motor.setSpeed(200);
  servo.attach(motor1);
  servo2.attach(motor2);
  servo3.attach(motor3);
  servo4.attach(motor4);
  servo.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  delay(3000);
  servo.write(95);
  servo2.write(95);
  servo3.write(65);
  servo4.write(65);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  static unsigned long previousMillis = 0;
  unsigned long interval = 2000;

  if (Serial.available()) {
    bytesRead = Serial.readBytesUntil('\n', buffer, buffersize);
    buffer[bytesRead] = '\0';
  }

  if (Serial.available() > 0) {
    if (buffer[0] == 'a') {
      for (int ii = 0; ii <= 180; ii++) {
        servo.write(ii);
        servo2.write(ii);
        delay(5);
      }


      currentPosition = 0;
      while (1) {
        if (currentPosition < targetPosition) {
          motor.step(1, FORWARD, SINGLE);
          currentPosition++;
        }
        else {
          motor.release();
          break;
        }
      }

      servo.write(0);
      servo2.write(0);
      delay(2000);
      servo.write(95);
      servo2.write(95);

      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        int distance1 = measureDistance(trigPin1, echoPin1);

        if (distance1 <= notifyDistance) {
          Serial.println("test1");
        }
      }

      while (Serial.read() == 'a');
    } else if (buffer[0] == 'b') {
      for (int ii = 0; ii <= 180; ii++) {
        servo3.write(ii);
        servo4.write(ii);
        delay(5);
      }

      currentPosition = 0;
      while (1) {
        if (currentPosition < targetPosition) {
          motor.step(1, BACKWARD, SINGLE);
          currentPosition++;
        } else {
          motor.release();
          break;
        }
      }

      for (int ii = 180; ii >= 0; ii--) {
        servo3.write(ii);
        servo4.write(ii);
        delay(5);
      }

      delay(2000);
      servo3.write(65);
      servo4.write(65);

      if (currentMillis - previousMillis >= interval){
        previousMillis = currentMillis;

        int distance2 = measureDistance(trigPin2, echoPin2);

        if (distance2 <= notifyDistance) {
          Serial.println("test2");
        }
      }

      while (Serial.read() == 'b');
    }
  }
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}

