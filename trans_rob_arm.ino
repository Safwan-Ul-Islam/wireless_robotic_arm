#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid = " ";           // WiFi Name
const char* password = " ";   // WiFi Password
const char* receiverIP = "  "; // Receiver IP address

WiFiUDP udp;

const int VRx1 = A0; // Joystick 1 - X axis (Base rotation)
const int VRy1 = D1; // Joystick 1 - Y axis (Shoulder movement)
const int VRx2 = D2; // Joystick 2 - X axis (Elbow movement)
const int VRy2 = D3; // Joystick 2 - Y axis (Wrist movement)

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  udp.begin(4210);
}

void loop() {
  int baseStick = analogRead(VRx1);     // Joystick 1 X-axis
  int shoulderStick = analogRead(VRy1); // Joystick 1 Y-axis
  int elbowStick = analogRead(VRx2);    // Joystick 2 X-axis
  int wristStick = analogRead(VRy2);    // Joystick 2 Y-axis

  String message = String(baseStick) + "," + String(shoulderStick) + "," + String(elbowStick) + "," + String(wristStick);
  
  udp.beginPacket(receiverIP, 4210);
  udp.print(message);
  udp.endPacket();
  
  Serial.print("Data Sent: ");
  Serial.println(message);
  
  delay(50); // slow down control a little
}
