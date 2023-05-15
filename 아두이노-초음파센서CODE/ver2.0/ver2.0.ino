// 초음파 센서를 연결할 핀들을 지정합니다.
const int trigPin = 9;
const int echoPin = 10;

// 알림을 보낼 거리의 기준값을 설정합니다.
const int notifyDistance = 20; // 20cm

void setup() {
  // Serial 통신을 초기화합니다.
  Serial.begin(9600);
  
  // 핀 모드를 설정합니다.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // 초음파 센서에 신호를 보내 측정을 시작합니다.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 초음파를 보낸 후 센서로부터 돌아오는 에코 신호의 지속 시간을 측정합니다.
  long duration = pulseIn(echoPin, HIGH);
  
  // 에코 신호의 지속 시간으로 거리를 계산합니다. (단위: cm)
  int distance = duration * 0.034 / 2;
  
  //  거리를 시리얼 모니터에 출력합니다.
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  //  거리가 알림 기준값 이하인 경우 알림을 보냅니다.
  if (distance <= notifyDistance) {
    // 시리얼 모니터에 알림을 출력합니다.
    Serial.println("Distance within notification threshold");
    // 여기에 실제로 알림을 보내는 코드를 추가할 수 있습니다. (예: 부저, LED 등)
  }
  
  // 다음 측정을 위해 잠시 기다립니다.
  delay(500);
}
