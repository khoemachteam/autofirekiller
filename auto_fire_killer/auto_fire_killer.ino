#include <Servo.h>

#define FIRE_SENSOR_APIN A6  // Cảm biến lửa (Analog)
#define FIRE_SENSOR_DPIN A7   // Cảm biến lửa (Digital)
#define RELAY_PIN 2          // Rơ-le báo động
#define SERVO_PIN 3          // Servo
#define START_ANGLE 90

Servo myServo;
// int nguong = 600;  // Ngưỡng phát hiện lửa
int nguong = 1;
bool fireDetected = false; // Trạng thái có lửa hay không
int angle = START_ANGLE;      // Góc servo
bool increasing = true;  // Biến kiểm soát hướng quay

void setup() {
  Serial.begin(9600);
  pinMode(FIRE_SENSOR_APIN, INPUT);
  pinMode(FIRE_SENSOR_DPIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  myServo.attach(SERVO_PIN);
  myServo.write(angle);  // Servo bắt đầu từ vị trí start độ
  digitalWrite(RELAY_PIN, HIGH);  // Bật rơ-le báo động
  delay(1000);
  digitalWrite(RELAY_PIN, LOW);  // Bật rơ-le báo động

}

void loop() {
  int fire_a = analogRead(FIRE_SENSOR_APIN);  // Đọc giá trị cảm biến lửa
  int fire_d = digitalRead(FIRE_SENSOR_DPIN);
  Serial.print("fire_d = ");
  Serial.print(fire_d);
  Serial.print(" | fire_a = ");
  Serial.println(fire_a);

  // Kiểm tra có lửa không
  if (fire_d < nguong) {  
  // if(fire_d == 1){
    Serial.println("🔥 Cảnh báo: Phát hiện lửa!");
    Serial.println("Máy bơm bật");
    digitalWrite(RELAY_PIN, HIGH);  // Bật rơ-le báo động
    fireDetected = true;  // Dừng servo khi có lửa
    delay(1000);
  } else {
    digitalWrite(RELAY_PIN, LOW);  // Tắt cảnh báo
    fireDetected = false;  // Cho phép servo quay tiếp
  }

  // Điều khiển Servo
  if (!fireDetected) {  
    myServo.write(angle);
    // delay(20);
    
    if (increasing) {
      angle += 10;  // Tăng góc
      if (angle >= 180) {
        increasing = false;  // Đổi hướng giảm
      }
    } else {
      angle -= 10;  // Giảm góc
      if (angle <= 0) {
        increasing = true;  // Đổi hướng tăng
      }
    }
  }
  delay(200);
}