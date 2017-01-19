# CeilingBot
##What is Ceiling Bot?
Ceiling Bot is a revolutionary technological leap forward in home integration and accessibility. Ceiling Bot uses DC motors to travel along a preinstalled rail track. These motors, among other sensors on the robot, are controlled using an ESP8266. This microcontroller uses MQTT protocol to communicate to an online broker, such as io.adafruit, which can then be integrated to IFTTT and communicate with an Amazon Echo device for voice enabled user interfacing.
##Project Team
Ceiling Bot is a collaborative project between educators and several high school students. Besides revolutionizing home integration, Ceiling Bot provides an oppurtunity for high school students to engage in applied STEM research. 
##Self Setup
Before this code can be used for all functions, several hardware and online services must be configured correctly.
###MQTT Broker
In the current version of the program, the code is set to use the io.adafruit.com cloud MQTT broker. It is currently setup to use an private account. To gain access to this account, use the issues tab to let me know. Another alternative is to set up your own io.adafruit.com account. The CeilingBot.ino file has information on what all the parameters of each block are.
