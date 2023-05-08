// Define pins for ultrasonic sensor
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send a pulse to the ultrasonic sensor to trigger measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of the echo pulse from the sensor
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in centimeters based on the duration
  int distance = duration * 0.034 / 2;
  
  // Output the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Wait a moment before measuring again
  delay(500);
}
