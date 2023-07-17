# Servo and Sensor Control Arduino Code
## Overview
This Arduino sketch controls a Servo motor and two LEDs based on the input from two sensors. The current state of the system, defined by the values read from the sensors, determines the position of the Servo and the status of the LEDs.
## Details
The code uses two sensors connected to digital pins 6 and 7. Based on their digital readings (LOW or HIGH), the state of the system is determined:
* **STATE_1**: Both sensors read LOW.
* **STATE_2**: Sensor 1 reads LOW, and sensor 2 reads HIGH.
* **STATE_3**: Any other combination of sensor readings.

Depending on the current state, the Servo motor (attached to pin 3) is set to a certain position:

* **STATE_1**: Servo is set to 0 degrees.
* **STATE_2**: Servo is set to 90 degrees.
* **STATE_3**: Servo is set to 180 degrees.

In addition, two LEDs (connected to digital pins 4 and 5) have their status set based on the current state:
* **STATE_1**: LED_1 is HIGH, and LED_2 is LOW.
* **STATE_2**: LED_1 is LOW, and LED_2 is HIGH.
* **STATE_3**: Both LEDs are HIGH.

## Usage
To use this code, connect two sensors, a Servo motor, and two LEDs to your Arduino board as described above. Load the sketch onto your Arduino. The Servo position and the status of the LEDs will change based on the input from the sensors.

```c++
// Include the required library
#include <Servo.h>

// Define the pin connections
const int SENSOR_1 = 6;
const int SENSOR_2 = 7;
const int SERVO_PIN = 3;
const int LED_1 = 4;
const int LED_2 = 5;

// Define the system states
enum STATE : int {
  STATE_1,
  STATE_2,
  STATE_3
};

// Define the Servo positions
const int POS_1 = 0;
const int POS_2 = 90;
const int POS_3 = 180;

// Initialize the Servo
Servo MyServo;

void setup() {
  // Begin the serial communication
  Serial.begin(9600);

  // Set the initial state
  currentState = STATE_3; 
  // Define the pin modes
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(LED_1, OUTPUT); 
  pinMode(LED_2, OUTPUT);
  
  // Attach the Servo
  MyServo.attach(SERVO_PIN);
  MyServo.write(POS_1);
}

void loop() { 
  // Read the sensor values
  int sensor1_state = digitalRead(SENSOR_1);
  int sensor2_state = digitalRead(SENSOR_2);
  
  // Determine the current state based on the sensor values
  if(sensor1_state == LOW && sensor2_state == LOW){
    currentState = STATE_1;
  }else if(sensor1_state == LOW && sensor2_state == HIGH){
    currentState = STATE_2;
  }else{
    currentState = STATE_3;
  }

  // Set the Servo position and LED status based on the current state
  setServo(currentState);
  setLEDs(currentState);

  // Wait for 200ms before the next loop
  delay(200);
}

void setServo(STATE state){
  // Set the Servo position based on the current state
  if(state == STATE_1){
    MyServo.write(POS_1);
  }else if(state == STATE_2){
    MyServo.write(POS_2);
  }else if(state == STATE_3){
    MyServo.write(POS_3);
  }
}

void setLEDs(STATE state){
  // Set the LED status based on the current state
  if(state == STATE_1){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
  }else if(state == STATE_2){
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
  }else if(state == STATE_3){
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
  }
}
```
#### Please note that this is a simple demonstration of using sensor inputs to control a Servo and LEDs. Depending on your specific sensors and hardware, you might need to adjust the code. Always make sure your hardware is compatible and correctly connected.