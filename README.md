# Smart Robot System  

This project consists of multiple modules, each with its own functionality, working together as an intelligent system. The Main module is the master module manages communication and control over the modules via **two CAN buses (CAN1 and CAN2)**, both operating with the same functionality. Additionally, the system supports Bluetooth control, allowing remote operation.  

The files in this repository provide a sample implementation to demonstrate the core concept of the system.  

## Features  
- **FreeRTOS** – Manages multitasking efficiently.  
- **Buttons & LEDs** – Handles user input and status indication.  
- **CAN Module** – Enables communication between microcontrollers using CAN1 and CAN2.  
- **Speaker Control** – Manages system ringtones and audio feedback.  
- **Menu & Keys** – Provides an interface for controlling modules via GLCD.  
- **Bluetooth Buffer** – Manages received Bluetooth messages before forwarding them via CAN.  

