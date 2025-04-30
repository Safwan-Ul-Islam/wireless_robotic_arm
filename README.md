# 🤖 4DOF Wireless Robotic Arm Using ESP8266 & Dual Joysticks

This project is a DIY **4 Degrees of Freedom (DOF) wireless robotic arm** controlled using **two 5-pin analog joysticks** and **two ESP8266 modules (NodeMCU/Wemos D1 Mini)**. The ESP8266 modules communicate wirelessly via **UDP** to control four servo motors: **Base, Shoulder, Elbow, and Wrist**.

---

## 📦 Components Used

- 2 × ESP8266 NodeMCU / Wemos D1 Mini
- 2 × 5-pin analog joysticks
- 4 × Servo motors (SG90 or MG996R)
- External 5V power supply (2A or higher) for servos
- Jumper wires and breadboard
- Common GND connection for ESP8266 and servo power

---

## 🧠 System Overview

- **Transmitter ESP8266:**
  - Reads two joysticks' X and Y values (4 total analog values)
  - Sends the data over WiFi via UDP

- **Receiver ESP8266:**
  - Listens for UDP packets
  - Parses joystick data and maps it to servo angles
  - Controls 4 servos (Base, Shoulder, Elbow, Wrist)

---

## 🔌 Pin Mapping

### Transmitter ESP8266

| Joystick Channel | ESP8266 Pin |
|------------------|-------------|
| Joystick 1 X     | A0          |
| Joystick 1 Y     | D1 (GPIO5)  |
| Joystick 2 X     | D2 (GPIO4)  |
| Joystick 2 Y     | D3 (GPIO0)  |
| VCC (Both)       | 3.3V        |
| GND (Both)       | GND         |

### Receiver ESP8266

| Servo Function | ESP8266 Pin |
|----------------|-------------|
| Base           | D1 (GPIO5)  |
| Shoulder       | D2 (GPIO4)  |
| Elbow          | D3 (GPIO0)  |
| Wrist          | D4 (GPIO2)  |
| Servo Power    | External 5V |
| GND            | Common GND  |

---

## 🔧 Setup Instructions

### 1. Install Arduino Libraries
- `ESP8266WiFi.h`
- `WiFiUDP.h`
- `Servo.h`

### 2. Flash the Codes
- Upload `transmitter.ino` to ESP #1
- Upload `receiver.ino` to ESP #2

### 3. Configure WiFi
In both sketches, update the following:
```cpp
const char* ssid = " ";         // Your WiFi name
const char* password = "  "; // Your WiFi password
