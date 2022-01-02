# Embeded-System-Assignments

This repository contains two of my assignments for Embedded system course.

## Saftey Robot
This is a robot that detect gas leak and based on the concentration of the gas turn on its fan or move backward. This robot is implemented using FreeRTOS.

### Description

The robot operates in such a way that when it faces a source of toxic gas leakage, it moves forward to the gas source by commanding its 
wheel while turning on its fan motor to avoid the gas.
But if the distance of the robot from the source of gas leakage is less than the allowable threshold (1 meter) or the concentration of gas near the
robot exceeds the allowable limit, to avoid the risk of explosion, it must turn off its fan and Move backwards from the gas source to enter 
the allowable range or where the gas concentration reaches the allowable limit and then starts again.


### Technology

* PlatformIO 
* Proteus
* Arduino Uno
* Gas detection sensor : MQ2 Sensor
* Measuring the distance to the gas source : Ultrasonic Sensor
* Wheel motor : DC Motors 
* Fan motor : DC Motors 

## Smart Key system
The system layout is as follows: A central node(master) controls a number of smart keys(slaves) that are connected via a ‫‪RS485‬‬ bus.
![alt text](https://github.com/mahtab2/Embeded-System-Assignments/main/asset/smartkey.jpg?raw=true)

### Description
Smart keys can be single or have more bridges. The different 
bridges of these switches can be switched on and off separately via the local buttons or by the central node via a common bus.


The central node has switches with which you can select the desired smart key (select Device.) After selecting
the desired smart key, the status of the continuous key is read through the bus and displayed locally. In addition, after
selecting a specific key in the central node can be done using the local keys on and off the selected key bridges changed.

### Technology

* PlatformIO 
* Proteus
* Arduino Uno
* Simulink
* Stateflow

## Prerequisites

* Proteus Pro 8.10
* Matlab R2020a


