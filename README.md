# Object Retrieval Robot

This project implements an autonomous robot capable of:
- Detecting objects using vision
- Avoiding obstacles using IR and ultrasonic sensors
- Picking up objects using a servo-based robotic arm
- Returning to a home base using color detection

## System Architecture
The system is divided into three layers:
1. Vision Layer (Python/OpenCV)
2. Navigation Layer (ESP8266)
3. Manipulation Layer (Arduino Servo Arm)

## Arm Control
The robotic arm is controlled using:
- High torque servo for lifting
- Micro servo for claw gripping
- Serial communication for command-based control (PICK, HOME)

## Files
- arm_serial_control.ino → Arduino arm command system
- object_retrieval.ino → Full robot logic with sensors
