# Openbot-Online
Openbot Online is an IoT remote controlled car. See [here](https://drive.google.com/file/d/1vAvbvAioSfMq6ArK5MM-z32Zgnl8PhDt/view?usp=sharing) for a demo.

The body of the car is based on the Openbot platform - https://www.openbot.org/, which powers a self driving car using a smartphone. Openbot Online uses an IoT messaging protocol called MQTT to pass commands from the React app to the Raspberry Pi, which then sends it to Arduino via an I2C connection. 

##### Wiring Diagram
<img width="568" alt="image" src="https://user-images.githubusercontent.com/62212652/161445781-a698ae27-01ea-40ab-bc96-5675a2cd3c39.png">


