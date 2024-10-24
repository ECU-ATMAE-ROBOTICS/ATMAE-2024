# ATMAE-2024 Shopping Cart

## Overview
This project involves building a robot designed to compete in a 1v1v1v1 object collection challenge at the ATMAE 2024 Student Robotics Compeition. The robot uses a Raspberry Pi 4 and an Arduino Giga R1 WiFi to control various components, including sensors and motors. Each robot competes to collect objects scattered in a square arena. As weel as many other ways to score points. The robot with the most points wins the round!

# Rules and Rubrics
- Rules: https://cdn.ymaws.com/www.atmae.org/resource/resmgr/2024conference/atmae_sdrc_2024_updated_as_o.pdf
- Rubrics: https://cdn.ymaws.com/www.atmae.org/resource/resmgr/2024conference/REV-FINAL-ATMAE_SDRC_24_Rubr.pdf

## Hardware
- Raspberry Pi 4: Acts as the main control unit and recieves in the input from the Xbox controller and sends it to the Ardunio over serial. The Raspberry Pi is also used to stream a video to a phone.
- Arduino Giga R1 WiFi: Handles low-level control of motors, sensors, and parses the serial from the Pi. It communicates with the Raspberry Pi via serial.
- Router: Raspberry Pi and client connects to the router to stream camera to a client (in this case it was someones phone)

## Key Components:
- Motors: REV-41-1291 Hex Motor
- Smart Sensors: PiCamera 
- Power Supply: Dewalt Battery 

