## 📌 Overview
This repository contains the implementation of two beginner-level autonomous mobile robots:
- **Line Follower Robot**
- **Obstacle Avoider Robot**

The primary goal of this project is to build a strong foundation in **robot sensing**, **decision-making logic**, and **motor control using PWM** with Arduino.

---

## ✨ Features
- Line tracking using IR reflective sensors  
- Smooth turning using PWM-based motor speed control  
- Obstacle detection using ultrasonic sensor (HC-SR04)  
- Intelligent direction selection by comparing left and right clearance  
- Modular and readable motor control functions  

---

## 🧰 Hardware Used
- Arduino Uno / Nano  
- IR Line Sensors (2)  
- Ultrasonic Sensor (HC-SR04)  
- L298N Motor Driver  
- DC Gear Motors  
- 2WD Robot Chassis  
- 7.4V Li-ion Battery Pack (2 × 18650 cells)  

---

## ⚙️ Working Principle

### 🚗 Line Follower
- IR sensors detect black and white contrast on the surface.
- Motor speeds are adjusted using PWM instead of stopping motors.
- Continuous motion ensures smooth turns and prevents stalling.

### 🚧 Obstacle Avoider
- The ultrasonic sensor measures distance in front of the robot.
- When an obstacle is detected within a threshold distance:
  - The robot checks clearance on the left and right.
  - The robot turns toward the direction with more free space.

---

### Learnings
-
-
-
-
-
-
