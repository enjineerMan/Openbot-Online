# Openbot-Online
Openbot Online is a car that can be controlled wirelessly over the internet. See [here](https://drive.google.com/file/d/1vAvbvAioSfMq6ArK5MM-z32Zgnl8PhDt/view?usp=sharing) for a demo.

The body of the car is based on the Openbot platform - https://www.openbot.org/, where you can find the original code, materials, and assembly instructions. 

![alt text](https://github.com/enjineerMan/Openbot-Online/blob/main/Arduino/IoT_pic.jpg)

The frontend is built with React, and includes arrow keys whose keyPressed status is streamed to an MQTT topic, which is received by Raspberry Pi and sent to Arduino via an I2C connection. 
