# Openbot-Online
Openbot Online is a robot car that can be controlled wirelessly over the internet.

This project is based on the Openbot platform - https://www.openbot.org/, where you can find the original code and assembly instructions. Openbot supports several accessories including an ultrasonic sensor, speed sensors, battery meter, indicator lights, etc., that are not included here. 

![alt text](https://github.com/enjineerMan/Openbot-Online/blob/main/Arduino/IoT_pic.jpg)

You can start by implementing an analog joystick as a placeholder for the wireless controls, to test the functionality of your robot car. Power the arduino remotely with the battery pack by wiring it [in parallel](https://drive.google.com/file/d/1-fU374w7UUGw3x4KoXRMy0vZBtCq_B5N/view?usp=sharing) with the L298n motor.
![alt text](https://github.com/enjineerMan/Openbot-Online/blob/main/Arduino/cargif.gif)

The frontend is built with React, and includes arrow keys whose keyPressed status is streamed to an MQTT topic, which is received by Raspberry Pi and sent to Arduino via an I2C connection. To establish the I2C connection, hook up Raspberry Pi's SDA, SCL, and ground pins to A4, A5 and GND on the Arduino. 

# Next Steps

1. Integrate Raspberry Pi camera module that displays the car's vision on the webpage
2.  Beautify the car - create a cover that prevents parts from flying out


