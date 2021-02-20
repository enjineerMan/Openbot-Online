#  Raspberry Pi Master for Arduino Slave
#  i2c_master_pi.py
#  Connects to Arduino via I2C
  
#  DroneBot Workshop 2019
#  https://dronebotworkshop.com
 
from smbus import SMBus
 
addr = 0x8 # bus address
bus = SMBus(1) # indicates /dev/ic2-1
 
bus.write_byte(addr, 0x2) #send signal over I2C
