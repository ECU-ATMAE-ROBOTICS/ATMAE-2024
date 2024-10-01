# ATMAE-2024 Shopping Cart
# README IS WORK IN PROGRESS

## Overview
This project involves building a robot designed to compete in a 1v1v1v1 object collection challenge at the ATMAE 2024 Student Robotics Compeition. The robot uses a Raspberry Pi 4 and an Arduino Giga R1 WiFi to control various components, including sensors and motors. Each robot competes to collect objects scattered in a square arena. As weel as many other ways to score points. The robot with the most points wins the round!

# Rules and Rubrics
- Rules(https://cdn.ymaws.com/www.atmae.org/resource/resmgr/2024conference/atmae_sdrc_2024_updated_as_o.pdf)
- Rubrics(https://cdn.ymaws.com/www.atmae.org/resource/resmgr/2024conference/REV-FINAL-ATMAE_SDRC_24_Rubr.pdf)

## Hardware
Raspberry Pi 4: Acts as the main control unit, managing high-level decision-making, communication between modules, and overall strategy.
Arduino Giga R1 WiFi: Handles low-level control of motors, sensors, and other peripherals. It communicates with the Raspberry Pi via serial or wireless connection.
## Key Components:
Motors: To drive the robot and operate object-collecting mechanisms.
Sensors: For object detection, distance measurement, and collision avoidance.
Servo/Linear Actuators: To manipulate arms or collectors.
Power Supply: A battery pack suitable for powering both the Raspberry Pi and the Arduino.
## Software
Raspberry Pi 4
The Raspberry Pi runs the high-level logic, including:

Object detection: Using sensors or camera data to find objects.
Movement control: Commands for driving the motors based on the robot’s position and the object locations.
Strategy: Determines the most efficient path to collect objects and avoid competitors.
Arduino Giga R1 WiFi
The Arduino handles low-level tasks, such as:

Motor control: For driving and steering the robot.
Sensor reading: To detect objects and obstacles.
Actuator control: For manipulating the object collection system.
Communication
The Raspberry Pi and Arduino communicate over a serial connection, with the Pi sending high-level commands to the Arduino, which executes them by controlling motors and sensors.

Setup
Hardware Setup
Assemble the robot: Attach motors, sensors, and actuators to the chassis.
Connect the Raspberry Pi and Arduino: Set up serial or wireless communication between the two.
Power up: Ensure that both the Raspberry Pi and Arduino have adequate power from the battery pack.
Software Setup
Raspberry Pi:
Install the necessary Python or C++ libraries for controlling motors, handling sensor input, and communicating with the Arduino.
Write or load the strategy script to handle object detection and robot control.
Arduino:
Upload the control program that handles low-level motor control and sensor input.
Competition Rules
Objective: Each robot must collect as many objects as possible within a designated time limit.
Arena: A square playing field with objects placed randomly.
Robots: Four robots will compete simultaneously, each controlled by a Raspberry Pi and Arduino setup.
Scoring: Points are awarded for each object collected and returned to the base.
Future Improvements
Integrate more advanced object recognition using machine learning on the Raspberry Pi.
Improve wireless communication between the Raspberry Pi and Arduino for faster response times.
Enhance the collection mechanism for better efficiency and precision.
License
This project is open-source and available under the MIT License.

