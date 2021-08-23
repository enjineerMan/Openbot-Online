//WIRING: in1 - D5, in2 - D6, in3 - D9, in4 - D10
//analog joystick values (with pin definitions on left): left to right - x-axis 0 to 1000, up to down - y-axis 0 to 1000 
// PIN_PWM_L1,PIN_PWM_L2,PIN_PWM_R1,PIN_PWM_R2  Low-level control of left DC motors via PWM 
//------------------------------------------------------//
// DEFINITIONS
//------------------------------------------------------//
//------------------------------------------------------//
//SETTINGS
//------------------------------------------------------//
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
#define X_pin A1 //joystick x-direction
#define Y_pin A0 //joystick y-direction
//------------------------------------------------------//
// INITIALIZATION
//------------------------------------------------------//
#include <limits.h>
#include <Wire.h>
#include <ArduinoJson.h>
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
char new_data;
char left;
char right;
char up;
char down;
//------------------------------------------------------//
// SETUP
//------------------------------------------------------//
void setup()
{
  //Outputs
  pinMode(PIN_PWM_L1,OUTPUT);
  pinMode(PIN_PWM_L2,OUTPUT);
  pinMode(PIN_PWM_R1,OUTPUT);
  pinMode(PIN_PWM_R2,OUTPUT);
  //Inputs
  
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
  Serial.begin(115200,SERIAL_8N1); //8 data bits, no parity, 1 stop bit
  send_timeout = millis() + SEND_INTERVAL; //wait for one interval to get readings
  
  #if HAS_SPEED_SENSORS
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PIN_SPEED_L), update_speed_left, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PIN_SPEED_R), update_speed_right, FALLING);
  #endif  
}
void receiveEvent(int howMany) {
  String msg = "";
  DynamicJsonDocument doc(1024);
  
  while(Wire.available()) {
    new_data = Wire.read();
    msg+=new_data;
    
  }

  msg = msg.substring(2);
  //Serial.println(msg);
  left = msg.charAt(0);
  right = msg.charAt(1);
  down = msg.charAt(2);
  up = msg.charAt(3);
  
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
    // drive forward
//      Serial.println("joy x: "+String(joy_x));
//      Serial.println("joy y: "+String(joy_y));
  if(left == '1' && right == '0'){
    ctrl_left = 1;
  }else if(right == '1' && left == '0'){
    ctrl_right = 1;
  }else if(up == '1'){
    Serial.println("go forwards");
    ctrl_left = 1;
    ctrl_right = 1;
  }else if (down == '1'){
    ctrl_left = -1;
    ctrl_right = -1;
  }else{
    ctrl_left = 0;
    ctrl_right = 0;
  }

  update_left_motors();
  update_right_motors();
}
//------------------------------------------------------//
// FUNCTIONS
//------------------------------------------------------//
//write ctrl_left and ctrl_right values to motor
void update_left_motors() {
    if (ctrl_left == -1) {
      analogWrite(PIN_PWM_L1,64); 
    }
    else if (ctrl_left == 1) {
      analogWrite(PIN_PWM_L2,64);
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
  #else
  #endif 
}
