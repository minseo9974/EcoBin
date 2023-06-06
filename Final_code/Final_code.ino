#include<Servo.h>
#include <AFMotor.h>

Servo servo;
Servo servo2;
Servo servo3;
Servo servo4;

AF_Stepper motor(20, 2);

// 초음파 센서 1에 대한 핀들을 지정합니다.
const int trigPin1 = 2;
const int echoPin1 = 3;

// 초음파 센서 2에 대한 핀들을 지정합니다.
const int trigPin2 = 4;
const int echoPin2 = 5;

int motor1 = 9;
int motor2 = 10;
int motor3 = 11;
int motor4 = 7;

const int buffersize = 64;
char buffer[buffersize];
int bytesRead = 0;

// 알림을 보낼 거리의 기준값을 설정합니다.
const int notifyDistance = 10; // 10cm

void setup() {
  Serial.begin(115200);
  motor.setSpeed(200);
  servo.attach(motor1);
  servo2.attach(motor2);
  servo3.attach(motor3);
  servo4.attach(motor4);
  servo.write(180);
  servo2.write(0);
  servo3.write(180);
  servo4.write(0);

  // Serial 통신을 초기화합니다.
  Serial.begin(9600);
  
  // 초음파 센서 1에 대한 핀 모드를 설정합니다.
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // 초음파 센서 2에 대한 핀 모드를 설정합니다.
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}



void loop() {


          // 현재 시간을 저장합니다.
  unsigned long currentMillis = millis();
  
  // 이전 측정 시간과의 차이를 계산합니다.
  static unsigned long previousMillis = 0;
  unsigned long interval = 2000; // 2초

  if (Serial.available()) {
    bytesRead = Serial.readBytesUntil('\n', buffer, buffersize);
    buffer[bytesRead] = '\0';
  }

  if (Serial.available() > 0) {
    // 결과값이 0이면 can의 개폐칸 작동
    if (buffer[0] == 'a') {
      Serial.println("can");
      
      // 서보 모터를 이용하여 "can"의 개폐칸 동작을 수행합니다.
      for (int ii = 0; ii <= 90; ii++) {
        servo.write(180 - ii);
        servo2.write(ii);
        delay(5);
      }
      
      delay(3000);
      
      // 스텝 모터를 이용하여 회전시킵니다.
      motor.step(360, FORWARD, SINGLE);
      
      // 서보 모터를 이용하여 "can"의 개폐칸 역동작을 수행합니다.
      for (int ii = 90; ii <= 180; ii++) {
        servo.write(ii);
        servo2.write(180 - ii);
        delay(5);
      }


      // 일정 간격으로 측정을 수행합니다.
  if (currentMillis - previousMillis >= interval) {
    // 이전 측정 시간을 업데이트합니다.
    previousMillis = currentMillis;

    // 초음파 센서 1에 대한 거리를 측정합니다.
    int distance1 = measureDistance(trigPin1, echoPin1);

    // 각 센서의 거리를 시리얼 모니터에 출력합니다.
    Serial.print("Can Distance: ");
    Serial.print(distance1);
    Serial.println(" cm");

  
    // 거리가 알림 기준값 이하인 경우 알림을 보냅니다.
    if (distance1 <= notifyDistance ) {
      // 시리얼 모니터에 알림을 출력합니다.
      Serial.println("can message send");
      // 여기에 실제로 알림을 보내는 코드를 추가할 수 있습니다. (예: 부저, LED 등)
    }
  }
      while (Serial.read() == 'a');
    }
    
    // 결과값이 1이면 plastic의 개폐칸 작동
    else if (buffer[0] == 'b') {
      Serial.println("plastic");
      
      // 서보 모터를 이용하여 "plastic"의 개폐칸 동작을 수행합니다.
      for (int ii = 0; ii <= 90; ii++) {
        servo3.write(180 - ii);
        servo4.write(ii);
        delay(5);
      }
      
      delay(3000);
      
      // 스텝 모터를 이용하여 회전시킵니다.
      motor.step(360, BACKWARD, SINGLE);
      
      // 서보 모터를 이용하여 "plastic"의 개폐칸 역동작을 수행합니다.
      for (int ii = 90; ii <= 180; ii++) {
        servo3.write(ii);
        servo4.write(180 - ii);
        delay(5);
      }


      // 일정 간격으로 측정을 수행합니다.
  if (currentMillis - previousMillis >= interval) {
    // 이전 측정 시간을 업데이트합니다.
    previousMillis = currentMillis;


    // 초음파 센서 2에 대한 거리를 측정합니다.
    int distance2 = measureDistance(trigPin2, echoPin2);

    // 각 센서의 거리를 시리얼 모니터에 출력합니다.

    Serial.print("Plastic Distance: ");
    Serial.print(distance2);
    Serial.println(" cm");
  
    // 거리가 알림 기준값 이하인 경우 알림을 보냅니다.
    if (distance2 <= notifyDistance) {
      // 시리얼 모니터에 알림을 출력합니다.
      Serial.println("plastic message send");
      // 여기에 실제로 알림을 보내는 코드를 추가할 수 있습니다. (예: 부저, LED 등)
    }
  }
      while (Serial.read() == 'b');
    }
  }
}
// 초음파 센서의 거리를 측정하는 함수
int measureDistance(int trigPin, int echoPin) {
  // 초음파를 보내 측정을 시작합니다.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 초음파를 보낸 후 센서로부터 돌아오는 에코 신호의 지속 시간을 측정합니다.
  long duration = pulseIn(echoPin, HIGH);
  
  // 에코 신호의 지속 시간으로 거리를 계산합니다. (단위: cm)
  int distance = duration * 0.034 / 2;

  // 측정된 거리를 반환합니다.
  return distance;
}
