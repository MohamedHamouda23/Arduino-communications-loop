# 📚 About This Project

This project was originally developed as part of a university assignment at the University of the West of England (UWE) 🏫 and is now shared as part of my personal portfolio and resume.

🛠️ The code is based on a template provided by the university, but I was responsible for completing specific parts of the software and building the hardware required to demonstrate the project.

🛠️ It's here to showcase my work and to help others learn — you're welcome to explore the structure, coding style, and problem-solving approach for educational purposes.

🚫 Please don’t copy or submit it as your own — that would go against academic integrity policies and could be considered plagiarism.

👍 Feel free to use it for inspiration, learn from it, and use what you learn to build something even better!

<br>

# 🔆 Optical Communication & Sensor Control System Using Arduino Uno R3

## 🔧 Project Overview

This project implements an **optical communication system** using a white LED 💡 as the transmitter and a photoresistor 🌞 as the receiver. The system creates a basic wireless data link using light signals and is built on the **Arduino Uno R3** 🛠️.

Alongside the core optical communication, two additional sensor-based subsystems are integrated:

- 🎮 **Joystick-Controlled Fan Movement**  
  A joystick module controls the speed and direction of a small fan motor 🌬️ in real-time.

- 📡 **Ultrasonic Sensor Distance Measurement**  
  An ultrasonic sensor measures distance 📏 and displays the results live on an LCD screen 🖥️.



## ✅ Core Requirements

- Use an Arduino Uno R3 starter kit or anything equivalent include:


### 🛠️ Hardware Components

| Component               | Quantity | Notes                                 |
|------------------------|----------|----------------------------------------|
| Arduino Uno R3         | 1        | Main controller                        |
| White LED              | 1        | Transmitter                            |
| Photoresistor          | 1        | Receiver                               |
| Joystick Module        | 1        | Fan control                            |
| Fan + Motor            | 1        | Controlled by joystick                 |
| Ultrasonic Sensor      | 1        | For distance measurements              |
| LCD Display (16x2)     | 1        | Displays distance data                 |
| Breadboard             | 1        | For component connections              |
| Jumper Wires           | 26       | General wiring                         |
| Potentiometer          | 1        | Used with LCD                          |
| USB Cable              | 1        | For power and data                     |
| Resistors              | 3        | 2 × 220Ω, 1 × 100kΩ                    |
| Straw (optional)       | 1        | To focus LED light                     |



## 🧱 Message Format (9 Bytes)

| Byte Index | Description                      | Value / Notes                                                      |
|------------|----------------------------------|--------------------------------------------------------------------|
| 0          | **Start Byte**                   | `0x70` (Start of message)                                          |
| 1          | **Button State (Unused)**        | Always `0`                                                         |
| 2          | **Tilt Switch State (Unused)**   | Always `0`                                                         |
| 3          | **Potentiometer (Unused)**       | Range: `0-99`, not used in software                                |
| 4          | **Sensor A (Distance)**          | Range: `0-99`, ultrasonic reading                                  |
| 5          | **Sensor B (Joystick)**          | Range: `0-99`, for fan control                                     |
| 6          | **Sensor C (Unused)**            | Always `0`                                                         |
| 7          | **Sensor D (Unused)**            | Always `0`                                                         |
| 8          | **(Reserved)**                   | Always `0` (optional placeholder)                                  |
| 9          | **Stop Byte**                    | `0x71` (End of message)                                            |


> ⚠️ **Note**: The message format includes unused bytes, which introduces inefficiency. This structure was implemented to meet university assignment requirements. 📚



## 🖼️ Real-life Setup

Below is an image of the actual Arduino hardware setup used in this project:

![Arduino Setup](hardware-setup.png)



## 📐 Wiring Diagrams

To recreate or expand this project:

1. Follow the wiring diagrams and hardware list. Reference diagrams to help replicate the project can be found in the [`diagrams`](circuit-diagrams/) folder.
2. Write Arduino code to process incoming signals, control the fan, and display sensor data.



## 📌 Notes

- All components and mini-projects are integrated into a **single Arduino Uno R3**.
- Adjust the **photoresistor threshold** depending on ambient lighting to ensure accurate data reception.
- The project uses **nearly all available pins** on the Arduino Uno. Consider using an **Arduino Mega** for more expandability.
- The wiring diagrams provided are **representational**, not the exact ones used in the original implementation.
- No full video or official schematic exists, as this was a **university project** with constraints.
- ⚠️ **Disclaimer**: All diagrams and logic included in this repository are **based on examples from the official Arduino website**. They are **not specific to this exact project**, but they can be adapted with **appropriate pin adjustments**.



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





