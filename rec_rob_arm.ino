#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>

const char* ssid = " ";   // give ur wifi name
const char* password = "  ";  // wifi password

WiFiUDP udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];

Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo wristServo;

// Variables to smooth movement
int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;
int wristAngle = 90;

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  udp.begin(localUdpPort);
  
  baseServo.attach(D1);      // Base Servo
  shoulderServo.attach(D2);  // Shoulder Servo
  elbowServo.attach(D3);     // Elbow Servo
  wristServo.attach(D4);     // Wrist Servo

  Serial.println("Receiver ready.");
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0;
    }
    
    String data = String(incomingPacket);
    Serial.print("Data Received: ");
    Serial.println(data);
    
    int separator1 = data.indexOf(',');
    int separator2 = data.indexOf(',', separator1 + 1);
    int separator3 = data.indexOf(',', separator2 + 1);
    
    int baseStick = data.substring(0, separator1).toInt();
    int shoulderStick = data.substring(separator1 + 1, separator2).toInt();
    int elbowStick = data.substring(separator2 + 1, separator3).toInt();
    int wristStick = data.substring(separator3 + 1).toInt();
    
    // Map joystick values to servo angles
    int mappedBase = mapWithDeadzone(baseStick, 0, 1023, 0, 180, 20); // DEADZONE ADDED FOR BASE
    int mappedShoulder = map(shoulderStick, 0, 1023, 180, 0); // inverted for shoulder
    int mappedElbow = map(elbowStick, 0, 1023, 0, 180);
    int mappedWrist = map(wristStick, 0, 1023, 0, 180);

    // Smooth movement
    baseAngle = smoothMove(baseAngle, mappedBase, 3);
    shoulderAngle = smoothMove(shoulderAngle, mappedShoulder, 3);
    elbowAngle = smoothMove(elbowAngle, mappedElbow, 3);
    wristAngle = smoothMove(wristAngle, mappedWrist, 3);

    // Move servos
    baseServo.write(baseAngle);
    shoulderServo.write(shoulderAngle);
    elbowServo.write(elbowAngle);
    wristServo.write(wristAngle);
  }
}

// Smooth function
int smoothMove(int current, int target, int step) {
  if (abs(current - target) <= step) return target;
  if (current < target) return current + step;
  else return current - step;
}

// Deadzone mapping function
int mapWithDeadzone(int value, int fromLow, int fromHigh, int toLow, int toHigh, int deadzone) {
  int center = (fromHigh - fromLow) / 2;
  if (abs(value - center) < deadzone) {
    return (toHigh + toLow) / 2;  // Stay at center
  } else {
    return map(value, fromLow, fromHigh, toLow, toHigh);
  }
}
