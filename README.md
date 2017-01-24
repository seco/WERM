# CeilingBot
##What is Ceiling Bot?
Ceiling Bot is a revolutionary technological leap forward in home integration and accessibility. Ceiling Bot uses DC motors to travel along a preinstalled rail track. These motors, among other sensors on the robot, are controlled using an ESP8266. This microcontroller uses MQTT protocol to communicate to an online broker, such as io.adafruit, which can then be integrated to IFTTT and communicate with an Amazon Echo device for voice enabled user interfacing.
##Project Team
Ceiling Bot is a collaborative project between educators and several high school students. Besides revolutionizing home integration, Ceiling Bot provides an oppurtunity for high school students to engage in applied STEM research. 
##Motor Logic Table
Due to the lack of pins that could produce digitial outputs, the code uses 4 pins to control the 2 motors instead of the standard 5 pins. PWM_MOTOR_PIN is an analog PWM pin used for motor speed control. LEG1_MOTOR1_PIN is a digital pin that controls leg 1 of the first motor H bridge. LEG1_MOTOR2_PIN is a digital pin that controls leg 1 of the second motor H bridge. COMMON_LEG2_PIN is a digital pin that controls leg 2 of both motor 1 and motor 2. Below are the truth tables that outline the essential code for controlling dual actuators.

| Function | Leg1 | Leg2 |
|----------|------|------|
| Forward  | HIGH | LOW  |
| Reverse  | LOW  | HIGH |
| Stop     | LOW  | LOW  |
Figure 1: Logic of SN754410 H-bridge motor driver

| Function     | PWM_MOTOR_PIN | LEG1_MOTOR1_PIN | LEG1_MOTOR2_PIN | COMMON_LEG2_PIN |
|--------------|---------------|-----------------|-----------------|-----------------|
| testForward  | Variable      | HIGH            | HIGH            | LOW             |
| testBackward | Variable      | LOW             | LOW             | HIGH            |
| testYawLeft  | N/A           | LOW             | HIGH            | LOW             |
| testYawRight | N/A           | HIGH            | LOW             | LOW             |
Figure 2: Custom MQTT enabled methods for dual actuator drive
##Setup the Project
###MQTT Broker
The current build uses io.adafruit.com as the MQTT broker. Below is a table with all of the dashboard blocks already implemented.

| Block Name (Feed Name is Same) | Type   | Min Value | Max Value | Step | Value Interpretation |
|--------------------------------|--------|-----------|-----------|------|----------------------|
| testMotor1                     | Slider | -1000     | 1000      | 10   | d% PWM Duty Cycle    |
| testMotor2                     | Slider | -1000     | 1000      | 10   | d% PWM Duty Cycle    |
| testForward                    | Slider | 0         | 10000     | 10   | Milliseconds (mS)    |
| testBackward                   | Slider | 0         | 10000     | 10   | Milliseconds (mS)    |
| testYawLeft                    | Slider | 0         | 1000      | 10   | Milliseconds (mS)    |
| testYawRight                   | Slider | 0         | 1000      | 10   | Milliseconds (mS)    |
Figure 3: Current build blocks
Within CeilingBot.ino, near the top under '/**MQTT**/', the MQTT account can be edited. To link your account, edit the server, username, and key variables. After editting this in the MQTT protocol side of the project will be operational.
###Wifi
Within CeilingBot.ino, near the top under '/**WIFI**/', add the details for a local wifi details by editing the variables for SSID and password.
###Breadboard Wiring
Module not finished yet.
