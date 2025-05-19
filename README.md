# 🔆 Optical Communication & Sensor Control System Using Arduino Uno R3

## 🔧 Project Overview

This project implements an **optical communication system** using an LED transmitter 💡 and a photoresistor receiver 🌞 to create a wireless data link through light signals. The entire system is built and controlled using an **Arduino Uno R3** 🛠️.

Alongside the core optical communication system, two mini-projects run simultaneously on the same Arduino board:

- 🎮 **Joystick-Controlled Fan Movement:**  
  The joystick module is used to control the speed and direction of a fan motor 🌬️ in real time.

- 📡 **Ultrasonic Sensor Distance Measurement:**  
  An ultrasonic sensor measures distance 📏, and the data is displayed live on an LCD screen 🖥️ connected to the Arduino.

These components collectively demonstrate a multifunctional system combining optical data transmission with interactive sensor controls and output displays.



### ✅ Core Requirements
- Implement a functional **optical communication loop** (LED 💡 → photoresistor 🌞).
- Use a 9-byte communication message format 📦.
- Ensure all hardware is pre-wired and ready to demonstrate without live reprogramming ⚡.
- Integrate joystick input 🎮 to control fan movement 🌬️.
- Display ultrasonic sensor readings 📡 on an LCD 🖥️.



## 🛠️ Hardware Used

- 🛠️ Arduino Uno R3  
- 💡 White LED  
- 🌞 Photoresistor  
- 🎮 Joystick module  
- 🌬️ Fan and fan motor  
- 📡 Ultrasonic sensor  
- 🖥️ LCD display  
- 🟫 Breadboard  
- 🔌 26 wires  
- 🔀 2 jumper wires  
- 🔌 USB cable  
- 🎚️ Potentiometer  
- ⚡ Resistors:  
- 2 × 220 Ω  
- 1 × 100k Ω  
- 🥤 Optional: Straw for LED focusing

  # 📸 Real-life Arduino Setup

Here is a photo of the actual Arduino setup used in this project, featuring the photoresistor and LED wiring. ⚡️🔆

![Arduino Setup](hardware_setup.png)



  

| Byte Index | Description                      | Value / Notes                                                      |
| ---------- | -------------------------------- | ------------------------------------------------------------------ |
| 0          | **Start Byte**                   | `0x70` (Start of message indicator)                                |
| 1          | **Button State (Unused)**        | Set to `0` (unused)                                                |
| 2          | **Tilt Switch State (Unused)**   | Set to `0` (unused)                                                |
| 3          | **Potentiometer (Unused in SW)** | Hardware exists, range `0` to `99`, but not used in software logic |
| 4          | **Sensor A (Distance)**          | Range: `0` to `99` — ultrasonic sensor distance (shown on LCD)     |
| 5          | **Sensor B**                     | Range: `0` to `99` — joystick movement for fan/motor control       |
| 6          | **Sensor C (Unused)**            | Set to `0` (unused)                                                |
| 7          | **Sensor D (Unused)**            | Set to `0` (unused)                                                |
| 8          | **(Unused / Reserved)**          | Set to `0` (optional placeholder if you want to keep 9 bytes)      |
| 9          | **Stop Byte**                    | `0x71` (End of message indicator)                                  |


## ⚠️ Important

However, there are a lot of unused bytes in the message, which makes transmission slower than necessary.  
I only implemented this because it was a requirement from my university. 📚


## 📜 Notes

- All mini-projects run simultaneously on a single Arduino board ⚙️.
- Make sure to adjust the photoresistor threshold based on the ambient light environment 🌞⚡ to ensure reliable optical data reception.
- There is still availability to transmit more projects, but the number of pins on the Arduino Uno R3 may become a limitation 🛑📌.
- Using an Arduino Mega would provide more pins and allow for additional expansions, as this project uses all pins except pins 2  🛠️➡️📏.

  
<br>

## 🚀 How to Run

### Step 1: ⚠️ Important: You must clone this repository first before doing anything else!
**🔄 Clone this repository**
```bash
https://github.com/MohamedHamouda23/Arduino-communications-loop
```


### Step 2: 🔌 Prepare Your Hardware


### Step 3: 💻 Open the Code in Arduino IDE


 1. Open main.ino (File > Open)

 2. Select your Arduino board (Tools > Board)

 3. Choose the correct COM port (Tools > Port)

### Step 4: ⬆️ Upload the Code


### Step 5: 📡 Open Serial Monitor





