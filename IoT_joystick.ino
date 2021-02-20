@article{openbot2020,
    author    = {Matthias M\"uller and Vladlen Koltun},
    title     = {{OpenBot}: Turning Smartphones into Robots},
    journal   = {arXiv:2008.10631},
    year      = {2020},
}
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
#define X_pin 0 //joystick x-direction
#define Y_pin 1 //joystick y-direction

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
  
  #if HAS_SPEED_SENSORS
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PIN_SPEED_L), update_speed_left, FALLING);
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(PIN_SPEED_R), update_speed_right, FALLING);
  #endif  
}

//------------------------------------------------------//
// MAIN LOOP
//------------------------------------------------------//

void loop() {
  
  float joy_x = analogRead(X_pin); //read data to joystick variables
  float joy_y = analogRead(Y_pin);
  
  // Send vehicle measurments to serial every SEND_INTERVAL
  if (millis() >= send_timeout) {
    send_vehicle_data();
    send_timeout = millis() + SEND_INTERVAL;
  }

    // drive forward
      
      if(joy_x>450&&joy_x<530) //neutral x is 504
      {
        if(joy_y >500 && joy_y<550) //if both x and y are centered, car does not move
        {
          analogWrite(PIN_PWM_L1,0);
          analogWrite(PIN_PWM_L2,0);
          analogWrite(PIN_PWM_R1,0);
          analogWrite(PIN_PWM_R2,0);
          ctrl_left=0;
          ctrl_right=0;
          Serial.println("not moving");
        }
        if(joy_y < 500) //if x is centered but y<500, car moves forwards
        {
          ctrl_left = 1;
          ctrl_right = 1;
          Serial.println("going forwards");
        }else if(joy_y>550) //neutral y is 523 - if x is centered but y>550, car moves back
        {
          ctrl_left = -1;
          ctrl_right = -1;
          Serial.println("going backwards");
        }
      }else if(joy_x<450) 
      {
          ctrl_left = 1;
          ctrl_right = 0;
          Serial.println("turn left");
      }else if(joy_x>530)
      {
        ctrl_left = 0;
        ctrl_right = 1;
        Serial.println("turn right");
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
