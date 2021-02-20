# Openbot-Online
Openbot Online is a robot car that can be controlled wirelessly over the internet.

![alt text](https://github.com/enjineerMan/Openbot-Online/blob/main/IoT_pic.jpg)
This project is based on the Openbot platform - https://www.openbot.org/, where you can find the code and assembly instructions. Openbot supports several accessories including an ultrasonic sensor, speed sensors, battery meter, indicator lights, etc., that are not included here. 

You can start by implementing an analog joystick as a placeholder for the wireless controls, to test the functionality of your robot car. Power the arduino remotely with the battery pack by wiring it [in parallel](https://drive.google.com/file/d/1-fU374w7UUGw3x4KoXRMy0vZBtCq_B5N/view?usp=sharing) with the L298n motor.
![alt text](https://github.com/enjineerMan/Openbot-Online/blob/main/cargif.gif)

The frontend of the application is an html webpage with four buttons coresponding to forward, backward, turn left, and turn right, that respond when arrow keys are pressed. Each html button exectues a different Python script that writes a unique value to Arduino through an I2C connection. To establish the I2C connection, hook up Raspberry Pi's SDA, SCL, and ground pins to A4, A5 and GND on the Arduino. 

# Next Steps

1. Figure out how to execute Python scripts from HTML, maybe using Django - https://www.youtube.com/watch?v=ERMRVORGvZM&ab_channel=HACKANONS
2. Publish the application
3. Integrate Raspberry Pi camera module that displays the car's vision on the webpage
4. Beautify the car - create a cover that prevents parts from flying out


