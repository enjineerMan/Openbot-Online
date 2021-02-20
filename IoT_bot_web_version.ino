@article{openbot2020,
    author    = {Matthias M\"uller and Vladlen Koltun},
    title     = {{OpenBot}: Turning Smartphones into Robots},
    journal   = {arXiv:2008.10631},
    year      = {2020},
}
//WIRING: in1 - D5, in2 - D6, in3 - D9, in4 - D10
// Contributors:
//  - October 2020: OLED display support by Ingmar Stapel
// ---------------------------------------------------------------------------

// PIN_PWM_L1,PIN_PWM_L2,PIN_PWM_R1,PIN_PWM_R2  Low-level control of left DC motors via PWM 

//------------------------------------------------------//
// DEFINITIONS
//------------------------------------------------------//

// DO NOT CHANGE!
#define DIY 0
#define PCB_V1 1
#define PCB_V2 2

//------------------------------------------------------//
//SETTINGS
//------------------------------------------------------//

// Setup the OpenBot version (DIY,PCB_V1,PCB_V2)
#define OPENBOT DIY

// WARNING: If the sonar sensor is not setup, the car will go full speed forward!
#define NO_PHONE_MODE 1

//------------------------------------------------------//
// PINOUT
//------------------------------------------------------//
//Setup the pin definitions

#define PIN_PWM_L1 5 //left wheels forward
#define PIN_PWM_L2 6 //left wheels back
#define PIN_PWM_R1 10 //right wheels forward
#define PIN_PWM_R2 9 //right wheels back
#include <Wire.h> //I2C library to connect to Raspberry Pi

//------------------------------------------------------//
// INITIALIZATION
//------------------------------------------------------//

#include <limits.h>
const unsigned int STOP_THRESHOLD = 32; //cm

#if NO_PHONE_MODE
  int turn_direction = 0; // right
  const unsigned long TURN_DIRECTION_INTERVAL = 2000; // How frequently to change turn direction (ms).
  unsigned long turn_direction_timeout = 0;   // After timeout (ms), random turn direction is updated.
#endif

//Vehicle Control
int ctrl_left = 0;
int ctrl_right = 0;
//Voltage measurement
const unsigned int VIN_ARR_SZ = 10;
unsigned int vin_counter = 0;
unsigned int vin_array[VIN_ARR_SZ]={0};

//Speed sensor
const unsigned int DISK_HOLES = 20;
volatile int counter_left = 0;
volatile int counter_right = 0;

//Indicator Signal
const unsigned long INDICATOR_INTERVAL = 500; //Blinking rate of the indicator signal (ms).
unsigned long indicator_timeout = 0;
int indicator_val = 0;

//Serial communication
const unsigned long SEND_INTERVAL = 1000; // How frequently vehicle data is sent (ms).
unsigned long send_timeout = 0;
String inString = "";

//------------------------------------------------------//
// SETUP
//------------------------------------------------------//
char dir=0;
void setup()
{
  //Outputs
  pinMode(PIN_PWM_L1,OUTPUT);
  pinMode(PIN_PWM_L2,OUTPUT);
  pinMode(PIN_PWM_R1,OUTPUT);
  pinMode(PIN_PWM_R2,OUTPUT);

  //Inputs
 
  Serial.begin(115200,SERIAL_8N1); //8 data bits, no parity, 1 stop bit
  send_timeout = millis() + SEND_INTERVAL; //wait for one interval to get readings
  
  Wire.begin(0x8); //begin I2C connection
  Wire.onReceive(receiveEvent); //call receiveEvent whenever data is received
}
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    dir = Wire.read(); // receive car direction as a character (from 0x1 to 0x4)
  }
}
//------------------------------------------------------//
// MAIN LOOP
//------------------------------------------------------//

void loop() {
  
  // Send vehicle measurments to serial every SEND_INTERVAL
  if (millis() >= send_timeout) {
    send_vehicle_data();
    send_timeout = millis() + SEND_INTERVAL;
  }
      //change left and right controls according to input value from RPI
      if(dir==0x1) //forwards
      {
        ctrl_left = 1;
        ctrl_right = 1;
        Serial.println("going forwards");
      }else if(dir==0x2) //backwards
      {
        ctrl_left = -1;
        ctrl_right = -1;
        Serial.println("going backwards");
      }else if(dir==0x3) //turn left
      {
        ctrl_left = 1;
        ctrl_right = 0;
        Serial.println("turn left");
      }else if(dir==0x4) //turn right
      {
        ctrl_left = 0;
        ctrl_right = 1;
        Serial.println("turn right");
      }else
      {
          analogWrite(PIN_PWM_L1,0);
          analogWrite(PIN_PWM_L2,0);
          analogWrite(PIN_PWM_R1,0);
          analogWrite(PIN_PWM_R2,0);
          ctrl_left=0;
          ctrl_right=0;
          Serial.println("not moving");
      }

  update_left_motors();
  update_right_motors();
}

//------------------------------------------------------//
// FUNCTIONS
//------------------------------------------------------//

//write ctrl_left and ctrl_right values to motor
void update_left_motors() {
    if (ctrl_left < 0) {
      analogWrite(PIN_PWM_L1,64);
    }
    else if (ctrl_left > 0) {
      analogWrite(PIN_PWM_L2,10);
    }
    else { //Motor brake
      analogWrite(PIN_PWM_L1,255);
      analogWrite(PIN_PWM_L2,255);
    }
}

void update_right_motors() {
    if (ctrl_right < 0) {
      analogWrite(PIN_PWM_R1,64);
    }
    else if (ctrl_right > 0) {
      analogWrite(PIN_PWM_R2,10);
    }
    else { //Motor brake
      analogWrite(PIN_PWM_R1,255);
      analogWrite(PIN_PWM_R2,255);
    }
}

//this segment came with openbot code, code breaks if removed
void send_vehicle_data() {
//  float voltage_value = get_voltage();
  int ticks_left = counter_left;
  counter_left = 0;
  int ticks_right = counter_right;
  counter_right = 0;
  
  #if (NO_PHONE_MODE || HAS_OLED)
    float rpm_factor = 60.0*(1000.0/SEND_INTERVAL)/(DISK_HOLES);
    float rpm_left = ticks_left*rpm_factor;
    float rpm_right = ticks_right*rpm_factor;
  #endif
  #if (NO_PHONE_MODE)
  //  Serial.print("Voltage: "); Serial.println(voltage_value, 2);
    Serial.print("Left RPM: "); Serial.println(rpm_left, 0);
    Serial.print("Right RPM: "); Serial.println(rpm_right, 0);
//    Serial.print("Distance: "); Serial.println(distance_estimate);
    Serial.println("------------------");
  #else
    Serial.print(voltage_value);
    Serial.print(",");
    Serial.print(ticks_left);
    Serial.print(",");
    Serial.print(ticks_right);
    Serial.print(",");
    Serial.print(distance_estimate);
    Serial.println();
  #endif 
}
