# Smart Robot System  

This project consists of multiple modules, each with its own functionality, working together as an intelligent system. The **Main module** is the master, managing communication and control over the modules via **two CAN buses (CAN1 and CAN2)**, both operating with the same functionality. Additionally, the system supports **Bluetooth control**, allowing remote operation. A **GLCD-based menu** provides direct control from the Main module.  

## System Overview  
The system consists of six modules, all based on **STM32F4**, except for the Intelligent Module, which runs on **Khadas VIM3**:  
- **Arm Module** – Controls robotic arm movement.  
- **Motors Module** – Manages motor control and actuation.  
- **Sensors Module** – Handles environmental sensing and data acquisition.  
- **Inverted Pendulum Module** – Implements balance control for the pendulum system.  
- **Intelligent Module** – Processes advanced algorithms and decision-making (*Runs on Khadas VIM3*).  
- **Main Module** – The master module that manages communication (*Runs on STM32F4*).  

The **Main module** receives messages via **Bluetooth**, extracts the frame, checks the **unit ID**, and forwards it to the target module over **CAN1 or CAN2**.  

The files in this repository provide a **sample implementation** to demonstrate the core concept of the system.  

## Features  
- **FreeRTOS** – Manages multitasking efficiently.  
- **Buttons & LEDs** – Handles user input and status indication.  
- **CAN Module** – Enables communication between microcontrollers using CAN1 and CAN2.  
- **Speaker Control** – Manages system ringtones and audio feedback.  
- **Menu & Keys** – Provides an interface for controlling modules via GLCD.  
- **Bluetooth Buffer** – Manages received Bluetooth messages before forwarding them via CAN.  
